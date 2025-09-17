// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MIGameMode.h"
#include "Character/MIMegaMikeCharacter.h"

AMIGameMode::AMIGameMode()
{
	DefaultPawnClass = AMIMegaMikeCharacter::StaticClass();

}
