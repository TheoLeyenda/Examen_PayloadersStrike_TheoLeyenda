// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Payloaders_Test/Components/HealthComponent.h"
#include "BaseCharacter.generated.h"
UCLASS()
class PAYLOADERS_TEST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathCharacter, ABaseCharacter*, BaseCharacter);
public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings", meta=(ClampMin = 0.01))
	float DestroyActorDelay = 0.01;

	FTimerHandle DestroyActorTimer;

	FOnDeathCharacter OnDeathCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	UHealthComponent* HealthComponent;
	
	UFUNCTION(BlueprintCallable)
	virtual void Death();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void AutoDestroy();

	UFUNCTION()
	void ApplyRagdoll();
	
	virtual void Destroyed() override;

};
