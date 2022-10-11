#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class PAYLOADERS_TEST_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings")
	float RunningSpeed = 620.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Settings")
	class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(BlueprintReadOnly)
	float DefaultMaxWalkSpeed;

	UPROPERTY(BlueprintReadOnly)
	float DefaultMaxWalkSpeedCrouched;

	UPROPERTY(BlueprintReadOnly)
	float DefaultMaxAcceleration;

	UPROPERTY(BlueprintReadOnly)
	float DefaultMaxFlySpeed;

	UPROPERTY(BlueprintReadOnly)
	float DefaultMaxSwimSpeed;

protected:
	UPROPERTY(BlueprintReadWrite)
	class AEnemyController* EnemyController;
};
