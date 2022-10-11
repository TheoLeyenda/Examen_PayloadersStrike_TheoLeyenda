// Copyright Epic Games, Inc. All Rights Reserved.

#include "Payloaders_TestProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Payloaders_Test/Components/HealthComponent.h"

APayloaders_TestProjectile::APayloaders_TestProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APayloaders_TestProjectile::OnBeginOverlap);		// set up a notification for when this component hits something blocking
	CollisionComp->OnComponentHit.AddDynamic(this, &APayloaders_TestProjectile::OnHit);
	
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void APayloaders_TestProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if((OtherActor != nullptr) && (OtherActor != this))
	{
		if ((OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * ImpulseHit, GetActorLocation());
		}

		if(auto* HealthComponent = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass())))
		{
			HealthComponent->OnTakeDamage(OtherActor, DamageHit, DamageType.GetDefaultObject(), OwnerShooterController, this);
		}
		
		Destroy();
	}
}

void APayloaders_TestProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if((OtherActor != nullptr) && (OtherActor != this))
    {
    	if ((OtherComponent != nullptr) && OtherComponent->IsSimulatingPhysics())
    	{
    		OtherComponent->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
    	}

    	if(auto* HealthComponent = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass())))
    	{
    		HealthComponent->OnTakeDamage(OtherActor, DamageHit, DamageType.GetDefaultObject(), OwnerShooterController, this);
    	}
    	
    	Destroy();
    }
}
