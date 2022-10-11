// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Payloaders_Test/Characters/PlayerCharacter.h"
#include "Payloaders_Test/HUD/GameplayHUD.h"
#include "UObject/ConstructorHelpers.h"

AGameplayGameMode::AGameplayGameMode(): Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGameplayHUD::StaticClass();
}

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
}
