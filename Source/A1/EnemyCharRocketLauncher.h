// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyCharacter.h"
#include "EnemyCharRocketLauncher.generated.h"

class AHomingMissile;
/**
 * 
 */
UCLASS()
class A1_API AEnemyCharRocketLauncher : public ABaseEnemyCharacter
{
	GENERATED_BODY()
public:
	AEnemyCharRocketLauncher();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Missile")
	TSubclassOf<AHomingMissile> MissileClass;

	UFUNCTION(BlueprintCallable)
	void LaunchMissile();

	//Alternate left right
	bool bNextLeft;

	FVector GetMissileSpawnDirection();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Target;

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* TargetOwner);

	UFUNCTION(BlueprintCallable)
	USceneComponent* GetTarget();
};
