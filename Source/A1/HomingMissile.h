// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "HomingMissile.generated.h"

/**
 * 
 */
UCLASS()
class A1_API AHomingMissile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	AHomingMissile();

	protected :

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float InitialSpeed;

	UPROPERTY(EditAnywhere)
	float FinalSpeed;
	
	UPROPERTY(EditAnywhere)
	float TurnSpeed;

	//In seconds
	UPROPERTY(EditAnywhere)
	float LockDelay;

	float ElapsedTime;

	//Target location after LockDelay
	UPROPERTY()
	FVector LockTargetLocation;

	UPROPERTY()
	bool bIsLocked = false;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* TargetComponent;

	UPROPERTY(VisibleAnywhere, Category="Transform", meta=(MakeEditWidget=true))
	FVector GizmoInitialTargetLocation;
	
	void SwitchToPlayerHoming();

public :
	UFUNCTION(BlueprintCallable)
	void SetTargetComponent(USceneComponent* NewTargetComponent);
	
	UFUNCTION(BlueprintCallable)
	USceneComponent* GetTargetComponent();
	
};
