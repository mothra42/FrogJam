// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Chef/FrogJamCharacter.h"
#include "Amphibian.generated.h"

UCLASS()
class FROGJAM_API AAmphibian : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAmphibian();

	//projectile Type
	UPROPERTY(Category = Projectile, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AFrogProjectile> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//damage that amphibian applies to player
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float DamageValue = 10.f;
	//tongue length for determining if attack hits
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float TongueLength = 100.f;

public:	
	//value that affects how many points needed for transformation
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float TransformationValue = 10.f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndLife();

	void ChangeCharacterDirection(float RightValue, float ForwardValue);

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ECharacterDirection CharacterDirection = ECharacterDirection::South;
};
