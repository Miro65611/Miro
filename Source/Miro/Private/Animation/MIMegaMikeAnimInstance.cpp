// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MIMegaMikeAnimInstance.h"
#include "Character/MIMegaMikeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMIMegaMikeAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwningPawn = TryGetPawnOwner();
	if (OwningPawn)
	{
		if (AMIMegaMikeCharacter* Character = Cast<AMIMegaMikeCharacter>(OwningPawn))
		{
			FVector Velocity = Character->GetVelocity();
			FVector Foward = Character->GetActorForwardVector();
			FVector Right = Character->GetActorRightVector();
			float MaxSpeed = Character->GetMaxDashSpeed();
			
			if (MaxSpeed > 0.f)
			{
				FowardSpeedRatio = Foward.Dot(Velocity) / MaxSpeed;
				RightSpeedRatio = Right.Dot(Velocity) / MaxSpeed;
			}

			bIsJumping = Character->IsJumping();
		}
	}

}
