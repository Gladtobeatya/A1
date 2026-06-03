// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeSupportComponent.h"

#include "PlayerCharacter1.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
ULifeSupportComponent::ULifeSupportComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULifeSupportComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentOxygen = MaxOxygen;
	CurrentHealth = MaxHealth;
	
	OnOxygenChanged.Broadcast(CurrentOxygen, MaxOxygen);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
	
	CachedOwnerChar = Cast<APlayerCharacter1>(GetOwner());
}

void ULifeSupportComponent::UpdateHeadSubmerged()
{
	
	if (!CachedOwnerChar || !CachedOwnerChar->GetOxygenSensor()) return;
	
	APhysicsVolume* CurrentVol = CachedOwnerChar->GetOxygenSensor()->GetPhysicsVolume();
	bIsHeadSubmerged = CurrentVol && CurrentVol->bWaterVolume;
}

// Called every frame
void ULifeSupportComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Oxygen
	UpdateHeadSubmerged();

	if (!bIsHeadSubmerged || bIsInOxygenZone)
	{
		AddOxygen(10.0f * DeltaTime);
	}
	else
	{
		AddOxygen(-1.0f * OxygenDepletionRate * DeltaTime);
	}


	// Pressure
	const float CurrentDepth = FMath::Abs(GetOwner()->GetActorLocation().Z) / 100.0f;
	const bool bIsTooDeep = CurrentDepth > MaxPressureDepth;

	// Apply damage
	if (CurrentOxygen <= 0.0f)
	{
		TakeDamage(SuffocationDamageRate * DeltaTime);
	}
    
	if (bIsTooDeep)
	{
		TakeDamage(PressureDamageRate * DeltaTime);
	}
}

void ULifeSupportComponent::TakeDamage(const float Amount)
{
	const float PreviousHealth = CurrentHealth;
	CurrentHealth = FMath::Max(0.0f, CurrentHealth - Amount);
	// Give info only when value changed (for UI)
	if (PreviousHealth != CurrentHealth) {
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
	}
	if (CurrentHealth <= 0.0f) {
		// death logic (Broadcast, Respawn, etc.)
	}
}

void ULifeSupportComponent::AddOxygen(const float Amount)
{
	const float PreviousOxygen = CurrentOxygen;
	if (Amount >= 0)
	{
		CurrentOxygen = FMath::Min(MaxOxygen, CurrentOxygen + Amount);
	}
	else
	{
		CurrentOxygen = FMath::Max(0.0f, CurrentOxygen + Amount);	
	}
	
	// Give info only when integer changed (for UI)
	if (PreviousOxygen != CurrentOxygen) {
		OnOxygenChanged.Broadcast(CurrentOxygen, MaxOxygen);
	}
}

void ULifeSupportComponent::Heal(const float Amount)
{
	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + Amount);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void ULifeSupportComponent::AddMaxPressure(const float Amount)
{
	MaxPressureDepth += Amount;
}

void ULifeSupportComponent::AddMaxOxygen(const float Amount)
{
	MaxOxygen += Amount;
	AddOxygen(Amount);
}
