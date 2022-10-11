#include "BTService_CheckInRangeAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckInRangeAttack::UBTService_CheckInRangeAttack()
{
	bNotifyTick = true;
}

void UBTService_CheckInRangeAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(auto* Blackboard = OwnerComp.GetBlackboardComponent())
	{
		if(auto* Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName)))
		{
			if(OwnerComp.GetAIOwner())
			{
				if(OwnerComp.GetAIOwner()->GetPawn())
				{
					float DistanceRequiredToShoot = Blackboard->GetValueAsFloat(RangeAttackKey.SelectedKeyName);
					float CurrentDistanceToTarget = FVector::Distance(Target->GetActorLocation(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
					Blackboard->SetValueAsBool(InRangeAttackKey.SelectedKeyName, CurrentDistanceToTarget <= DistanceRequiredToShoot);
				}
			}
		}
		else
		{
			Blackboard->SetValueAsBool(InRangeAttackKey.SelectedKeyName, false);
		}
	}
}
