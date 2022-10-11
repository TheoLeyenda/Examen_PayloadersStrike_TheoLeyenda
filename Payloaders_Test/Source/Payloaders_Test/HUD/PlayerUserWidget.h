// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API UPlayerUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	class AGameplayGameMode* GameplayGameMode;
};
