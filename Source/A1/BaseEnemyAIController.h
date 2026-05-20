// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyTypes.h"
#include "BaseEnemyAIController.generated.h"

class ABaseEnemyCharacter;
/**
 * 
 */
UCLASS()
class A1_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void Update(float DeltaTime);
	void SetState(EEnemyState NewState);
	virtual void OnPossess(APawn* NewPawn) override;

private:
	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY()
	ABaseEnemyCharacter* ControlledEnemy;
	
	EEnemyState CurrentState;
	bool bIsClimbing = false;
	
};
