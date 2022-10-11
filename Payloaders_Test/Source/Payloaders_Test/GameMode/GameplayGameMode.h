// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

UCLASS(minimalapi)
class AGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameplayGameMode();
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
	class APlayerCharacter* PlayerCharacter;
};



