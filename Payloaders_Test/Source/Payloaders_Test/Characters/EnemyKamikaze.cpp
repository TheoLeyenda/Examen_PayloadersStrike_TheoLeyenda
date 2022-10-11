// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyKamikaze.h"

AEnemyKamikaze::AEnemyKamikaze()
{
	ExplosiveComponent = CreateDefaultSubobject<UExplosiveComponent>(TEXT("ExplosiveComponent"));
}

void AEnemyKamikaze::BeginPlay()
{
	Super::BeginPlay();

	ExplosiveComponent->OnFinishExplosion.AddDynamic(this, &AEnemyKamikaze::AutoDestroy);
}

void AEnemyKamikaze::Death()
{
	Super::Death();
	ExplosiveComponent->Detonate();
}

void AEnemyKamikaze::Destroyed()
{
	Super::Destroyed();
	
	ExplosiveComponent->OnFinishExplosion.Clear();
}
