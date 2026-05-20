// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class ABaseEnemyCharacter;

UCLASS()
class A1_API AEnemyManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ABaseEnemyCharacter*> Enemies;

	/*Since we are batching on Enemies in tick function, we need a temporary array to store new enemies before we
	start ticking them to note mess up the code */
	UPROPERTY()
	TArray<ABaseEnemyCharacter*> NewEnemies;
	
	int32 CurrentBatchStart = 0;
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

	//How many enemies we update each frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Manager")
	int32 EnemiesPerTick = 1001;

	UFUNCTION()
	void AddEnemy(ABaseEnemyCharacter* Enemy);

	// Singleton global
	static AEnemyManager* Instance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
