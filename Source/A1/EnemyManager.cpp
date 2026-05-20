// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "BaseEnemyCharacter.h"

//Definition for linker
AEnemyManager* AEnemyManager::Instance = nullptr;

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Global ref
	Instance = this;
}

void AEnemyManager::AddEnemy(ABaseEnemyCharacter* Enemy)
{
	if (IsValid(Enemy))
	{
		NewEnemies.Add(Enemy);
	}
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("EnemyManager NewEnemies : %d & Enemies : %d"), NewEnemies.Num(), Enemies.Num());
	if (Enemies.Num() == 0 && NewEnemies.Num() == 0) return;

	if (CurrentBatchStart == 0)
	{
		// Add new enemies before starting batch
		if (NewEnemies.Num() > 0)
		{
			Enemies.Append(NewEnemies);
			NewEnemies.Empty();
		}
	}
	
	int32 End = FMath::Min(CurrentBatchStart + EnemiesPerTick, Enemies.Num());

	for (int32 i = CurrentBatchStart; i < End; i++)
	{
		ABaseEnemyCharacter* Enemy = Enemies[i];
		if (!IsValid(Enemy)) continue;

		//UE_LOG(LogTemp, Warning, TEXT("EnemyManager call update"));
		Enemy->Update(DeltaTime);
	}

	// Update batch start for next tick
	CurrentBatchStart = End >= Enemies.Num() ? 0 : End;
}

