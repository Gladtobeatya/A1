// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void InitializeInteraction(class UInteractorComponent* Interactor);

protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	AActor* FocusedActor;

	//We use that to update visuals in BP
	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnFocusedActorChanged();

private:

	UFUNCTION()
	void HandleFocusChanged(AActor* NewActor);
};
