// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MIMegaMikeAnimInstance.generated.h"

/**
 * MegaMike
 */
UCLASS()
class MIRO_API UMIMegaMikeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	uint8 bIsJumping : 1;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float FowardSpeedRatio;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float RightSpeedRatio;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsEnergyDischarged;


};
