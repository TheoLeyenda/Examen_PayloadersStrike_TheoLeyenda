// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckICanSeeTarget.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UBTService_CheckICanSeeTarget : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_CheckICanSeeTarget();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FBlackboardKeySelector ICanSeeTargetKey;
	
	//virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
