// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeSupportWidget.h"
#include "LifeSupportComponent.h"
void ULifeSupportWidget::InitializeLifeSupport(ULifeSupportComponent* InLSC)
{
	if (InLSC)
	{
		InLSC->OnOxygenChanged.AddDynamic(this, &ULifeSupportWidget::HandleOxygenChanged);
		InLSC->OnHealthChanged.AddDynamic(this, &ULifeSupportWidget::HandleHealthChanged);
        
	}
}

void ULifeSupportWidget::HandleOxygenChanged(float Current, float Max)
{
	OxygenPercent = Current / Max;
	OnOxygenUpdated();
}

void ULifeSupportWidget::HandleHealthChanged(float Current, float Max)
{
	HealthPercent = Current / Max;
	OnHealthUpdated();
}
