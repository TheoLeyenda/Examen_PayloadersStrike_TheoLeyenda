// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
	}
}

void UHealthComponent::AddCurrentHealth(float AddValue)
{
	CurrentHealth = CurrentHealth + AddValue;
	CheckMaxHealth();
}

void UHealthComponent::SubstractCurrentHealth(float SubstractValue)
{
	CurrentHealth = CurrentHealth - SubstractValue;
	CheckDeath();
}

void UHealthComponent::AddMaxHealth(float AddValue)
{
	MaxHealth = MaxHealth + AddValue;
}

void UHealthComponent::SubstractMaxHealth(float SubstractValue)
{
	MaxHealth = MaxHealth - SubstractValue;
	CheckMaxHealth();
}

void UHealthComponent::SetCurrentHealth(float Value)
{
	CurrentHealth = Value;
	CheckDeath();
	CheckMaxHealth();
}

void UHealthComponent::SetMaxHealth(float Value)
{
	MaxHealth = Value;
	CheckMaxHealth();
}

float UHealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser)
{
	if(Damage <= 0)
		return;

	SubstractCurrentHealth(Damage);

	OnReciveDamage.Broadcast(CurrentHealth, MaxHealth);
}

void UHealthComponent::CheckDeath()
{
	if(CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		OnStartDeath.Broadcast();
	}
}

void UHealthComponent::CheckMaxHealth()
{
	if(CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

