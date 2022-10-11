// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckInRangeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UBTService_CheckInRangeAttack : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_CheckInRangeAttack();
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FBlackboardKeySelector InRangeAttackKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FBlackboardKeySelector RangeAttackKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FBlackboardKeySelector TargetKey;
	
	//virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
