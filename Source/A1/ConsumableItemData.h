// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "ConsumableItemData.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UConsumableItemData : public UItemData
{
	GENERATED_BODY()
public:
	UConsumableItemData(){ ItemType = EItemType::Consumable; }
};
