// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MICharacter.h"
#include "MIMegaMikeCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;

/**
 * MegaMike Mesh Ä³¸¯ÅÍ 
 */
UCLASS()
class MIRO_API AMIMegaMikeCharacter : public AMICharacter
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AMIMegaMikeCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	USkeletalMeshComponent* GetMesh3P() { return Mesh1P; }	

protected:
	UPROPERTY(Replicated,BlueprintReadOnly, Category = "Animation")
	bool bIsJumping;

public:
	virtual void OnJumped_Implementation() override;
	virtual void Landed(const FHitResult& Hit) override;

	bool IsJumping()const { return bIsJumping; }

protected:
	virtual void OnRep_bIsEnergyDischarged() override;

private: 
	FTransform RelativeMeshTransform;


};
