// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Payloaders_Test/GameMode/GameplayGameMode.h"

void UScoreUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameplayGameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if(GameplayGameMode)
	{
		Score = GameplayGameMode->CurrentScore;
	}
}

int32 UScoreUserWidget::UpdateCurrentScore()
{
	if(GameplayGameMode)
	{
		Score = GameplayGameMode->CurrentScore;
	}
	return Score;
}
