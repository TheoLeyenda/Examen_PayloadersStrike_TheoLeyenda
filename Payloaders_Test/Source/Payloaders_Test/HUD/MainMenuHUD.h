// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AMainMenuGameMode* MainMenuGameMode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Widgets")
	class UMainMenuUserWidget* MainMenuUserWidget;
};
