// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Payloaders_Test/Characters/EnemyCharacter.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI" , meta = (ClampMin = 0.01f))
	float LostTargetDelay = 0.01f;

	FTimerHandle LostTargetTimer;

	UFUNCTION()
	void SelectNewTarget();

	UFUNCTION()
	void OnAgentDeah();
	
public:
	AEnemyController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "AI")
	AEnemyCharacter* Agent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI")
	TArray<TSubclassOf<AActor>> TargetClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "AI")
	AActor* CurrentTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "AI")
	TArray<AActor*> ActorsDetected;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "AI")
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI")
	FName TargetKey = "Target";

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateActorsDetected();

	UFUNCTION(BlueprintCallable)
	void SetCurrentTarget(AActor* NewTarget);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* GetClosetActorDetected();
	
	class UAISenseConfig_Sight* SightConfig;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Destroyed() override;

private:
	bool bWaitProssesPerception = false;
	
};
