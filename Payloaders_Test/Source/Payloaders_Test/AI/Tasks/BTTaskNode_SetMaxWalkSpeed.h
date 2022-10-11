// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetMaxWalkSpeed.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UBTTaskNode_SetMaxWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float NewMaxWalkSpeed;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
