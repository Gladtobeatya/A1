// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ABaseEnemyCharacter;

UCLASS()
class A1_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<ABaseEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, Category="Spawning")
	int32 TotalEnemiesToSpawn = 400;

	UPROPERTY(EditAnywhere, Category="Spawning")
	int32 EnemiesPerGroup = 20;

	UPROPERTY(EditAnywhere, Category="Spawning")
	float SpawnRadiusMin = 700.f;

	UPROPERTY(EditAnywhere, Category="Spawning")
	float SpawnRadiusMax = 1600.f;

	void SpawnAllGroups();
	void SpawnGroup(const int32 Amount, const FVector& PlayerLocation);
};
