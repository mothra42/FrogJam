// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FrogJamCharacter.generated.h"
//TODO add enum state to track transformation state
UENUM()
enum class ECharacterTransformState : uint8
{
	NoTransform,
	Transformed,
	FinalBossFight
};

UENUM(BlueprintType)
enum class ECharacterDirection : uint8
{
	North,
	Northwest,
	Northeast,
	East,
	West,
	South,
	Southwest,
	Southeast
};

UCLASS(Blueprintable)
class AFrogJamCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFrogJamCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MoveSpeed = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float JumpPower = 50.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Life")
	float Life = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Transformation")
	float TransformationLevel = 0.f;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ECharacterDirection CharacterDirection = ECharacterDirection::South;
	//projectile Type
	UPROPERTY(Category = Projectile, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AFrogProjectile> ProjectileClass;

	ECharacterTransformState GetCharacterTransformState();

	//attack functions that trigger blueprint events
	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void SwingNet();
	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void UseTongue();
	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void SpitToad();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void OnTransform(ECharacterTransformState NewTransformState);

	UFUNCTION(BlueprintCallable)
	float TakeDamage(float DamageToTake);

	UFUNCTION(BlueprintCallable)
	float ConsumeAmphibian(float TransformationValue, class AAmphibian* AmphibianToConsume);

	void ChangeCharacterDirection(float RightValue, float ForwardValue);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	ECharacterTransformState TransformState = ECharacterTransformState::NoTransform;
};

