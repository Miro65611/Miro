// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/MIInteractable.h"
#include "MIGoalPoint.generated.h"

class UBoxComponent;
class UPrimitiveComponent;

DECLARE_MULTICAST_DELEGATE(FOnNextStageButtonPressed);

/// <summary>
/// ¹Ì·Î °ñ ÁöÁ¡
/// </summary>
UCLASS()
class MIRO_API AMIGoalPoint : public AActor, public IMIInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMIGoalPoint();

	FOnNextStageButtonPressed OnNextStageButtonPressed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* PlayerCheckBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GoalPointMesh;

	UPROPERTY(Replicated)
	int32 PlayerCount;

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// IMIInteractable Interface
	virtual bool CanInteractable()const override;
	virtual void OnInteract(AActor* InstigatorActor) override;
	virtual void OnHighlightBegin(AActor* InstigatorActor) override;
	virtual void OnHighlightEnd(AActor* InstigatorActor) override;

};
