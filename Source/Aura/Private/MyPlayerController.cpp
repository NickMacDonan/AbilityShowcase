// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/ApplicationCore/Public/GenericPlatform/ICursor.h"
#include "../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/Engine/Classes/Engine/EngineBaseTypes.h"
#include "../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Interaction/EnemyInterface.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AMyPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	
	/**
	 * Line trace from cursor. There are several scenarios
	 * A. LastActor is null and ThisActor is null
	 * - Do nothing
	 * B. LastActor is null and ThisActor is not null
	 * - Call highlight on this actor
	 * C. LastActor is not null and ThisActor is null
	 * - UnHighlight LastActor
	 * D. Both are valid, but LastActor != ThisActor
	 * - UnHighlight LastActor, Highlight ThisActor
	 * E. Both actors are valid and are the same
	 * - Do nothing
	 */
	if(LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//Case B
			ThisActor->HighlightActor();
		} else
		{
			//Case A
			
		}
	}
	else //LastActor Valid
	{
		if (ThisActor == nullptr)
		{
			//Case C
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				//Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//Case E
			}
		}
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);
}

void AMyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(FVector::ForwardVector, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(FVector::RightVector, InputAxisVector.X);
	}
}


