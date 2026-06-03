// Fill out your copyright notice in the Description page of Project Settings.


#include "OxygenProviderComponent.h"

#include "LifeSupportComponent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UOxygenProviderComponent::UOxygenProviderComponent()
{
	//No need for tick or init for now
	PrimaryComponentTick.bCanEverTick = false;

	OxygenZone = CreateDefaultSubobject<USphereComponent>(TEXT("OxygenZone"));
	OxygenZone->SetSphereRadius(OxygenZoneRadius);
	//Custom profile for trigger detection
	OxygenZone->SetCollisionProfileName(TEXT("Trigger"));
	// ...
}

// Called when the game starts
void UOxygenProviderComponent::BeginPlay()
{
	Super::BeginPlay();

	//We need to attach the sphere to the owner of this component. Can't do it in constructor
	if (GetOwner())
	{
		OxygenZone->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		
		//Delegate binds
		OxygenZone->OnComponentBeginOverlap.AddDynamic(this, &UOxygenProviderComponent::OnOverlapBegin);
		OxygenZone->OnComponentEndOverlap.AddDynamic(this, &UOxygenProviderComponent::OnOverlapEnd);
	}
	
}

void UOxygenProviderComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ULifeSupportComponent* LSC = OtherActor->FindComponentByClass<ULifeSupportComponent>();
		if (LSC)
		{
			LSC->bIsInOxygenZone = true;
		}
	}
}

void UOxygenProviderComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ULifeSupportComponent* LSC = OtherActor->FindComponentByClass<ULifeSupportComponent>();
		if (LSC)
		{
			LSC->bIsInOxygenZone = false;
		}
	}
}

