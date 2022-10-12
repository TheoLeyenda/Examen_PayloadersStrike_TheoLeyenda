// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite)
	class AGameplayGameMode* GameplayGameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Score Text")
	FString ScoreString  = "Score: ";

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 UpdateCurrentScore();
	
};
