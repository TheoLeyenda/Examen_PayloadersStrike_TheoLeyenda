// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UHealthUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UHealthComponent* HealthComponent;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float UpdateProgressBar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitHealthUserWidget();
};
