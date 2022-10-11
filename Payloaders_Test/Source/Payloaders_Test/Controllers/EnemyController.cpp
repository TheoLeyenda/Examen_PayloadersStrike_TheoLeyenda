// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyController::AEnemyController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2500.f;
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AEnemyController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	UpdateActorsDetected();
}

void AEnemyController::UpdateActorsDetected()
{
	if(!Agent) return;
	
	ActorsDetected.Empty();

	AIPerceptionComponent->GetCurrentlyPerceivedActors(SightConfig->GetSenseImplementation(),ActorsDetected);

	bool bCurrentTargetDetected = false;

	TArray<int32> IndexOfElementsToRemove;

	for(int i = 0; i < ActorsDetected.Num(); i++)
	{
		bool bRemoveItem = true;
		for(int j = 0; j < TargetClasses.Num(); j++)
		{
			if(ActorsDetected[i]->GetClass() == TargetClasses[j])
			{
				bRemoveItem = false;
			}
		}
		if(bRemoveItem)
		{
			IndexOfElementsToRemove.Add(i);
		}
	}
	
	for(int i = 0; i < IndexOfElementsToRemove.Num(); i++)
	{
		ActorsDetected.RemoveAt(IndexOfElementsToRemove[i]);
	}
	
	for(AActor* ActorDetected : ActorsDetected)
	{
		if(ActorDetected == CurrentTarget)
		{
			bCurrentTargetDetected = true;
			break;
		}
	}
	
	if(!bCurrentTargetDetected)
	{
		if(CurrentTarget)
		{
			GetWorld()->GetTimerManager().SetTimer(LostTargetTimer,this, &AEnemyController::SelectNewTarget, LostTargetDelay, false);
		}
		else
		{
			SelectNewTarget();
		}
	}
}

void AEnemyController::SetCurrentTarget(AActor* NewTarget)
{
	if(NewTarget)
	{
		BlackboardComponent->SetValueAsObject(TargetKey, NewTarget);
		if(auto* HealthComponent = Cast<UHealthComponent>(NewTarget->GetComponentByClass(UHealthComponent::StaticClass())))
		{
			if(!HealthComponent->OnStartDeath.Contains(this, FName("UpdateActorsDetected")))
			{
				HealthComponent->OnStartDeath.AddDynamic(this, &AEnemyController::UpdateActorsDetected);
			}
		}
	}
	else
	{
		if(CurrentTarget)
		{
			if(auto* HealthComponent = Cast<UHealthComponent>(CurrentTarget->GetComponentByClass(UHealthComponent::StaticClass())))
			{
				HealthComponent->OnStartDeath.Remove(this, FName("UpdateActorsDetected"));
			}
		}
		BlackboardComponent->ClearValue(TargetKey);
	}

	CurrentTarget = NewTarget;
}

void AEnemyController::SelectNewTarget()
{
	if(ActorsDetected.Num() == 1)
	{
		if(ActorsDetected[0] != nullptr)
		{
			SetCurrentTarget(ActorsDetected[0]);
			return;
		}
	}
		
	SetCurrentTarget(GetClosetActorDetected());
}

AActor* AEnemyController::GetClosetActorDetected()
{
	if(ActorsDetected.Num() == 0)
		return nullptr;

	float MinDistance = FVector::Distance(ActorsDetected[0]->GetActorLocation(), Agent->GetActorLocation());
	AActor* Actor = ActorsDetected[0];
	for(AActor* ActorDetected : ActorsDetected)
	{
		float CurrentDistance = FVector::Distance(ActorDetected->GetActorLocation(), Agent->GetActorLocation());
		if(CurrentDistance < MinDistance)
		{
			MinDistance = CurrentDistance;
			Actor = ActorDetected;
		}
	}
	return Actor;
}

void AEnemyController::OnAgentDeah()
{
	BehaviorTreeComponent->StopTree();
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Agent = Cast<AEnemyCharacter>(InPawn);
	
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnPerception);

	if(Agent && Agent->BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*Agent->BehaviorTree->BlackboardAsset);

		BehaviorTreeComponent->StartTree(*Agent->BehaviorTree);

		if(auto* HealthComponent = Cast<UHealthComponent>(Agent->GetComponentByClass(UHealthComponent::StaticClass())))
		{
			HealthComponent->OnStartDeath.AddDynamic(this, &AEnemyController::OnAgentDeah);
		}
	}
}

void AEnemyController::Destroyed()
{
	if(CurrentTarget)
	{
		if(auto* HealthComponent = Cast<UHealthComponent>(CurrentTarget->GetComponentByClass(UHealthComponent::StaticClass())))
		{
			HealthComponent->OnStartDeath.Remove(this, FName("UpdateActorsDetected"));
		}
	}
	if(Agent)
	{
		if(auto* HealthComponent = Cast<UHealthComponent>(Agent->GetComponentByClass(UHealthComponent::StaticClass())))
		{
			HealthComponent->OnStartDeath.Clear();
		}
	}
	
	Super::Destroyed();
}
