// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class A1_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	class ULifeSupportWidget* LifeSupportWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	class UInventoryWidget* InventoryWidget;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	class UInteractionWidget* InteractionWidget;
	
};
