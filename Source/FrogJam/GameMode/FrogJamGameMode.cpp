// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrogJamGameMode.h"
#include "../Chef/FrogJamPlayerController.h"
#include "../Chef/FrogJamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"

AFrogJamGameMode::AFrogJamGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFrogJamPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Chef/Behavior/Chef"));
	//if (PlayerPawnBPClass.Class != nullptr)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void AFrogJamGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void AFrogJamGameMode::EndGame()
{
	bIsGameWon = false;
	UGameplayStatics::OpenLevel(GetWorld(), FName("EndScreen"));
}