// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Payloaders_TestProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class APayloaders_TestProjectile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
protected:

	UPROPERTY(VisibleAnywhere)
	AController* OwnerShooterController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Projectile)
	TSubclassOf<UDamageType> DamageType;
public:
	UPROPERTY(BlueprintReadWrite, Category= Projectile)
	float DamageHit = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Projectile)
	float ImpulseHit = 200;

public:
	APayloaders_TestProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent
	, AActor* OtherActor
	, UPrimitiveComponent* OtherComponent
	, int32 OtherBodyIndex
	, bool bFromSweep
	, const FHitResult& SweepResult);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

