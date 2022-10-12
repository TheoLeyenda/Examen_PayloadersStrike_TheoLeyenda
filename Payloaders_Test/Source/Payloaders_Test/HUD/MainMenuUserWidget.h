// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AMainMenuGameMode* MainMenuGameMode;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ExitButton;

	UFUNCTION()
	void OnClickPlayButton();

	UFUNCTION()
	void OnClickExitButton();
};
