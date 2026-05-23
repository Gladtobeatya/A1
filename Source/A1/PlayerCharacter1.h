// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Targetable.h"
#include "PlayerCharacter1.generated.h"

class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
/**
 * 
 */
UCLASS()
class A1_API APlayerCharacter1 : public ABaseCharacter, public ITargetable
{
	GENERATED_BODY()

	APlayerCharacter1();
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	// Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;
	
	/*Inputs*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* SecondaryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* ToggleMenuAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void Secondary();
	void ToggleMenu();
	/*End inputs */

	/*Abilities*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	USphereComponent* RepulseSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	UStaticMeshComponent* ShieldMesh;

	// Timer callback to deactivate sphere repulsion
	UFUNCTION()
	void DeactivateRepulseSphere();

	// Timer handle
	FTimerHandle RepulseTimerHandle;
	/*End abilities*/

	/*Targetable interface implementation*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Targetable")
	USceneComponent* HomingTarget;

	virtual USceneComponent* GetHomingTargetComponent_Implementation() override;
	/*End Targetable interface implementation*/

	// La classe du widget (à remplir dans le BP du perso)
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	// L'instance du widget une fois créé
	UPROPERTY()
	class UInventoryWidget* InventoryWidget;

	bool bIsInventoryOpen = false;
public:
	/*Inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;
	
	/*End inventory*/
};
