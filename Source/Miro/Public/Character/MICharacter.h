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

	UPROPERTY(ReplicatedUsing = OnRep_SetDashInput)
	bool bOnDashInput = false;

	UFUNCTION()
	void OnRep_SetDashInput();

public:
	float GetMaxDashSpeed()const { return MaxDashSpeed; }

	// Status 
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	float MaxEnergy; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	float CurrentEnergy;

	void BeginStatus();
};
