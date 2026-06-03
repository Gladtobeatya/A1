// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeSupportComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, float, CurrentValue, float, MaxValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class A1_API ULifeSupportComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULifeSupportComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStatChangedDelegate OnOxygenChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStatChangedDelegate OnHealthChanged;
	
	void TakeDamage(const float Amount);
	
	UFUNCTION(BlueprintCallable)
	void AddOxygen(const float Amount);

	UFUNCTION(BlueprintCallable)
	void Heal(const float Amount);

	UFUNCTION(BlueprintCallable)
	void AddMaxPressure(const float Amount);

	UFUNCTION(BlueprintCallable)
	void AddMaxOxygen(const float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void UpdateHeadSubmerged();
	
	bool bIsHeadSubmerged = false;
	
	//Owner won't change during the game, so we get it one time instead of doing it every frame
	UPROPERTY()
	class APlayerCharacter1* CachedOwnerChar;
	
	//Oxygen
	UPROPERTY(EditAnywhere)
	float MaxOxygen = 100.0f;
	
	float CurrentOxygen;
	bool bIsInWater = false;
	
	UPROPERTY(EditAnywhere)
	float OxygenDepletionRate = 1.0f;
	
	//Health	
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;
	
	float CurrentHealth;
	
	UPROPERTY(EditAnywhere)
	float SuffocationDamageRate = 5.0f;

	//Pressure
	UPROPERTY(EditAnywhere)
	float MaxPressureDepth = 80.0f;
	
	UPROPERTY(EditAnywhere)
	float PressureDamageRate = 5.0f;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Is player in a oxygen zone ?
	UPROPERTY(BlueprintReadWrite, Category = "Oxygen")
	bool bIsInOxygenZone = false;
};
