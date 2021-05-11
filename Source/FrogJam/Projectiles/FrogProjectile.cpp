// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AFrogProjectile::AFrogProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	//ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

}

// Called when the game starts or when spawned
void AFrogProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFrogProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

