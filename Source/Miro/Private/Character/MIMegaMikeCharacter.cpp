// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MIMegaMikeCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"


AMIMegaMikeCharacter::AMIMegaMikeCharacter()
{
	// 캡슐컴포넌트 설정
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->InitCapsuleSize(10.f, 60.0f);

	// 카메라 설정
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// 메쉬 설정
	USkeletalMeshComponent* Mesh3P = GetMesh();
	Mesh3P->SetOwnerNoSee(true);
	Mesh3P->SetupAttachment(Capsule);

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetupAttachment(Mesh3P);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;


}

void AMIMegaMikeCharacter::BeginPlay()
{
	Super::BeginPlay();

	RelativeMeshTransform = GetMesh()->GetRelativeTransform();
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

		// 1. 충돌 설정
		//Mesh3P->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		Mesh3P->SetSimulatePhysics(true);
		Mesh3P->SetCollisionProfileName(TEXT("Ragdoll"));

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

		// 2. 카메라 설정


	}
	else
	{
		Mesh1P->SetVisibility(true);

		// 1. 충돌 설정
		Mesh3P->SetSimulatePhysics(false);
		Mesh3P->SetCollisionProfileName(TEXT("CharacterMesh"));

		UCapsuleComponent* Capsule = GetCapsuleComponent();

		const FVector MeshPosition = Mesh3P->GetComponentTransform().GetTranslation();
		const FVector RagdollOffset{ 0.f,0.f,Capsule->GetUnscaledCapsuleHalfHeight() };
		const FVector AddPosition = MeshPosition + RagdollOffset;

		Mesh3P->SetRelativeTransform(RelativeMeshTransform);
		Capsule->SetWorldLocation(AddPosition);

		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);


		// 2. 카메라 설정

	}

}

