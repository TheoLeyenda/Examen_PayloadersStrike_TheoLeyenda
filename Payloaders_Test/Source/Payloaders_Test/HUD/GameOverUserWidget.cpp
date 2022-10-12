// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(MainMenuButton && ResetLevelButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("Buttons Valid"))

		MainMenuButton->OnClicked.AddDynamic(this, &UGameOverUserWidget::OpenMainMenuLevel);
		ResetLevelButton->OnClicked.AddDynamic(this, &UGameOverUserWidget::ResetCurrentLevel);
	}
}

void UGameOverUserWidget::OpenMainMenuLevel()
{

	if(GetWorld())
		UGameplayStatics::OpenLevel(GetWorld(),MainMenuLevelName);
	
}

void UGameOverUserWidget::ResetCurrentLevel()
{
	if(GetWorld())
		UGameplayStatics::OpenLevel(GetWorld(),FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}
