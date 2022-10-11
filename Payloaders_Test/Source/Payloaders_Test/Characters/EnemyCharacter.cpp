// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Payloaders_Test/Controllers/EnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultMaxWalkSpeed = CharacterMovement->MaxWalkSpeed;
	DefaultMaxWalkSpeedCrouched = CharacterMovement->MaxWalkSpeedCrouched;
	DefaultMaxAcceleration = CharacterMovement->MaxAcceleration;
	DefaultMaxFlySpeed = CharacterMovement->MaxFlySpeed;
	DefaultMaxSwimSpeed = CharacterMovement->MaxSwimSpeed;

	EnemyController = Cast<AEnemyController>(GetController());
}

