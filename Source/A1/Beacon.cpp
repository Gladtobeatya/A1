// Fill out your copyright notice in the Description page of Project Settings.


#include "Beacon.h"

#include "OxygenProviderComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ABeacon::ABeacon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	BeaconLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("BeaconLight"));
	BeaconLight->SetupAttachment(Root);
	BeaconLight->SetIntensity(10000.f);
	BeaconLight->SetRelativeLocation(FVector(0, 0, 120.f)); 
	BeaconLight->SetLightColor(FColor(0, 210, 255));
	BeaconLight->SetAttenuationRadius(1000.f);
	BeaconLight->CastShadows = false; 

	// 2. SPOT LIGHT (Le projecteur abyssal)
	// On le place LÉGÈREMENT EN-DESSOUS de la sphère
	DownwardBeam = CreateDefaultSubobject<USpotLightComponent>(TEXT("DownwardBeam"));
	DownwardBeam->SetupAttachment(Root);
	//Under the beacon
	DownwardBeam->SetRelativeLocation(FVector(0, 0, -60.f));
	//Oriented downward
	DownwardBeam->SetRelativeRotation(FRotator(-90, 0, 0));
	DownwardBeam->SetIntensity(20000.f);
	DownwardBeam->SetOuterConeAngle(35.f);
	DownwardBeam->SetAttenuationRadius(3000.f);
	DownwardBeam->SetVolumetricScatteringIntensity(3.0f); 

	OxygenProvider = CreateDefaultSubobject<UOxygenProviderComponent>(TEXT("OxygenProvider"));
	
	InteractionText = NSLOCTEXT("BeaconNamespace", "TerminalDefault", "Accéder au terminal");
}

// Called when the game starts or when spawned
void ABeacon::BeginPlay()
{
	Super::BeginPlay();
}

void ABeacon::MoveToTargetZSmoothly(float DeltaTime)
{
	if (bIsMoving)
	{
		FVector CurrentLoc = GetActorLocation();

		//Where classic interp would bring us
		float IdealNextZ = FMath::FInterpTo(CurrentLoc.Z, TargetZ, DeltaTime, Smoothness);

		//Calc the movespeed we would be at
		float DesiredDelta = IdealNextZ - CurrentLoc.Z;
		float DesiredSpeed = DesiredDelta / DeltaTime;

		//Make sure we won't go too fast
		float ClampedSpeed = FMath::Clamp(DesiredSpeed, -MaxDescentSpeed, MaxDescentSpeed);
		
		float FinalNextZ = CurrentLoc.Z + (ClampedSpeed * DeltaTime);

		SetActorLocation(FVector(CurrentLoc.X, CurrentLoc.Y, FinalNextZ));

		// Stop
		if (FMath::IsNearlyEqual(FinalNextZ, TargetZ, 1.0f))
		{
			bIsMoving = false;
			SetActorTickEnabled(false);
			UE_LOG(LogTemp, Warning, TEXT("Beacon ARRIVED to %f"), TargetZ);
		}
	}
}

// Called every frame
void ABeacon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToTargetZSmoothly(DeltaTime);
}

// Called to bind functionality to input
void ABeacon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABeacon::OnInteract_Implementation(ABaseCharacter* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction with the beacon!"));
}

FText ABeacon::GetInteractionFullText_Implementation()
{
	return InteractionText;
}

void ABeacon::SetTargetDepth(float NewDepth)
{
	bIsMoving = true;
	TargetZ = NewDepth;
	UE_LOG(LogTemp, Warning, TEXT("Beacon SHOULD MOVE to %f"), TargetZ);
}

