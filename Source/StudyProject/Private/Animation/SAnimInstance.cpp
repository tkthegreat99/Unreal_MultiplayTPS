// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SAnimInstance.h"
#include "Character/SPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/SStatComponent.h"

USAnimInstance::USAnimInstance()
{
}

void USAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CurrentSpeed = 0.f;

	Velocity = FVector::ZeroVector;

	bIsFalling = false;

	bIsCrouching = false;
	
	bIsDead = false;
}

void USAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//UE_LOG(LogTemp, Log, TEXT("%s"), LocomotionState);

	ASCharacter* OwnerCharacter = Cast<ASCharacter>(TryGetPawnOwner());
	if (IsValid(OwnerCharacter) == true)
	{
		UCharacterMovementComponent* CharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
		if (IsValid(CharacterMovementComponent) == true)
		{
			Velocity = CharacterMovementComponent->GetLastUpdateVelocity();
			CurrentSpeed = Velocity.Size();
			bIsFalling = CharacterMovementComponent->IsFalling();
			bIsCrouching = CharacterMovementComponent->IsCrouching();
			bIsDead = OwnerCharacter->GetStatComponent()->GetCurrentHP() <= KINDA_SMALL_NUMBER;
			

			Acceleration = CharacterMovementComponent->GetCurrentAcceleration();

			if (Acceleration.Length() < KINDA_SMALL_NUMBER && Velocity.Length() < KINDA_SMALL_NUMBER)
			{
				LocomotionState = ELocomotionState::Idle;
			}
			else
			{
				LocomotionState = ELocomotionState::Walk;
			}
			
		}
		ASPlayerCharacter* OwnerPlayerCharacter = Cast<ASPlayerCharacter>(OwnerCharacter);
		if (IsValid(OwnerPlayerCharacter) == true) {

			//UE_LOG(LogTemp, Log, TEXT("valid"));

			if (KINDA_SMALL_NUMBER < OwnerPlayerCharacter->GetForwardInputValue())
			{
				MovementDirection = EMovementDirection::Fwd;
			}

			if (OwnerPlayerCharacter->GetForwardInputValue() < -KINDA_SMALL_NUMBER)
			{
				MovementDirection = EMovementDirection::Bwd;
			}

			if (KINDA_SMALL_NUMBER < OwnerPlayerCharacter->GetRightInputValue())
			{
				MovementDirection = EMovementDirection::Right;
			}

			if (OwnerPlayerCharacter->GetRightInputValue() < -KINDA_SMALL_NUMBER)
			{
				MovementDirection = EMovementDirection::Left;
			}
			ControlRotation.Pitch = OwnerPlayerCharacter->GetCurrentAimPitch();
			ControlRotation.Yaw = OwnerPlayerCharacter->GetCurrentAimYaw();
		}

		
	}
}

void USAnimInstance::PlayAnimMontage(UAnimMontage* InAnimMontage)
{
	checkf(IsValid(InAnimMontage) == true, TEXT("Invalid InAnimMontage"));

	if (Montage_IsPlaying(InAnimMontage) == false)
	{
		Montage_Play(InAnimMontage);
	}
}

void USAnimInstance::AnimNotify_CheckHit()
{
	if (OnCheckHit.IsBound() == true)
	{
		OnCheckHit.Broadcast();
	}
}

void USAnimInstance::AnimNotify_CheckAttackInput()
{
	if (OnCheckAttackInput.IsBound() == true)
	{
		OnCheckAttackInput.Broadcast();
	}
}
