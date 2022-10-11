// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AISense_Damage.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAYLOADERS_TEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartDeath);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReciveDamage, float, CurrentHealth, float, MaxHealth);
public:	
	UHealthComponent();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void AddCurrentHealth(float AddValue);

	UFUNCTION(BlueprintCallable)
	void SubstractCurrentHealth(float SubstractValue);

	UFUNCTION(BlueprintCallable)
	void AddMaxHealth(float AddValue);

	UFUNCTION(BlueprintCallable)
	void SubstractMaxHealth(float SubstractValue);
	
	void SetCurrentHealth(float Value);
	
	void SetMaxHealth(float Value);

	float GetCurrentHealth();

	float GetMaxHealth();
	
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStartDeath OnStartDeath;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnReciveDamage OnReciveDamage;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float CurrentHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float MaxHealth = 100;

private:
	void CheckDeath();

	void CheckMaxHealth();
};
