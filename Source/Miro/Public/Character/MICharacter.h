// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MICharacter.generated.h"


class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class MIRO_API AMICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMICharacter();

protected:
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnDashInput();
	void OffDashInput();

	UFUNCTION(Server, Unreliable)
	void Server_SetDashInput(bool bIsOnDashInput);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float MaxDashSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float MaxWalkSpeed = 200.f;

	UPROPERTY(Replicated)
	bool bOnDashInput = false;

	void UpdateMaxWalkSpeed();

public:
	float GetMaxDashSpeed()const { return MaxDashSpeed; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	float MaxEnergy = 100.f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	float CurrentEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	float DecreaseEnergyPerSecond = 10.f;

	void BeginStatus();

	void UpdateStatus(float DeltaTime);

private:
	UPROPERTY(ReplicatedUsing = OnRep_bIsEnergyDischarged)
	bool bIsEnergyDischarged = false;

protected:
	UFUNCTION()
	virtual void OnRep_bIsEnergyDischarged();


public:
	bool IsEnergyDischarged()const { return bIsEnergyDischarged; }

	UFUNCTION(BlueprintCallable, Category = "Status")
	float GetCurrentEnergy()const { return CurrentEnergy; }

};
