// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Pawn.h"
#include "Beacon.generated.h"

class UOxygenProviderComponent;
class UPointLightComponent;
class USpotLightComponent;

UCLASS()
class A1_API ABeacon : public APawn, public IInteractable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ABeacon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UOxygenProviderComponent* OxygenProvider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPointLightComponent* BeaconLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpotLightComponent* DownwardBeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractionText;

	//Max speed in unit/sec
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxDescentSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Smoothness = 2.0f;

	void MoveToTargetZSmoothly(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void OnInteract_Implementation(ABaseCharacter* Interactor) override;
	
	virtual FText GetInteractionFullText_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void SetTargetDepth(float NewDepth);
	
private:
	float TargetZ;
	bool bIsMoving;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DescentSpeed = 150.f;
};
