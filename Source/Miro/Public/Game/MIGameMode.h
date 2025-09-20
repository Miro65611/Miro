// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MIGameMode.generated.h"

/**
 * MiroGameMode
 */
UCLASS()
class MIRO_API AMIGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMIGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void BeginPlay() override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void HandleDisconnect(UWorld* InWorld, UNetDriver* NetDriver) override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	/// <summary>
	/// 다음 스테이지로 이동할때 호출
	/// </summary>
	virtual void GoNextStage();

public:
	virtual void HandleStageClear();
};
