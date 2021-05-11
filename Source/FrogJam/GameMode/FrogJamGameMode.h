// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FrogJamGameMode.generated.h"

UCLASS(minimalapi)
class AFrogJamGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AFrogJamGameMode();

	FTimerHandle GameLengthTimerHandle;

	float DefaultGameLength = 300.f;

	void EndGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameOver")
	bool bIsGameWon = false;
};



