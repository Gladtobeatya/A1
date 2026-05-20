// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMissile.h"

#include "PlayerCharacter1.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AHomingMissile::AHomingMissile()
{	
	InitialSpeed = 600.f;
	FinalSpeed = 2400.f;
	TurnSpeed = 1.5f;
	LockDelay = 0.7f;
	ElapsedTime = 0.f;
	bIsLocked = true;
	LockTargetLocation = FVector::ZeroVector;
	TargetComponent = nullptr;
	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->MaxSpeed = FinalSpeed;
}

void AHomingMissile::BeginPlay()
{
	Super::BeginPlay();
	
	/*FTimerHandle SwitchTimerHandle;
	GetWorldTimerManager().SetTimer(SwitchTimerHandle, this, &AHomingMissile::SwitchToPlayerHoming, LockDelay);*/
}

void AHomingMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(TargetComponent))
	{
		return;
	}
	// elapsedTime depuis le lancement
	
	ElapsedTime += DeltaTime;

	// facteur de vitesse 0..1 selon easing
	float t = FMath::Clamp(ElapsedTime / 3.0f, 0.f, 1.f);
	float SpeedFactor = 0.5f * (1 - FMath::Cos(PI * t)); // easeInOutSine

	// applique la vitesse sur le ProjectileMovementComponent
	/*if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() 
									   * FinalSpeed * SpeedFactor;
	}*/
	float Alpha = FMath::Clamp(ElapsedTime / 5.0f, 0.f, 1.f); 
	ProjectileMovement->Velocity = FMath::InterpEaseInOut(
	ProjectileMovement->Velocity,
	ProjectileMovement->Velocity.GetSafeNormal() * FinalSpeed,
	Alpha,
	1.0f
);
	Alpha = FMath::Clamp(ElapsedTime / 2.0f, 0.f, 1.f); 
	ProjectileMovement->MaxSpeed = FMath::InterpEaseInOut(
	ProjectileMovement->InitialSpeed,
	FinalSpeed,
	Alpha,
	1.0f
);
	ProjectileMovement->HomingAccelerationMagnitude = FMath::InterpEaseInOut(5000.0f, 2000.0f, Alpha, 2.0f);
	/*ProjectileMovement->HomingAccelerationMagnitude = FMath::FInterpTo(5000, 
ProjectileMovement->HomingAccelerationMagnitude,
2000,
DeltaTime,
1
);*/

	UE_LOG(LogTemp, Warning, TEXT("Current Velocity : %f"), ProjectileMovement->Velocity.Size());
}

void AHomingMissile::SwitchToPlayerHoming()
{
	//ProjectileMovement->HomingTargetComponent = TargetComponent;
	//UE_LOG(LogTemp, Warning, TEXT("Homing valid ? %hs"), ProjectileMovement->HomingTargetComponent.Get() ? "YES" : "NO");
	/*if (const APlayerCharacter1* PlayerCharacter = Cast<APlayerCharacter1>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		FVector PlayerCenter = PlayerCharacter->GetActorLocation();
		//PlayerCenter.Z += PlayerCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
		TargetActor->SetActorLocation(PlayerCenter);
		UE_LOG(LogTemp, Warning, TEXT("Switchtarget ITS VALID"));
		bIsLocked = true;
	}*/

}

void AHomingMissile::SetTargetComponent(USceneComponent* NewTargetComponent)
{
	TargetComponent = NewTargetComponent;
	ProjectileMovement->HomingTargetComponent = TargetComponent;
}

USceneComponent* AHomingMissile::GetTargetComponent()
{
	return TargetComponent;
}
