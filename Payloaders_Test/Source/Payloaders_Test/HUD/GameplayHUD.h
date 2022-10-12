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

	virtual void BeginPlay() override;
	
private:
	class UTexture2D* CrosshairTex;
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Widgets")
	class UPlayerUserWidget* PlayerUserWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Widgets")
	class UGameOverUserWidget* GameOverUserWidget;

	UFUNCTION()
	void ActivateGameOverViewport(ABaseCharacter* Character);
private:
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	bool bGameOverInViewport = false;
};

