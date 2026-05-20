// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharRocketLauncher.h"

#include "HomingMissile.h"
#include "Targetable.h"

AEnemyCharRocketLauncher::AEnemyCharRocketLauncher()
{
	bNextLeft = true;
	Target = nullptr;
}

void AEnemyCharRocketLauncher::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharRocketLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharRocketLauncher::LaunchMissile()
{
	if (!IsValid(Target))
		return;
	FVector StartLocation = GetActorLocation();
	StartLocation.Z += 300;
	const FRotator TargetDirection = GetMissileSpawnDirection().Rotation();
	AHomingMissile* Test =  GetWorld()->SpawnActor<AHomingMissile>(MissileClass, StartLocation, TargetDirection);
	Test->SetTargetComponent(Target);
}

FVector AEnemyCharRocketLauncher::GetMissileSpawnDirection()
{
	FVector MissileSpawnDirection = FVector(0, 0, 0);

	//Get direction to target
	FVector ToTarget = (Target->GetComponentLocation() - GetActorLocation()).GetSafeNormal();

	FVector SideVector = FVector::CrossProduct(ToTarget, FVector::UpVector);
	if (SideVector.SizeSquared() < KINDA_SMALL_NUMBER) {
		// ToTarget is parallel to Up, choose a fallback Up
		SideVector = FVector::CrossProduct(ToTarget, FVector(1,0,0));
	}
	SideVector.Normalize();
	
	//Vecteur orthogonal dans le plan perpendiculaire à ToTarget, orthogonal à SideVector
	FVector Ortho = FVector::CrossProduct(SideVector, ToTarget).GetSafeNormal();
	
	// Angle par rapport à la cible (60-80°)
	float ThetaDeg = FMath::RandRange(60.f, 80.f);
	float Theta = FMath::DegreesToRadians(ThetaDeg);

	float phi = bNextLeft ? PI : 0.0f; // alternate left/right
	bNextLeft = !bNextLeft;
	
	//small noise
	phi += FMath::RandRange(-0.1f, 0.1f);


	constexpr int MaxAttempts = 6;
	for (int i = 0; i < MaxAttempts; ++i) {
		MissileSpawnDirection = FMath::Sin(Theta) * FMath::Cos(phi) * SideVector
		  + FMath::Sin(Theta) * FMath::Sin(phi) * Ortho
		  + FMath::Cos(Theta) * ToTarget;
		MissileSpawnDirection.Normalize();
		if (FVector::DotProduct(MissileSpawnDirection, FVector::UpVector) > 0.0f)
			break; //Direction is in the half superior sphere so its valid
			
		// try slightly flipping phi to get upward component
		phi += PI/8.0f;
	}
	//Making sure we get something going up even if the tries failed before, less accurate but is ok =)
	MissileSpawnDirection.Z = FMath::Abs(MissileSpawnDirection.Z);
	return MissileSpawnDirection;
}

void AEnemyCharRocketLauncher::SetTarget(AActor* TargetOwner)
{
	if (IsValid(TargetOwner) && TargetOwner->Implements<UTargetable>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is valid"));
		Target = ITargetable::Execute_GetHomingTargetComponent(TargetOwner);
		UE_LOG(LogTemp, Warning, TEXT("Scenecomponent status : %hs"), IsValid(Target) ? "OK" : "KO" );
	}
}

USceneComponent* AEnemyCharRocketLauncher::GetTarget()
{
	return Target;
}
