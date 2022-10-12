// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

USTRUCT(BlueprintType)
struct FScoreForKill
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AEnemyCharacter> EnemyClassKill;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score;	
};

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Scoring")
	int32 CurrentScore = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Scoring")
	int32 ScoreForHit = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Scoring")
	TArray<FScoreForKill> KillsScores;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Spawning Enemys")
	TArray<AEnemyCharacter*> EnemysSpawned;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning Enemys")
	TArray<TSubclassOf<AEnemyCharacter>> EnemysToSpawnClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Spawning Enemys")
	TArray<class APlayerStart*> PlayerStarts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Spawning Enemys")
	int32 MaxEnemysSpawn = 25.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Spawning Enemys")
	float MinSpawnEnemysDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Spawning Enemys")
	float MaxSpawnEnemysDelay;
	
	FTimerHandle SpawnEnemyTimer;
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UFUNCTION()
	void UpdateScoreForHit(float CurrentHealth, float MaxHealth);

	UFUNCTION()
	void UpdateScoreForKill(class ABaseCharacter* Character);

	//virtual void Destroyed() override;
	
private:
	UFUNCTION()
	void SetSpawnTimer();
};
