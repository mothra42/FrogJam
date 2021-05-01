// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrogJamPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "FrogJamCharacter.h"
#include "Engine/World.h"

const FName AFrogJamPlayerController::MoveForwardBinding("MoveForward");
const FName AFrogJamPlayerController::MoveRightBinding("MoveRight");
const FName AFrogJamPlayerController::JumpBinding("Jump");
const FName AFrogJamPlayerController::AttackBinding("Attack");

AFrogJamPlayerController::AFrogJamPlayerController()
{
	bShowMouseCursor = false;
}

void AFrogJamPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis(MoveForwardBinding);
	InputComponent->BindAxis(MoveRightBinding);
	InputComponent->BindAction(JumpBinding, IE_Pressed, this, &AFrogJamPlayerController::PlayerJump);
	InputComponent->BindAction(AttackBinding, IE_Pressed, this, &AFrogJamPlayerController::PlayerAttack);
}

void AFrogJamPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	AFrogJamCharacter* Chef = Cast<AFrogJamCharacter>(GetPawn());

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	// Calculate  movement
	const FVector Movement = MoveDirection * Chef->MoveSpeed * DeltaTime;

	FVector PlayerVelocity = MoveDirection * Chef->MoveSpeed;
	//
	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		UCharacterMovementComponent* CharacterMovement = Chef->GetCharacterMovement();
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		CharacterMovement->AddInputVector(Movement, true);
	
		//This is here so that the ship can move even if it is hitting a wall or other object
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			CharacterMovement->AddInputVector(Deflection, true);
		}
	}

}

void AFrogJamPlayerController::PlayerJump()
{
	AFrogJamCharacter* Chef = Cast<AFrogJamCharacter>(GetPawn());
	if (Chef->CanJump())
	{
		Chef->Jump();
	}
}

void AFrogJamPlayerController::PlayerAttack()
{
	AFrogJamCharacter* Chef = Cast<AFrogJamCharacter>(GetPawn());
	//attack is three state
	UseTongue(Chef);
	//base state
	//swing net
	if (Chef->GetCharacterTransformState() == ECharacterTransformState::NoTransform)
	{
		SwingNet(Chef);
	}
	//transformed state
	else if (Chef->GetCharacterTransformState() == ECharacterTransformState::Transformed)
	{
		//use tongue
		UseTongue(Chef);
	}
	//boss fight state
	else if (Chef->GetCharacterTransformState() == ECharacterTransformState::FinalBossFight)
	{
		//spit out toads
		SpitToad(Chef);
	}
}

void AFrogJamPlayerController::SwingNet(AFrogJamCharacter* Chef)
{
	//play animation of swinging net

	//rotate hitbox around character while spinning
	Chef->SwingNet();
	
}

void AFrogJamPlayerController::UseTongue(AFrogJamCharacter* Chef)
{
	Chef->UseTongue();
}

void AFrogJamPlayerController::SpitToad(AFrogJamCharacter* Chef)
{
	Chef->SpitToad();
}



