// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"

// Sets default values
ABaseInteractable::ABaseInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	if (ItemData && Mesh && ItemData->Mesh)
	{
		Mesh->SetStaticMesh(ItemData->Mesh);
	}
}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseInteractable::OnInteract_Implementation(ABaseCharacter* Interactor)
{
	IInteractable::OnInteract_Implementation(Interactor);
	UE_LOG(LogTemp, Display, TEXT("%s"), *GetInteractionFullText_Implementation().ToString());
}

FText ABaseInteractable::GetInteractionFullText_Implementation()
{
	//Priority : Override > Default > Empty
	FText Verb = !InteractionVerbOverride.IsEmpty() ? InteractionVerbOverride : ItemData ? ItemData->DefaultInteractionVerb : FText::GetEmpty();

	FText Name = ItemData ? ItemData->DisplayName : FText::GetEmpty();

	return FText::Format(NSLOCTEXT("Interaction", "FullTextFormat", "{0} {1}"), Verb, Name);
}

void ABaseInteractable::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (Mesh && ItemData && ItemData->Mesh)
	{
		Mesh->SetStaticMesh(ItemData->Mesh);
	}
}

