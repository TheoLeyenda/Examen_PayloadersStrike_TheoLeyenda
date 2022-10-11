#include "BTService_CheckExplosion.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Payloaders_Test/Components/ExplosiveComponent.h"
#include "Payloaders_Test/Controllers/EnemyController.h"

UBTService_CheckExplosion::UBTService_CheckExplosion()
{
	bNotifyBecomeRelevant = true;
}

void UBTService_CheckExplosion::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Blackboard) return;
	
	AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));
	AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	
	if(Target && EnemyController && EnemyController->GetPawn())
	{
		if(auto* ExplosiveComponent = Cast<UExplosiveComponent>(EnemyController->GetPawn()->GetComponentByClass(UExplosiveComponent::StaticClass())))
		{
			float CurrentDistance = FVector::Distance(Target->GetActorLocation(), EnemyController->GetPawn()->GetActorLocation());

			if(CurrentDistance <= RangeToExplosion)
			{
				ExplosiveComponent->Detonate();
			}
		}

	}
}
