// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MICharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "InputActionValue.h"
#include "Interface/MIInteractable.h"


// Sets default values
AMICharacter::AMICharacter()
{
	PrimaryActorTick.bCanEverTick = true;


	bReplicates = true;

	SetReplicatingMovement(true);

	bAlwaysRelevant = true;

	// Camera Setup
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AMICharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMICharacter, bOnDashInput);
	DOREPLIFETIME(AMICharacter, CurrentEnergy);
	DOREPLIFETIME(AMICharacter, bIsEnergyDischarged);
}

void AMICharacter::BeginPlay()
{
	Super::BeginPlay();

	BeginStatus();
}

void AMICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DetectInteractableObject();

	UpdateMaxWalkSpeed();
	UpdateStatus(DeltaTime);

	// Debug
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (PlayerController->IsInputKeyDown(EKeys::P))
		{
			CurrentEnergy = MaxEnergy;
		}
	}
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

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMICharacter::Interact);

	}
	else
	{

	}

}

void AMICharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), -MovementVector.X);
	}
}

void AMICharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

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

void AMICharacter::Interact()
{
	if (NearestInteractableObject)
	{
		NearestInteractableObject->OnInteract(this);
	}
}

void AMICharacter::UpdateMaxWalkSpeed()
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = bOnDashInput ? MaxDashSpeed : MaxWalkSpeed;
}

void AMICharacter::Server_SetDashInput_Implementation(bool bIsOnDashInput)
{
	bOnDashInput = bIsOnDashInput;
}

void AMICharacter::BeginStatus()
{
	if (HasAuthority())
	{
		CurrentEnergy = MaxEnergy;
	}
}

void AMICharacter::UpdateStatus(float DeltaTime)
{
	if (HasAuthority())
	{
		const float DecreaseEnergy = DecreaseEnergyPerSecond * DeltaTime;
		CurrentEnergy = FMath::Max(CurrentEnergy - DecreaseEnergy, 0.f);

		// �������� ����
		if (!bIsEnergyDischarged && CurrentEnergy <= 0.f)
		{
			bIsEnergyDischarged = true;
			OnRep_bIsEnergyDischarged();
		}

		// �������� ����
		if (bIsEnergyDischarged && CurrentEnergy > 0.f)
		{
			bIsEnergyDischarged = false;
			OnRep_bIsEnergyDischarged();
		}
	}
}


void AMICharacter::OnRep_bIsEnergyDischarged()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (!IsLocallyControlled() || PlayerController == nullptr)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		return;
	}

	// �Է� ���ε� ����
	if (bIsEnergyDischarged)
	{
		Subsystem->RemoveMappingContext(DefaultMappingContext);
	}
	else
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

}

void AMICharacter::DetectInteractableObject()
{
	// ĳ������ �ü�(ī�޶�) ��ġ�� ������ �����ɴϴ�.
	FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndLocation = StartLocation + FirstPersonCameraComponent->GetComponentRotation().Vector() * InteractableDistance;

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, TraceParams);

	IMIInteractable* InteractableActor = Cast<IMIInteractable>(HitResult.GetActor());

	if (bHit && InteractableActor && InteractableActor->CanInteractable())
	{
		NearestInteractableObject = InteractableActor;
	}
	else
	{
		NearestInteractableObject = nullptr;
	}

	if (NearestInteractableObject)
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 0.0f, 0, 1.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.0f, 0, 1.0f);
	}

}











