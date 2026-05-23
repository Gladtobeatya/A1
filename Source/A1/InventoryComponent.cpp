// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemData.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	Content.SetNum(MaxTotalCapacity);
}

int32 UInventoryComponent::AddItem(UItemData* Item, int32 Quantity)
{
	int32 Remaining = Quantity;
	if (!Item || Quantity <= 0) return Remaining;

	//Fill existing stacks
	for (FInventorySlot& Slot : Content)
	{
		if (Slot.ItemData && Slot.ItemData == Item)
		{
			if (Slot.CurrentQuantity < Slot.ItemData->MaxStackSize)
			{
				const int32 ToAdd = FMath::Min(Slot.ItemData->MaxStackSize - Slot.CurrentQuantity, Remaining);
				Slot.CurrentQuantity += ToAdd;
				Remaining -= ToAdd;
				if (Remaining <= 0) break;
			}
		}
	}
	//Then fill empty slots
	for (FInventorySlot& Slot : Content)
	{
		if (Slot.ItemData == nullptr)
		{
			Slot.ItemData = Item;
			const int32 ToAdd = FMath::Min(Item->MaxStackSize, Remaining);
			Slot.CurrentQuantity = ToAdd;
			Remaining -= ToAdd;
			if (Remaining <= 0) break;
		}
	}
	return Remaining;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

