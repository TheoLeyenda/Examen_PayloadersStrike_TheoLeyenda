// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_SetMaxWalkSpeed.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Payloaders_Test/Controllers/EnemyController.h"

EBTNodeResult::Type UBTTaskNode_SetMaxWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
	
	if(auto* OwnerCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if(auto* CharacterMovementComponent = Cast<UCharacterMovementComponent>(OwnerCharacter->GetComponentByClass(UCharacterMovementComponent::StaticClass())))
		{
			CharacterMovementComponent->MaxWalkSpeed = NewMaxWalkSpeed;
			CharacterMovementComponent->MaxAcceleration = NewMaxWalkSpeed * 2;
			return EBTNodeResult::Succeeded;
		}
	}
		
	return EBTNodeResult::Failed;
}
