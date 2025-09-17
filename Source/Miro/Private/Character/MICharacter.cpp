// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MICharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMICharacter::AMICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// �� ���͸� ��Ʈ��ũ�� ���� ����(Replicate)�ϵ��� �����մϴ�.
	bReplicates = true;
	// �÷��̾� �Է¿� ���� ��Ʈ���� �����ϵ��� �����մϴ�.
	SetReplicatingMovement(true);
	// ������ �׻� �� ���͸� Ŭ���̾�Ʈ���� �����ϵ��� ����
	bAlwaysRelevant = true;
}

void AMICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMICharacter, bOnDashInput);
}

void AMICharacter::BeginPlay()
{
	Super::BeginPlay();

	BeginStatus();
}

void AMICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = bOnDashInput ? MaxDashSpeed : MaxWalkSpeed;
}


void AMICharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMICharacter::Move);

		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AMICharacter::OnDashInput);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &AMICharacter::OffDashInput);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMICharacter::Look);
	}
	else
	{

	}

}

void AMICharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), -MovementVector.X);
	}
}

void AMICharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void AMICharacter::OnDashInput()
{
	Server_SetDashInput(true);
}

void AMICharacter::OffDashInput()
{
	Server_SetDashInput(false);
}

void AMICharacter::Server_SetDashInput_Implementation(bool bIsOnDashInput)
{
	bOnDashInput = bIsOnDashInput;
}

void AMICharacter::OnRep_SetDashInput()
{
	if (bOnDashInput)
	{
		// ��� ���� ȿ�� (��: ����Ʈ, ����)
		GetCharacterMovement()->MaxWalkSpeed = MaxDashSpeed;
	}
	else
	{
		// ��� ���� ȿ�� (��: ����Ʈ ����, ����)
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}

}

void AMICharacter::BeginStatus()
{
	CurrentEnergy = MaxEnergy;
}







