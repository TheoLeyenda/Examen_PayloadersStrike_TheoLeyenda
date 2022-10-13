// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Payloaders_Test/Controllers/EnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	DefaultMaxWalkSpeedCrouched = GetCharacterMovement()->MaxWalkSpeedCrouched;
	DefaultMaxAcceleration = GetCharacterMovement()->MaxAcceleration;
	DefaultMaxFlySpeed = GetCharacterMovement()->MaxFlySpeed;
	DefaultMaxSwimSpeed = GetCharacterMovement()->MaxSwimSpeed;

	EnemyController = Cast<AEnemyController>(GetController());
}

