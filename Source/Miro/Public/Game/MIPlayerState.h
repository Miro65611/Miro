// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MIPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MIRO_API AMIPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMIPlayerState();

public:
	virtual void Tick(float DeltaSeconds) override;

};
