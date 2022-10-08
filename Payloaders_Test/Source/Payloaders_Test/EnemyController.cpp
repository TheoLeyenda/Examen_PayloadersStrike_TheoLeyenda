// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	Agent = Cast<ACharacter>(GetPawn());
}

AEnemyController::AEnemyController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2500.f;
	SightConfig->PeripheralVisionAngleDegrees = 180.f;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AEnemyController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if(!Agent) return;
	
	ActorsDetected.Empty();

	AIPerceptionComponent->GetCurrentlyPerceivedActors(SightConfig->GetSenseImplementation(),ActorsDetected);

	bool bCurrentTargetDetected = false;
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
		CurrentTarget = nullptr;
		//Si hay solo 1 lo asigna.

		if(ActorsDetected.Num() == 1)
		{
			if(ActorsDetected[0] != nullptr && ActorsDetected[0]->GetClass() == TargetClass)
			{
				SetCurrentTarget(ActorsDetected[0]);
			}
		}

		//sino busca al target mas cercano (TESTEAR QUE BUSQUE AL MAS CERCANO)
		CurrentTarget = GetClosetActorDetected();
	}
}

void AEnemyController::SetCurrentTarget(AActor* NewTarget)
{
	CurrentTarget = NewTarget;
	SetFocus(NewTarget);
}

AActor* AEnemyController::GetClosetActorDetected()
{
	if(ActorsDetected.Num() == 0)
		return nullptr;

	float MinDistance = FVector::Distance(ActorsDetected[0]->GetActorLocation(), Agent->GetActorLocation());
	AActor* Actor = nullptr;
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

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnPerception);
}
