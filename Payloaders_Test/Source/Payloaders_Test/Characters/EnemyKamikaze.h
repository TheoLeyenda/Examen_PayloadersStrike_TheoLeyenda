// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Payloaders_Test/Components/ExplosiveComponent.h"
#include "EnemyKamikaze.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API AEnemyKamikaze : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	AEnemyKamikaze();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	UExplosiveComponent* ExplosiveComponent;
	
	virtual void Death() override;
protected:
	void Destroyed() override;
};
