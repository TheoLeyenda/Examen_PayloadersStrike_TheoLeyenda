#include "EnemyShooter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Payloaders_Test/Controllers/EnemyController.h"

AEnemyShooter::AEnemyShooter()
{
	WeaponSKM = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeletalMesh");
	WeaponSKM->SetupAttachment(GetMesh());
	ProjectileSpawnScene = CreateDefaultSubobject<USceneComponent>("ProjectileSpawn");
	ProjectileSpawnScene->SetupAttachment(WeaponSKM);
}

void AEnemyShooter::BeginPlay()
{
	Super::BeginPlay();

	if(EnemyController)
	{
		UBlackboardComponent* BlackboardComponent = EnemyController->BlackboardComponent;
		if(BlackboardComponent)
		{
			BlackboardComponent->SetValueAsFloat(RangeAttackKeyName, RangeAttack);
			BlackboardComponent->SetValueAsFloat(FireRateKeyName, FireRate);
			BlackboardComponent->SetValueAsObject(ProjectileSpawnKeyName, ProjectileSpawnScene);
		}
	}
}

void AEnemyShooter::Death()
{
	Super::Death();
	ApplyRagdoll();
	GetWorld()->GetTimerManager().SetTimer(DestroyActorTimer,this, &AEnemyShooter::AutoDestroy, DestroyActorDelay, false);
}
