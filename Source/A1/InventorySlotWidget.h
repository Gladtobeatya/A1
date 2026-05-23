// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateSlot(FInventorySlot NewSlot);

protected:
	// For BP
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FInventorySlot SlotData;

	// Event to refresh visuals on BP side
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnSlotUpdated();
};
