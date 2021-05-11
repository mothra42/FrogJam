// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FrogProjectile.generated.h"

UCLASS()
class FROGJAM_API AFrogProjectile : public AActor
{
	GENERATED_BODY()
	
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed = 1200.f;

public:	
	// Sets default values for this actor's properties
	AFrogProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
