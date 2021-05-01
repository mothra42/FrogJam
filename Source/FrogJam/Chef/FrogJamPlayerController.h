// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrogJamPlayerController.generated.h"

UCLASS()
class AFrogJamPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFrogJamPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName JumpBinding;
	static const FName AttackBinding;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	virtual void PlayerJump();
	virtual void PlayerAttack();

	//three types of attack depending on state
	void SwingNet(class AFrogJamCharacter* Chef);

	void UseTongue(AFrogJamCharacter* Chef);

	void SpitToad(AFrogJamCharacter* Chef);
};


