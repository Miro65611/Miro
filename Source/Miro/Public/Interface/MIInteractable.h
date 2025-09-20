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
 * ĳ���Ϳ� ��ȣ�ۿ� ������ �������̽�
 */
class MIRO_API IMIInteractable
{
	GENERATED_BODY()

public:
	/// <summary>
	/// ���� ��ȣ�ۿ� �������� Ȯ��
	/// </summary>
	virtual bool CanInteractable()const abstract;

	/// <summary>
	/// ��ȣ�ۿ�ÿ� ȣ���ϴ� �Լ�
	/// </s
	/// ummary>
	virtual void OnInteract(AActor* InstigatorActor) abstract;
	
	/// <summary>
	/// ��ȣ�ۿ� ����Ʈ ���� 
	/// </summary>
	virtual void OnHighlightBegin(AActor* InstigatorActor) abstract;

	/// <summary>
	/// ��ȣ�ۿ� ����Ʈ ��
	/// </summary>
	virtual void  OnHighlightEnd(AActor* InstigatorActor) abstract;
};
