// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LifeSupportWidget.generated.h"

/**
 * 
 */
UCLASS()
class A1_API ULifeSupportWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Called by the player to pass the component to the widget
	UFUNCTION(BlueprintCallable, Category = "Survival")
	void InitializeLifeSupport(class ULifeSupportComponent* InLSC);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Survival")
	float OxygenPercent;

	UPROPERTY(BlueprintReadOnly, Category = "Survival")
	float HealthPercent;

	// For BP usage
	UFUNCTION(BlueprintImplementableEvent, Category = "Survival")
	void OnOxygenUpdated();

	// For BP usage
	UFUNCTION(BlueprintImplementableEvent, Category = "Survival")
	void OnHealthUpdated();

	// Callbacks
	UFUNCTION()
	void HandleOxygenChanged(float Current, float Max);
	UFUNCTION()
	void HandleHealthChanged(float Current, float Max);
};
