// Copyright Epic Games, Inc. All Rights Reserved.

#include "SurvivalGameMode.h"
#include "Payloaders_TestHUD.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASurvivalGameMode::ASurvivalGameMode(): Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APayloaders_TestHUD::StaticClass();
}
