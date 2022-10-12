// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterController.h"

void AShooterController::SetTimerShoot(float DelayShoot)
{
	GetWorld()->GetTimerManager().SetTimer(ShootTimer,this, &AShooterController::AviableSoot, DelayShoot, false);
}

void AShooterController::AviableSoot()
{
	bEnableShoot = true;
}
