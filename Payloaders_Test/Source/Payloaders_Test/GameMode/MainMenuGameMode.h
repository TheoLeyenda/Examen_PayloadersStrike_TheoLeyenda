// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Levels")
	FName FirstLevelName;

	APlayerController* PlayerController;
	
public:
	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void ExitGame();
};
