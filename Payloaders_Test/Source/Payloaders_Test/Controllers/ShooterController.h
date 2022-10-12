// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "ShooterController.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API AShooterController : public AEnemyController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bEnableShoot = true;

	UFUNCTION(BlueprintCallable)
	void SetTimerShoot(float DelayShoot);

	UFUNCTION(BlueprintCallable)
	void AviableSoot();
	
	FTimerHandle ShootTimer;
};
