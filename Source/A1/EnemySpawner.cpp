// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "BaseEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// No tick
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnAllGroups();
	UE_LOG(LogTemp, Warning, TEXT("EnemySpawner: %d ENEMIES TO SPAWN"), TotalEnemiesToSpawn);
}

void AEnemySpawner::SpawnAllGroups()
{
	UE_LOG(LogTemp, Warning, TEXT("EnemySpawner: SpawnAllgr!"));
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn || !EnemyClass) return;

	const FVector PlayerLocation = PlayerPawn->GetActorLocation();
	//Number of groups we need to spawn, ceil to int to cover the "modulo", cast to float so not truncated
	const int32 NumGroups = FMath::CeilToInt(static_cast<float>(TotalEnemiesToSpawn) / EnemiesPerGroup);

	for (int32 i = 0; i < NumGroups; i++)
	{
		const int32 Remaining = TotalEnemiesToSpawn - (i * EnemiesPerGroup);
		const int32 AmountToSpawn = FMath::Min(Remaining, EnemiesPerGroup);
		SpawnGroup(AmountToSpawn, PlayerLocation);
	}
}

void AEnemySpawner::SpawnGroup(int32 Amount, const FVector& PlayerLocation)
{
	for (int32 i  = 0; i < Amount; i++)
	{
		//Random pos around player
		const float Radius = FMath::RandRange(SpawnRadiusMin, SpawnRadiusMax);
		const float Angle = FMath::RandRange(0.f, 2* PI);

		FVector SpawnOffset(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, 0.f);
		FVector SpawnLocation = PlayerLocation + SpawnOffset;

		//Adjust height based on ground
		FHitResult Hit;
		FVector Start = SpawnLocation + FVector(0, 0, 500.f);
		FVector End = SpawnLocation + FVector(5000, 0, 1000.f);
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
		{
			SpawnLocation = Hit.ImpactPoint;
		}

		FRotator SpawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

