// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

#include "BaseEnemyAIController.h"
#include "EnemyManager.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	AIControllerClass = ABaseEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel1);
}

void ABaseEnemyCharacter::RegisterToManager()
{
	if (AEnemyManager::Instance)
	{
		AEnemyManager::Instance->AddEnemy(this);
	}
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	RegisterToManager();
}

void ABaseEnemyCharacter::Update(float DeltaTime) const
{
	if (ABaseEnemyAIController* EnemyController = Cast<ABaseEnemyAIController>(GetController()))
	{
		EnemyController->Update(DeltaTime);
	}
}

EEnemyState ABaseEnemyCharacter::GetCurrentState() const
{
	return CurrentState;
}

void ABaseEnemyCharacter::Freeze(float Duration)
{
	CurrentState = EEnemyState::Frozen;
	if (ABaseEnemyAIController* EnemyController = Cast<ABaseEnemyAIController>(GetController()))
	{
		EnemyController->SetState(EEnemyState::Frozen);
		EnemyController->StopMovement();
		GetWorldTimerManager().SetTimer(TimerHandle_Unfreeze, this, &ABaseEnemyCharacter::Unfreeze, Duration, false);
	}
}

void ABaseEnemyCharacter::Unfreeze()
{
	CurrentState = EEnemyState::Idle;
	if (ABaseEnemyAIController* EnemyController = Cast<ABaseEnemyAIController>(GetController()))
	{
		EnemyController->SetState(CurrentState);
	}
}

void ABaseEnemyCharacter::SetSelfCollision(const ECollisionResponse NewResponse) const
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, NewResponse);
}
