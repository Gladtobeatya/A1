// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"

#include "InteractorComponent.h"

void UInteractionWidget::InitializeInteraction(class UInteractorComponent* Interactor)
{
	if (Interactor)
	{
		Interactor->OnFocusChanged.AddDynamic(this, &UInteractionWidget::HandleFocusChanged);
	}
}

void UInteractionWidget::HandleFocusChanged(AActor* NewActor)
{
	FocusedActor = NewActor;
	OnFocusedActorChanged();
}
