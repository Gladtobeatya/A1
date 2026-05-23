// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true"))
	FText DisplayName = INVTEXT("Item name");
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true"))
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true"))
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true", MultiLine = true))
	FText TooltipText = INVTEXT("Item tooltip");;

	// "Casser", "Ramasser", "Ouvrir.."
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FText DefaultInteractionVerb = INVTEXT("Verb");;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess="true"))
	int32 MaxStackSize = 5;
};
