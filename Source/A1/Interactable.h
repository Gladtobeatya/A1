// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class A1_API IInteractable
{
	GENERATED_BODY()

public:
	//BlueprintNativeEvent = default implementation in c++, and can be overriden in blueprint
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(class ABaseCharacter* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractionFullText();

	//BlueprintImplementableEvent = only blueprint can implement it
	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void SetFocused();
};
