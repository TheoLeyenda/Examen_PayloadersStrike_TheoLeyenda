// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameplayGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Payloaders_Test/Characters/PlayerCharacter.h"
#include "Payloaders_Test/Characters/EnemyCharacter.h"
#include "Payloaders_Test/HUD/GameplayHUD.h"
#include "GameFramework/PlayerStart.h"
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

	TArray<AActor*> PlayerStartActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);

	for(AActor* Actor : PlayerStartActors)
	{
		if(auto* NewPlayerStart = Cast<APlayerStart>(Actor))
		{
			if(NewPlayerStart->PlayerStartTag != "PlayerSpawn")
			{
				PlayerStarts.Add(NewPlayerStart);
			}
		}
	}

	TArray<AActor*> EnemyCharacterActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), EnemyCharacterActors);
	for(AActor* Actor : EnemyCharacterActors)
	{
		if(auto* NewEnemyCharacter = Cast<AEnemyCharacter>(Actor))
		{
			if(auto* HealthComponent = Cast<UHealthComponent>(NewEnemyCharacter->GetComponentByClass(UHealthComponent::StaticClass())))
			{
				if(!HealthComponent->OnReciveDamage.Contains(this, "UpdateScoreForHit"))
				{
					HealthComponent->OnReciveDamage.AddDynamic(this, &AGameplayGameMode::AGameplayGameMode::UpdateScoreForHit);
				}
			}
			if(!NewEnemyCharacter->OnDeathCharacter.Contains(this, "UpdateScoreForKill"))
			{
				NewEnemyCharacter->OnDeathCharacter.AddDynamic(this, &AGameplayGameMode::UpdateScoreForKill);
			}
			EnemysSpawned.Add(NewEnemyCharacter);
		}
	}
	SetSpawnTimer();
}

void AGameplayGameMode::SpawnEnemy()
{
	EnemysSpawned.Remove(nullptr);
	
	if(PlayerStarts.Num() <= 0 || EnemysToSpawnClasses.Num() <= 0 || EnemysSpawned.Num() >= MaxEnemysSpawn)
	{
		SetSpawnTimer();
		return;
	}
	
	int indexSpawner = FMath::RandRange(0, PlayerStarts.Num()-1);

	FVector SpawnLocation = PlayerStarts[indexSpawner]->GetActorLocation();
	FRotator SpawnRotator = PlayerStarts[indexSpawner]->GetActorRotation();

	int indexEnemyClass = FMath::RandRange(0, EnemysToSpawnClasses.Num()-1);

	TSubclassOf<AEnemyCharacter> EnemyClass = EnemysToSpawnClasses[indexEnemyClass];

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	AEnemyCharacter* EnemySpawned = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass,SpawnLocation, SpawnRotator, ActorSpawnParams);
	if(EnemySpawned)
	{
		if(auto* HealthComponent = Cast<UHealthComponent>(EnemySpawned->GetComponentByClass(UHealthComponent::StaticClass())))
		{
			if(!HealthComponent->OnReciveDamage.Contains(this, "UpdateScoreForHit"))
			{
				HealthComponent->OnReciveDamage.AddDynamic(this, &AGameplayGameMode::AGameplayGameMode::UpdateScoreForHit);
			}
		}
		if(!EnemySpawned->OnDeathCharacter.Contains(this, "UpdateScoreForKill"))
		{
			EnemySpawned->OnDeathCharacter.AddDynamic(this, &AGameplayGameMode::UpdateScoreForKill);
		}
		EnemysSpawned.Add(EnemySpawned);

	}
	SetSpawnTimer();
}

void AGameplayGameMode::UpdateScoreForHit(float CurrentHealth, float MaxHealth)
{
	CurrentScore = CurrentScore + ScoreForHit;
}

void AGameplayGameMode::UpdateScoreForKill(ABaseCharacter* BaseCharacter)
{
	if(!BaseCharacter)
		return;
	
	for(int i = 0; i < EnemysSpawned.Num(); i++)
	{
		if(EnemysSpawned[i])
		{
			if(EnemysSpawned[i] == BaseCharacter)
			{
				for(int j = 0; j < KillsScores.Num(); j++)
				{
					if(KillsScores[j].EnemyClassKill == BaseCharacter->GetClass())
					{
						CurrentScore = CurrentScore + KillsScores[j].Score;
						return;
					}
				}
			}
		}
	}
	EnemysSpawned.RemoveSingle(Cast<AEnemyCharacter>(BaseCharacter));
}

void AGameplayGameMode::SetSpawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnEnemyTimer,this, &AGameplayGameMode::SpawnEnemy, FMath::RandRange(MinSpawnEnemysDelay, MaxSpawnEnemysDelay), false);
}
