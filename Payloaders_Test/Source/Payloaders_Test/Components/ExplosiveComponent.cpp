// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveComponent.h"

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

UExplosiveComponent::UExplosiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UExplosiveComponent::SpawnParticles()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplosionParticle,GetOwner()->GetActorLocation()+ OffsetSpawnParticles, FRotator::ZeroRotator, ScaleParticles);
}

void UExplosiveComponent::Detonate()
{
	SpawnParticles();
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	for(int i = 0; i < CollisionChannels.Num(); i++)
	{
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(CollisionChannels[i]));
	}
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	
	TArray<AActor*> OutActors;
	TArray<AActor*> ActorsToIgnore;
	
	if(!GetOwner())
		return;

	ActorsToIgnore.Add(GetOwner());
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(),GetOwner()->GetActorLocation(), ExplosionRange, ObjectTypes, ExplosionFilterClass, ActorsToIgnore, OutActors);
	
	for(int i = 0; i < OutActors.Num(); i++)
	{
		if(OutActors[i])
		{
			if(auto* HealthComponent = Cast<UHealthComponent>(OutActors[i]->GetComponentByClass(UHealthComponent::StaticClass())))
			{
				AController* Controller = nullptr;
				if(auto* Pawn = Cast<APawn>(GetOwner()))
				{
					Controller = Pawn->GetController();
				}
				HealthComponent->OnTakeDamage(OutActors[i], ExplosionDamage, DamageType.GetDefaultObject(), Controller,GetOwner());
			}

			TArray<UActorComponent*> Components;
			OutActors[i]->GetComponents(UStaticMeshComponent::StaticClass(),Components);

			for(UActorComponent* Component : Components)
			{
				if(auto* MeshComp = Cast<UStaticMeshComponent>(Component))
				{
					MeshComp->AddRadialImpulse(GetOwner()->GetActorLocation(), ExplosionRange, ExplosionImpulse,ERadialImpulseFalloff::RIF_Constant, true);
				}
			}
		}
	}

	OnFinishExplosion.Broadcast();
}

void UExplosiveComponent::ActivateTimerToDetonate()
{
	if(GetWorld() && !bTimerActivated)
	{
		bTimerActivated = true;
		GetWorld()->GetTimerManager().SetTimer(TimerToDetonate,this, &UExplosiveComponent::Detonate, DelayToDetonate, false);
	}
}

void UExplosiveComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	
	if(GetWorld())
		GetWorld()->GetTimerManager().ClearTimer(TimerToDetonate);
}



