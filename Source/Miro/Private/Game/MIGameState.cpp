// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MIGameState.h"
#include "Net/UnrealNetwork.h"

AMIGameState::AMIGameState()
{
}

void AMIGameState::Tick(float DeltaSeconds)
{
	
}

void AMIGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMIGameState, bIsClearStage);
}
