// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// Called by the player to pass inventory to the widget
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitializeInventory(class UInventoryComponent* NewInventory);

	//For BP usage
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnInventoryInitialized();
	
	// Which inventory to display 
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* InventoryReference;
};
