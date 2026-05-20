// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerDefault.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class A1_API APlayerControllerDefault : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

};
