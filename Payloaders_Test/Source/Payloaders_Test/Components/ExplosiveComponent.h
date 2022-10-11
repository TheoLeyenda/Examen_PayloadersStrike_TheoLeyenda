// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExplosiveComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishExplosion);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAYLOADERS_TEST_API UExplosiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExplosiveComponent();

	UFUNCTION(BlueprintCallable)
	void SpawnParticles();

	UFUNCTION(BlueprintCallable)
	virtual void Detonate();

	UFUNCTION(BlueprintCallable)
	void ActivateTimerToDetonate();

	FOnFinishExplosion OnFinishExplosion;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	TSubclassOf<AActor> ExplosionFilterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	TArray<TEnumAsByte<ECollisionChannel>> CollisionChannels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings", meta=(ClampMin = 0.01f))
	float DelayToDetonate = 0.01f;

	FTimerHandle TimerToDetonate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FVector OffsetSpawnParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	FVector ScaleParticles = FVector(1,1,1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float ExplosionImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float ExplosionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float ExplosionDamage;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
private:
	bool bTimerActivated = false;

	TSubclassOf<UActorComponent> MeshComponentClass = UStaticMeshComponent::StaticClass();
};
