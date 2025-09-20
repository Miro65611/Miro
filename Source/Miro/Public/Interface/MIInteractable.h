// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MIInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMIInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 캐릭터와 상호작용 가능한 인터페이스
 */
class MIRO_API IMIInteractable
{
	GENERATED_BODY()

public:
	/// <summary>
	/// 현재 상호작용 가능한지 확인
	/// </summary>
	virtual bool CanInteractable()const abstract;

	/// <summary>
	/// 상호작용시에 호출하는 함수
	/// </s
	/// ummary>
	virtual void OnInteract(AActor* InstigatorActor) abstract;
	
	/// <summary>
	/// 상호작용 이펙트 시작 
	/// </summary>
	virtual void OnHighlightBegin(AActor* InstigatorActor) abstract;

	/// <summary>
	/// 상호작용 이펙트 끝
	/// </summary>
	virtual void  OnHighlightEnd(AActor* InstigatorActor) abstract;
};
