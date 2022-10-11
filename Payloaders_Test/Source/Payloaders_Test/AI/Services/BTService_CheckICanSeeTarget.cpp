// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckICanSeeTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Payloaders_Test/Controllers/EnemyController.h"

UBTService_CheckICanSeeTarget::UBTService_CheckICanSeeTarget()
{
	bNotifyTick = true;
}

void UBTService_CheckICanSeeTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(auto* Blackboard = OwnerComp.GetBlackboardComponent())
	{
		if(auto* EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
		{
			EnemyController->UpdateActorsDetected();
			TArray<AActor*> Actors = EnemyController->ActorsDetected;
		
			if(auto* Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName)))
			{
				bool bFoundTarget = false;
				for(AActor* Actor : Actors)
				{
					if(Target == Actor)
					{
						bFoundTarget = true;
					}
				}
				Blackboard->SetValueAsBool(ICanSeeTargetKey.SelectedKeyName, bFoundTarget);
			}
			else
			{
				Blackboard->SetValueAsBool(ICanSeeTargetKey.SelectedKeyName, false);
			}
		}
	}
}
