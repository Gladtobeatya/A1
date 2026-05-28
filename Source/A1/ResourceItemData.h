// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "ResourceItemData.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UResourceItemData : public UItemData
{
	GENERATED_BODY()
public:
	UResourceItemData(){ ItemType = EItemType::Resource; }
};
