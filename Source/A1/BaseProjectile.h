// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class A1_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnImpact(AActor* OtherActor);

};
