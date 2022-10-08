// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PAYLOADERS_TEST_API AEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionComponent* AIPerceptionComponent;

	virtual void BeginPlay() override;
public:
	AEnemyController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "AI")
	ACharacter* Agent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI | DetectionSystem")
	TSubclassOf<AActor> TargetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "AI | DetectionSystem")
	AActor* CurrentTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI | DetectionSystem")
	TArray<AActor*> ActorsDetected;
	
	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)
	void SetCurrentTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* GetClosetActorDetected();
	
	class UAISenseConfig_Sight* SightConfig;

	virtual void OnPossess(APawn* InPawn) override;
	
};
