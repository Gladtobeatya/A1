// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent.h"
#include "Interactable.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInteractorComponent::TraceForInteractables()
{
	// We make sure the pawn is controlled by the player
	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn || !OwnerPawn->IsLocallyControlled()) return;

	const APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
	if (!PC) return;

	FVector Location;
	FRotator Rotation;
	PC->GetPlayerViewPoint(Location, Rotation);

	const FVector End = Location + (Rotation.Vector() * TraceDistance);
    
	FHitResult Hit;

	//We use sphere so collision feels smoother
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(15.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	//ECC_GameTraceChannel3 = Interactable
	const bool bHit = GetWorld()->SweepSingleByChannel(Hit, Location, End, FQuat::Identity, ECC_GameTraceChannel3, Sphere, Params);

	AActor* HitActor = bHit ? Hit.GetActor() : nullptr;
	
	if (HitActor != FocusedActor)
	{
		//Unfocus previous object
		if (FocusedActor && FocusedActor->Implements<UInteractable>())
		{
			IInteractable::Execute_SetFocused(FocusedActor, false);
		}
		
		FocusedActor = HitActor;
		//Focus new object
		if (FocusedActor && FocusedActor->Implements<UInteractable>())
		{
			IInteractable::Execute_SetFocused(FocusedActor, true);
		}
		OnFocusChanged.Broadcast(FocusedActor);
	}
}


// Called every frame
void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TraceForInteractables();
	// ...
}

