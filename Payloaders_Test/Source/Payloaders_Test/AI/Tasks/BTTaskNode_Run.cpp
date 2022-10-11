// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Run.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Payloaders_Test/Controllers/EnemyController.h"

EBTNodeResult::Type UBTTaskNode_Run::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	
	if(auto* OwnerCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if(auto* CharacterMovementComponent = Cast<UCharacterMovementComponent>(OwnerCharacter->GetComponentByClass(UCharacterMovementComponent::StaticClass())))
		{
			CharacterMovementComponent->MaxWalkSpeed = OwnerCharacter->RunningSpeed;
			CharacterMovementComponent->MaxAcceleration = OwnerCharacter->RunningSpeed * 2;
			return EBTNodeResult::Succeeded;
		}
	}
		
	return EBTNodeResult::Failed;
}
