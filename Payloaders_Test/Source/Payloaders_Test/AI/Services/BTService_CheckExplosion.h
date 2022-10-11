// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckExplosion.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UBTService_CheckExplosion : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_CheckExplosion();
protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	FBlackboardKeySelector TargetKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float RangeToExplosion;
	
};
