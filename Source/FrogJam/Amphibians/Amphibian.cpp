// Fill out your copyright notice in the Description page of Project Settings.


#include "Amphibian.h"
#include "AmphibianAIController.h"
#include "../Chef/FrogJamCharacter.h"
#include "../Projectiles/FrogProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAmphibian::AAmphibian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAmphibian::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmphibian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentNormalizedVelocity = GetCharacterMovement()->Velocity.GetSafeNormal();
	ChangeCharacterDirection(CurrentNormalizedVelocity.Y, CurrentNormalizedVelocity.Y);
}

void AAmphibian::EndLife()
{
	AAmphibianAIController* MyController = Cast<AAmphibianAIController>(GetController());
	DetachFromControllerPendingDestroy();
	MyController->Destroy();
	Destroy();
}

void AAmphibian::ChangeCharacterDirection(float RightValue, float ForwardValue)
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
