// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class A1_API ABaseInteractable : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractable();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess="true"))
	UItemData* ItemData;

	//In case we need other than default Verb
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	FText InteractionVerbOverride;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation(ABaseCharacter* Interactor) override;

	virtual FText GetInteractionFullText_Implementation() override;

	// Called when we change a variable in editor
	virtual void OnConstruction(const FTransform& Transform) override;

};
