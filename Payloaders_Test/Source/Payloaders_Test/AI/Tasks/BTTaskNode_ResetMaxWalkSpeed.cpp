// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_ResetMaxWalkSpeed.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Payloaders_Test/Characters/EnemyCharacter.h"

EBTNodeResult::Type UBTTaskNode_ResetMaxWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

	if(auto* OwnerCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		if(auto* CharacterMovementComponent = Cast<UCharacterMovementComponent>(OwnerCharacter->GetComponentByClass(UCharacterMovementComponent::StaticClass())))
		{
			CharacterMovementComponent->MaxWalkSpeed = OwnerCharacter->DefaultMaxWalkSpeed;
			CharacterMovementComponent->MaxAcceleration = OwnerCharacter->DefaultMaxAcceleration;
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
