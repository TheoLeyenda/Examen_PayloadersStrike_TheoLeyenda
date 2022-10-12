// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Payloaders_Test/Characters/EnemyShooter.h"
#include "Payloaders_Test/Controllers/EnemyController.h"
#include "Payloaders_Test/Controllers/ShooterController.h"
#include "Payloaders_Test/Projectiles/Payloaders_TestProjectile.h"

UBTService_Shoot::UBTService_Shoot()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

void UBTService_Shoot::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	ShooterController = Cast<AShooterController>(OwnerComp.GetAIOwner());
}

void UBTService_Shoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Blackboard = OwnerComp.GetBlackboardComponent();
	if(Blackboard)
	{
		if(ShooterController && ShooterController->bEnableShoot)
		{
			Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));
			ProjectileSpawn = Cast<USceneComponent>(Blackboard->GetValueAsObject(ProjectileSpawnKey.SelectedKeyName));

			if(Target && ProjectileSpawn)
			{
				float FireRate = Blackboard->GetValueAsFloat(FireRateKey.SelectedKeyName);
				ShooterController->SetFocus(Target);
				ShooterController->SetTimerShoot(FireRate);
				Shoot();
				ShooterController->bEnableShoot = false;
			}
		}
	}
}

void UBTService_Shoot::Shoot()
{
	if(auto* EnemyCharacter = ShooterController->Agent)
	{
		const FRotator SpawnRotation = ShooterController->Agent->GetControlRotation();
		const FVector SpawnLocation = ((ProjectileSpawn != nullptr) ? ProjectileSpawn->GetComponentLocation() : EnemyCharacter->GetActorLocation()) + SpawnRotation.RotateVector(ProjectileSpawnOffset);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		APayloaders_TestProjectile* Projectile = GetWorld()->SpawnActor<APayloaders_TestProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		
		if(auto* EnemyShooter = Cast<AEnemyShooter>(ShooterController->Agent))
		{
			if(Projectile)
			{
				Projectile->DamageHit = EnemyShooter->ShootDamage;
			}
		}
		
	}
	
}