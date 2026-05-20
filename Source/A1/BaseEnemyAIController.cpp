// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyAIController.h"

#include "BaseEnemyCharacter.h"
#include "PlayerCharacter1.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void ABaseEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ABaseEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABaseEnemyAIController::Update(float DeltaTime)
{
	if (!IsValid(ControlledEnemy) || !ControlledEnemy->bCanMove)
		return;
		
	if (CurrentState != EEnemyState::Frozen)
	{
		auto* MoveComp = ControlledEnemy->GetCharacterMovement();
		FVector Start = ControlledEnemy->GetActorLocation() - FVector(0,0, ControlledEnemy->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		Start += FVector(0, 0, 10.0f);
		FVector End = Start + ControlledEnemy->GetActorForwardVector() * 60.f;

		FHitResult HitForward;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(ControlledEnemy);

		bool bHitForward = GetWorld()->LineTraceSingleByChannel(HitForward, Start, End, ECC_WorldStatic, Params);
		
		DrawDebugLine(GetWorld(), Start, End, bHitForward ? FColor::Red : FColor::Green, false, 0.f, 0, 2.f);
		if (bHitForward && HitForward.GetActor() && !HitForward.GetActor()->IsA(APlayerCharacter1::StaticClass()))
		{
			// On monte (fly activé le temps du climb)
			if (MoveComp->MovementMode != MOVE_Flying)
				MoveComp->SetMovementMode(MOVE_Flying);
			FVector ClimbDir = ControlledEnemy->GetActorForwardVector() + FVector(0, 0, 0.8f);
			ClimbDir.Normalize();
			ControlledEnemy->AddMovementInput(ClimbDir);
			// Direction vers le joueur
			FVector ToPlayer = PlayerPawn->GetActorLocation() - ControlledEnemy->GetActorLocation();
			ToPlayer.Z = 0.f;
			ToPlayer.Normalize();
			ControlledEnemy->SetActorRotation(ToPlayer.Rotation());
		}
		else
		{
			if (MoveComp->MovementMode == MOVE_Flying)
			{
				MoveComp->SetMovementMode(MOVE_Falling);
				MoveComp->Velocity.Z = 0.f;
			}
			else if (MoveComp->MovementMode == MOVE_Walking)
			{
				//UE_LOG(LogTemp, Warning, TEXT("collision before: %d"), (int32)ControlledEnemy->GetCapsuleComponent()->GetCollisionResponseToChannel(ECC_GameTraceChannel1));
				ControlledEnemy->SetSelfCollision(ECR_Block);
			}
			const FVector Direction = (PlayerPawn->GetActorLocation() - ControlledEnemy->GetActorLocation()).GetSafeNormal();        
			ControlledEnemy->AddMovementInput(Direction);
		}
	}
}

void ABaseEnemyAIController::SetState(const EEnemyState NewState)
{
	CurrentState = NewState;
}

void ABaseEnemyAIController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	ControlledEnemy = Cast<ABaseEnemyCharacter>(NewPawn);
}
