// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter1.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseEnemyCharacter.h"
#include "Interactable.h"
#include "InteractionWidget.h"
#include "InteractorComponent.h"
#include "InventoryComponent.h"
#include "ItemData.h"
#include "MainHUDWidget.h"
#include "InventoryWidget.h"
#include "LifeSupportComponent.h"
#include "LifeSupportWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

APlayerCharacter1::APlayerCharacter1()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	// Camera distance from character
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create the camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Only the spring arm is pivoting, not the camera
	FollowCamera->bUsePawnControlRotation = false;

	RepulseSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RepulseSphere"));
	RepulseSphere->SetupAttachment(RootComponent);
	RepulseSphere->SetSphereRadius(200.0f);
	//No collision by default
	RepulseSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
	RepulseSphere->SetCollisionResponseToAllChannels(ECR_Overlap);

	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	ShieldMesh->SetupAttachment(RootComponent);

	//No collision by default
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ShieldMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	HomingTarget = CreateDefaultSubobject<USceneComponent>(TEXT("HomingTarget"));
	HomingTarget->SetupAttachment(GetRootComponent());

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	LifeSupportComponent = CreateDefaultSubobject<ULifeSupportComponent>(TEXT("LifeSupportComponent"));
	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("InteractorComponent"));
	
	OxygenSensor = CreateDefaultSubobject<USphereComponent>(TEXT("OxygenSensor"));
	OxygenSensor->SetupAttachment(GetMesh(), FName("SK_Mouth"));
	OxygenSensor->SetSphereRadius(5.0f);
	OxygenSensor->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	OxygenSensor->SetGenerateOverlapEvents(true);
}

void APlayerCharacter1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		/*EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);*/

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter1::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter1::Look);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter1::Interact);

		// Secondary
		EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Started, this, &APlayerCharacter1::Secondary);

		// Toggle Menu
		EnhancedInputComponent->BindAction(ToggleMenuAction, ETriggerEvent::Started, this, &APlayerCharacter1::ToggleMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerCharacter1::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Lancement du composant sur %s (Adresse : %p)"), *GetOwner()->GetName(), this);
	if (AController* PC = GetController())
	{
		// Pitch/Yaw/Roll of the camera, because we can't default in viewport since it follow the player's inputs
		PC->SetControlRotation(FRotator(-40.f, 0.f, 0.f)); 
	}
	InitMainHudWidget();
}

void APlayerCharacter1::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter1::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter1::Interact()
{
	if (InteractorComponent)
	{
		AActor* FocusedActor = InteractorComponent->GetFocusedActor();
		if (FocusedActor && FocusedActor->Implements<UInteractable>())
		{
			IInteractable::Execute_OnInteract(FocusedActor, this);
		}
	}
	//OLD INTERACT!
	/*UE_LOG(LogTemp, Warning, TEXT("PLayerCharacter: BUMP TRIGGERED YAY!"));
	RepulseSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Display sphere if needed
	RepulseSphere->SetHiddenInGame(false);

	// Timer after which the sphere deactivate
	GetWorldTimerManager().SetTimer(
		RepulseTimerHandle,
		this,
		&APlayerCharacter1::DeactivateRepulseSphere,
		0.2f,
		false
	);

	TArray<AActor*> OverlappingActors;
	RepulseSphere->GetOverlappingActors(OverlappingActors, ABaseEnemyCharacter::StaticClass());
	FVector PlayerLocation = GetActorLocation();
	float MaxForce = 1500.f; 
	float MinForce = 500.f;  
	float Radius = RepulseSphere->GetScaledSphereRadius();

	for (AActor* Actor : OverlappingActors)
	{
		if (ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(Actor))
		{
			if (Enemy->GetCurrentState() == EEnemyState::Frozen)
			{
				FVector Direction = (Enemy->GetActorLocation() - PlayerLocation);
				float Distance = Direction.Size();
				Direction = Direction.GetSafeNormal();

				// Calculate force based of off distance
				float ForceMultiplier = FMath::Clamp(1.0f - (Distance / Radius), 0.f, 1.f);
				float LaunchStrength = FMath::Lerp(MinForce, MaxForce, ForceMultiplier);

				// Some heigth
				Direction.Z = 0.5f;
				//Disable collision while bumped so they don't bump on each other
				Enemy->SetSelfCollision(ECR_Ignore);
				Enemy->LaunchCharacter(Direction * LaunchStrength, true, true);
			}
		}
	}*/
}

void APlayerCharacter1::Secondary()
{
	//TODO remove, code is for testing purpose
	if (InventoryComponent)
	{
		for (const auto& [ItemData, CurrentQuantity] : InventoryComponent->Content)
		{
			if (ItemData)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *ItemData->DisplayName.ToString());
				
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Secondary triggered YAY!"));
	// Active collision 
	RepulseSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Visual display for debug
	RepulseSphere->SetHiddenInGame(false);

	// Timer to deactivate after .2sec
	GetWorldTimerManager().SetTimer(
		RepulseTimerHandle,
		this,
		&APlayerCharacter1::DeactivateRepulseSphere,
		0.2f,
		false
	);

	TArray<AActor*> OverlappingActors;
	RepulseSphere->GetOverlappingActors(OverlappingActors, ABaseEnemyCharacter::StaticClass());
	for (AActor* Actor : OverlappingActors)
	{
		if (ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(Actor))
		{
			Enemy->Freeze();
		}
	}
}

void APlayerCharacter1::ToggleMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("PLayerCharacter: Toggle menu"));
	if (!MainHUDWidget || !MainHUDWidget->InventoryWidget) return;
	UE_LOG(LogTemp, Warning, TEXT("PLayerCharacter: mainwidget class OK"));
	//Show inventory
	if (!bIsInventoryOpen)
	{
		MainHUDWidget->InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		
		// Configure mouse and input
		APlayerController* PC = Cast<APlayerController>(GetController());
		PC->SetInputMode(FInputModeGameAndUI());
		PC->bShowMouseCursor = true;
        
		bIsInventoryOpen = true;
	}
	//Hide inventory
	else
	{
		MainHUDWidget->InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
        
		APlayerController* PC = Cast<APlayerController>(GetController());
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
        
		bIsInventoryOpen = false;
	}
}

void APlayerCharacter1::DeactivateRepulseSphere()
{
	RepulseSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RepulseSphere->SetHiddenInGame(true);
}

USceneComponent* APlayerCharacter1::GetHomingTargetComponent_Implementation()
{
	return HomingTarget;
}

void APlayerCharacter1::InitMainHudWidget()
{
	// Creates Main HUD widget (UI) if we set the class in BP
	if (MainHUDWidgetClass)
	{
		MainHUDWidget = CreateWidget<UMainHUDWidget>(GetWorld(), MainHUDWidgetClass);
		if (MainHUDWidget)
		{
			MainHUDWidget->AddToViewport();
			if (MainHUDWidget->LifeSupportWidget)
			{
				MainHUDWidget->LifeSupportWidget->InitializeLifeSupport(LifeSupportComponent);
			}
			if (MainHUDWidget->InventoryWidget)
			{
				MainHUDWidget->InventoryWidget->InitializeInventory(InventoryComponent);
			}
			if (MainHUDWidget->InteractionWidget)
			{
				MainHUDWidget->InteractionWidget->InitializeInteraction(InteractorComponent);
			}
		}
	}
}

const USphereComponent* APlayerCharacter1::GetOxygenSensor() const
{
	return OxygenSensor;
}
