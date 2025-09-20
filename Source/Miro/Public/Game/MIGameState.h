// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MIGameState.generated.h"


/**
 * ���� Ŭ���̾�Ʈ ���¸� �����Ѵ�
 */
UCLASS()
class MIRO_API AMIGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMIGameState();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

private:
	UPROPERTY(Replicated)
	bool bIsClearStage;

};
