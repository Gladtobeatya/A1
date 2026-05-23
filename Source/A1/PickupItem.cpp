// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"

#include "InventoryComponent.h"
#include "PlayerCharacter1.h"

void APickupItem::OnInteract_Implementation(ABaseCharacter* Interactor)
{
	Super::OnInteract_Implementation(Interactor);
	UE_LOG(LogTemp, Warning, TEXT("before check dynamic"));
	if (const APlayerCharacter1* Character = dynamic_cast<APlayerCharacter1*>(Interactor))
	{
		UE_LOG(LogTemp, Warning, TEXT("after dynamic cst"));
		Character->InventoryComponent->AddItem(this->ItemData);
	}
	
}
