// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainMenuButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ResetLevelButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MainMenuLevelName = "MainMenuMap";

	UFUNCTION()
	void OpenMainMenuLevel();

	UFUNCTION()
	void ResetCurrentLevel();
	
	virtual void NativeConstruct() override;
};
