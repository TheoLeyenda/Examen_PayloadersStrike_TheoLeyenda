// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUserWidget.h"

#include "Components/Button.h"
#include "Payloaders_Test/GameMode/MainMenuGameMode.h"

void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(PlayButton && ExitButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnClickPlayButton);
		ExitButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnClickExitButton);
	}
}

void UMainMenuUserWidget::OnClickPlayButton()
{
	if(MainMenuGameMode)
	{
		MainMenuGameMode->PlayGame();
	}
}

void UMainMenuUserWidget::OnClickExitButton()
{
	if(MainMenuGameMode)
	{
		MainMenuGameMode->ExitGame();
	}
}
