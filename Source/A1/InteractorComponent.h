// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFocusChangedDelegate, AActor*, NewFocusedActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class A1_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractorComponent();

	//For BP
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AActor* GetFocusedActor() const { return FocusedActor; }

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FFocusChangedDelegate OnFocusChanged;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void TraceForInteractables();

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditAnywhere)
	float TraceDistance = 300.f;

	UPROPERTY(EditAnywhere)
	float TraceRadius = 15.f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
