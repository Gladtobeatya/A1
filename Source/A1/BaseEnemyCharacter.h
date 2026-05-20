// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyTypes.h"
#include "BaseEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class A1_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseEnemyCharacter();
	
private:
	UFUNCTION()
	void RegisterToManager();

	EEnemyState CurrentState;
	FTimerHandle TimerHandle_Unfreeze;
	bool bIsBumped = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/*Called by Manager in its tick*/
	void Update(float DeltaTime) const;
	EEnemyState GetCurrentState() const;
	void Freeze(float Duration = 1.5f);
	void Unfreeze();
	void SetSelfCollision(ECollisionResponse NewResponse) const;
	UPROPERTY(BlueprintReadWrite)
	bool bCanMove = true;
	
};
