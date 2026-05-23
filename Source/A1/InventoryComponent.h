// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"
class UItemData;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemData* ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentQuantity = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class A1_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	//Add item to the inventory. Returns the remaining quantity if any left
	int32 AddItem(UItemData* Item, int32 Quantity = 1);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FInventorySlot> Content;
	
	// Actual number of used slots (meaning content size)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 CurrentMaxCapacity = 20;
	
	// Max number of slots
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaxTotalCapacity = 20;
};
