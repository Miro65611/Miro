// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MIGameMode.h"
#include "Character/MIMegaMikeCharacter.h"
#include "Miro/Miro.h"
#include "Game/MIGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Props/MIGoalPoint.h"
#include "EngineUtils.h"

AMIGameMode::AMIGameMode()
{
	DefaultPawnClass = AMIMegaMikeCharacter::StaticClass();

	bUseSeamlessTravel = true;
}

void AMIGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::InitGame(MapName, Options, ErrorMessage);
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMIGameMode::StartPlay()
{
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::StartPlay();
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("End"));



}

void AMIGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AMIGoalPoint> Iter(GetWorld()); Iter; ++Iter)
	{
		Iter->OnNextStageButtonPressed.AddUObject(this, &AMIGameMode::HandleStageClear);
	}
}

void AMIGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("End"));

}

APlayerController* AMIGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("Begin"));
	APlayerController* PlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	MI_LOG(LogMINetwork, Log, TEXT("%s %s"), *NewPlayer->GetName(), *PlayerController->GetName());
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("End"));

	return PlayerController;
}

void AMIGameMode::PostLogin(APlayerController* NewPlayer)
{
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostLogin(NewPlayer);
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMIGameMode::Logout(AController* Exiting)
{
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::Logout(Exiting);
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMIGameMode::HandleDisconnect(UWorld* InWorld, UNetDriver* NetDriver)
{
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::HandleDisconnect(InWorld, NetDriver);
	MI_LOG(LogMINetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMIGameMode::Tick(float DeltaSeconds)
{
	AMIGameState* MiroGameState = GetGameState<AMIGameState>();

	if (MiroGameState)
	{
	}


}

void AMIGameMode::GoNextStage()
{
	//	UGameplayStatics::OpenLevel(this, FName("Lobby"), true);

	// TODO : 게임 레벨 종료 추가


	ProcessServerTravel(TEXT("Lobby"), true);
}

void AMIGameMode::HandleStageClear()
{
	GoNextStage();
}


