// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthUserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Payloaders_Test/Components/HealthComponent.h"
#include "Payloaders_Test/GameMode/GameplayGameMode.h"
#include "Payloaders_Test/Characters/PlayerCharacter.h"

void UHealthUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitHealthUserWidget_Implementation();
}

void UHealthUserWidget::InitHealthUserWidget_Implementation()
{
	bool bInitDone = false;
	
	if(auto* GameplayGameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if(GameplayGameMode->PlayerCharacter)
		{
			HealthComponent = Cast<UHealthComponent>(GameplayGameMode->PlayerCharacter->GetComponentByClass(UHealthComponent::StaticClass()));
			if(HealthComponent)
			{
				CurrentHealth =  HealthComponent->GetCurrentHealth();
				MaxHealth = HealthComponent->GetMaxHealth();
				bInitDone = true;
			}
		}
	}
		
	if(!bInitDone)
	{
		CurrentHealth = 100.0f;
		MaxHealth = 100.0f;
	}
}

float UHealthUserWidget::UpdateProgressBar()
{
	CurrentHealth =  HealthComponent->GetCurrentHealth();
	MaxHealth = HealthComponent->GetMaxHealth();
	float Value = 0;
	Value = CurrentHealth;
	Value = Value * 100;
	Value = Value / MaxHealth;
	Value = Value / 100;
	
	return Value;
}
