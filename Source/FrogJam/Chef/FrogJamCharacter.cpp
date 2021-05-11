// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrogJamCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "../GameMode/FrogJamGameMode.h"
#include "../Amphibians/Amphibian.h"
#include "../Projectiles/FrogProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AFrogJamCharacter::AFrogJamCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AFrogJamCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

ECharacterTransformState AFrogJamCharacter::GetCharacterTransformState()
{
	return TransformState;
}

float AFrogJamCharacter::TakeDamage(float DamageToTake)
{
	Life -= DamageToTake;
	if (Life <= 0)
	{
		AFrogJamGameMode* GameMode = Cast<AFrogJamGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode != nullptr)
		{
			GameMode->EndGame();
		}
	}
	return Life;
}

float AFrogJamCharacter::ConsumeAmphibian(float TransformationValue, AAmphibian* AmphibianToConsume)
{
	TransformationLevel += TransformationValue;
	AmphibianToConsume->EndLife();

	//TODO encode these values in vars
	if (TransformationLevel >= 120.f && TransformState != ECharacterTransformState::FinalBossFight)
	{
		TransformState = ECharacterTransformState::FinalBossFight;
		OnTransform(TransformState);
	}
	else if (TransformationLevel >= 60.f && TransformState != ECharacterTransformState::FinalBossFight && TransformState != ECharacterTransformState::Transformed)
	{
		TransformState = ECharacterTransformState::Transformed;
		OnTransform(TransformState);
	}

	return TransformationLevel;
}

void AFrogJamCharacter::ChangeCharacterDirection(float RightValue, float ForwardValue)
{
	if (RightValue == 0 && ForwardValue > 0)
	{
		CharacterDirection = ECharacterDirection::North;
	}
	else if (RightValue > 0 && ForwardValue == 0)
	{
		CharacterDirection = ECharacterDirection::East;
	}
	else if (RightValue == 0 && ForwardValue < 0)
	{
		CharacterDirection = ECharacterDirection::South;
	}
	else if (RightValue < 0 && ForwardValue == 0)
	{
		CharacterDirection = ECharacterDirection::West;
	}
	else if (RightValue > 0 && ForwardValue > 0)
	{
		CharacterDirection = ECharacterDirection::Northeast;
	}
	else if (RightValue > 0 && ForwardValue < 0)
	{
		CharacterDirection = ECharacterDirection::Southeast;
	}
	else if (RightValue < 0 && ForwardValue < 0)
	{
		CharacterDirection = ECharacterDirection::Southwest;
	}
	else if (RightValue < 0 && ForwardValue > 0)
	{
		CharacterDirection = ECharacterDirection::Northwest;
	}
}
