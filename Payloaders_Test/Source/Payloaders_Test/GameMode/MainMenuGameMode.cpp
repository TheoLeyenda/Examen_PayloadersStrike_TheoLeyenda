// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
}

void AMainMenuGameMode::PlayGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FirstLevelName);
}

void AMainMenuGameMode::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),PlayerController,EQuitPreference::Quit, true);
}
