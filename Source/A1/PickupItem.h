// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class A1_API APickupItem : public ABaseInteractable
{
	GENERATED_BODY()
public:
	virtual void OnInteract_Implementation(ABaseCharacter* Interactor) override;
};
