// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Payloaders_Test/GameMode/GameplayGameMode.h"
#include "GameplayHUD.generated.h"

UCLASS()
class AGameplayHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGameplayHUD();
	
	virtual void DrawHUD() override;

private:
	class UTexture2D* CrosshairTex;
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "GameModeUse")
	class AGameplayGameMode* GameplayGameMode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Health")
	class UPlayerUserWidget* PlayerUserWidget;
};

