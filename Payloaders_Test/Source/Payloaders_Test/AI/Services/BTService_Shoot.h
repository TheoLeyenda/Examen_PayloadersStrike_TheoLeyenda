// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UBTService_Shoot : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_Shoot();
	UFUNCTION()
	void Shoot();
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FBlackboardKeySelector ProjectileSpawnKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings", meta=(ClampMin = 0.01f))
	FBlackboardKeySelector FireRateKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FBlackboardKeySelector EnableShootKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FVector ProjectileSpawnOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category= "Settings")
	TSubclassOf<class APayloaders_TestProjectile> ProjectileClass;
	
	FTimerHandle ShootTimer;

	UBlackboardComponent* Blackboard;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	class AEnemyController* EnemyController = nullptr;
	USceneComponent* ProjectileSpawn = nullptr;
	AActor* Target = nullptr;
	bool bFlagFirstShoot = true;
};
