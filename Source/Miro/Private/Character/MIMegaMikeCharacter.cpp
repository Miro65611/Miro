// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MIMegaMikeCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"


AMIMegaMikeCharacter::AMIMegaMikeCharacter()
{
	// ĸ��������Ʈ ����
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->InitCapsuleSize(10.f, 60.0f);

	// ī�޶� ����
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// �޽� ����
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(Capsule);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	USkeletalMeshComponent* Mesh3P = GetMesh();
	Mesh3P->SetOwnerNoSee(true);
	Mesh3P->SetupAttachment(Capsule);

}

void AMIMegaMikeCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMIMegaMikeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMIMegaMikeCharacter, bIsJumping);
}

void AMIMegaMikeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMIMegaMikeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AMIMegaMikeCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	bIsJumping = true;
}

void AMIMegaMikeCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	bIsJumping = false;

	UE_LOG(LogTemp, Log, TEXT("Landed"));
}

void AMIMegaMikeCharacter::OnRep_bIsEnergyDischarged()
{
	Super::OnRep_bIsEnergyDischarged();
	USkeletalMeshComponent* Mesh3P = GetMesh();

	if (IsEnergyDischarged())
	{
		Mesh1P->SetVisibility(false);

		// 1. �浹 ����
		Mesh3P->SetSimulatePhysics(true);
		Mesh3P->SetCollisionProfileName(TEXT("Ragdoll"));

		//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetRootComponent(Mesh3P);

		// 2. ī�޶� ����

	}
	else
	{
		Mesh1P->SetVisibility(true);

		// 1. �浹 ����
		Mesh3P->SetSimulatePhysics(false);
		Mesh3P->SetCollisionProfileName(TEXT("CharacterMesh"));
		SetRootComponent(GetCapsuleComponent());


		//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		// 2. ī�޶� ����

	}

}

