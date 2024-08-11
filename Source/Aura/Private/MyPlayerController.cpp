// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/ApplicationCore/Public/GenericPlatform/ICursor.h"
#include "../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/Engine/Classes/Engine/EngineBaseTypes.h"
#include "../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/Engine/Classes/GameFramework/PlayerController.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
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
