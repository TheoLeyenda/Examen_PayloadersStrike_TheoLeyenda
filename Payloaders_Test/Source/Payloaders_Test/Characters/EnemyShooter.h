// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "EnemyShooter.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API AEnemyShooter : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	AEnemyShooter();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Settings")
	float ShootDamage = 10.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	USkeletalMeshComponent* WeaponSKM;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	USceneComponent* ProjectileSpawnScene;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float RangeAttack = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float FireRate = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FName RangeAttackKeyName = "RangeAttack";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FName FireRateKeyName = "FireRate";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FName ProjectileSpawnKeyName = "ProjectileSpawn";
	
	virtual void Death() override;
};
