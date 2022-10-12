// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Payloaders_Test/Characters/EnemyShooter.h"
#include "Payloaders_Test/Controllers/EnemyController.h"
#include "Payloaders_Test/Projectiles/Payloaders_TestProjectile.h"

UBTService_Shoot::UBTService_Shoot()
{
	bNotifyTick = true;
}
void UBTService_Shoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Blackboard = OwnerComp.GetBlackboardComponent();
	EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	if(Blackboard)
	{
		if(Blackboard->GetValueAsBool(EnableShootKey.SelectedKeyName) || bFlagFirstShoot)
		{
			Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));
			ProjectileSpawn = Cast<USceneComponent>(Blackboard->GetValueAsObject(ProjectileSpawnKey.SelectedKeyName));

			if(EnemyController && Target && ProjectileSpawn)
			{
				float FireRate = Blackboard->GetValueAsFloat(FireRateKey.SelectedKeyName);
				EnemyController->SetFocus(Target);
				GetWorld()->GetTimerManager().SetTimer(ShootTimer,this, &UBTService_Shoot::Shoot, FireRate, false);
				Blackboard->SetValueAsBool(EnableShootKey.SelectedKeyName, false);
				bFlagFirstShoot = false;
			}
		}
	}
}

void UBTService_Shoot::Shoot()
{
	if(auto* EnemyCharacter = EnemyController->Agent)
	{
		const FRotator SpawnRotation = EnemyController->Agent->GetControlRotation();
		const FVector SpawnLocation = ((ProjectileSpawn != nullptr) ? ProjectileSpawn->GetComponentLocation() : EnemyCharacter->GetActorLocation()) + SpawnRotation.RotateVector(ProjectileSpawnOffset);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		APayloaders_TestProjectile* Projectile = GetWorld()->SpawnActor<APayloaders_TestProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		
		if(auto* EnemyShooter = Cast<AEnemyShooter>(EnemyController->Agent))
		{
			if(Projectile)
			{
				Projectile->DamageHit = EnemyShooter->ShootDamage;
			}
		}
		Blackboard->SetValueAsBool(EnableShootKey.SelectedKeyName, true);
	}
	
}