// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnStartDeath.AddDynamic(this, &ABaseCharacter::Death);
}

void ABaseCharacter::AutoDestroy()
{
	GetWorld()->GetTimerManager().ClearTimer(DestroyActorTimer);
	Destroy();
}

void ABaseCharacter::ApplyRagdoll()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}


void ABaseCharacter::Destroyed()
{
	Super::Destroyed();

	if(HealthComponent)
	{
		HealthComponent->OnStartDeath.Clear();
	}
}

void ABaseCharacter::Death()
{
	OnDeathCharacter.Broadcast(this);
}



