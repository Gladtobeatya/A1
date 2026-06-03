// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventoryComponent.h"
void UInventoryWidget::InitializeInventory(class UInventoryComponent* NewInventory)
{
	InventoryReference = NewInventory;
	if (InventoryReference)
	{
		InventoryReference->OnInventoryChanged.AddDynamic(this, &UInventoryWidget::RefreshInventoryUI);
	}
	RefreshInventoryUI();
}
