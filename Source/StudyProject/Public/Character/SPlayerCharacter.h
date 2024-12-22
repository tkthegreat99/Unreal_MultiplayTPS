// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SCharacter.h"
#include "InputActionValue.h"
#include "Game/SPlayerState.h"
#include "SPlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USInputConfig;
class UInputMappingContext;
class UAnimMontage;
class UParticleSystemComponent;
struct FStreamableHandle;
class UMaterial;

UENUM(BlueprintType)
enum class EViewMode : uint8
{
	None,
	BackView,
	QuarterView,
	TPSView,
	End
};



/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASPlayerCharacter : public ASCharacter
{
	GENERATED_BODY()
	
public:

	UParticleSystemComponent* GetParticleSystem() const { return ParticleSystemComponent; }

public:

	ASPlayerCharacter();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaSeconds) override;

	void SetViewMode(EViewMode InViewMode);

	float GetForwardInputValue() const { return ForwardInputValue; }

	float GetRightInputValue() const { return RightInputValue; }

	float GetCurrentAimPitch() const { return CurrentAimPitch; }

	float GetCurrentAimYaw() const { return CurrentAimYaw; }

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetMeshMaterial(const EPlayerTeam& InPlayerTeam);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	void InputMove(const FInputActionValue& InValue);
	void InputLook(const FInputActionValue& InValue);
	void InputChangeView(const FInputActionValue& InValue);
	void InputQuickSlot01(const FInputActionValue& InValue);
	void InputQuickSlot02(const FInputActionValue& InValue);
	void InputAttack(const FInputActionValue& InValue);
	void InputMenu(const FInputActionValue& InValue);
	void StartIronSight(const FInputActionValue& InValue);
	void EndIronSight(const FInputActionValue& InValue);
	void ToggleTrigger(const FInputActionValue& InValue);
	void StartFire(const FInputActionValue& InValue);
	void StopFire(const FInputActionValue& InValue);
	void SpawnLandMine(const FInputActionValue& InValue);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USInputConfig> PlayerCharacterInputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> PlayerCharacterInputMappingContext;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float ForwardInputValue;

	float PreviousForwardInputValue = 0.f;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float RightInputValue;

	float PreviousRightInputValue = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UCameraShakeBase> FireShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> LandMineClass;

	UPROPERTY()
	TSubclassOf<UAnimInstance> UnarmedCharacterAnimLayer;

	UPROPERTY()
	TObjectPtr<UAnimMontage> UnequipAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterial> BlackMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterial> WhiteMaterial;


protected:

	EViewMode CurrentViewMode = EViewMode::None;

	FVector DirectionToMove = FVector::ZeroVector;

	float DestArmLength = 0.f;

	float ArmLengthChangeSpeed = 3.f;

	FRotator DestArmRotation = FRotator::ZeroRotator;

	float ArmRotationChangeSpeed = 10.f;

	FSoftObjectPath CurrentPlayerCharacterMeshMaterialPath = FSoftObjectPath();

	TSharedPtr<FStreamableHandle> AssetStreamableHandle = nullptr;

	float TargetFOV = 70.f;

	float CurrentFOV = 70.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float FirePerMinute = 1200;

	bool bIsTriggerToggle = false;

	FTimerHandle BetweenShotsTimer;

	float TimeBetweenFire;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float CurrentAimPitch = 0.f;

	float PreviousAimPitch = 0.f;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float CurrentAimYaw = 0.f;

	float PreviousAimYaw = 0.f;

	float TargetRagDollBlendWeight = 0.f;

	float CurrentRagDollBlendWeight = 0.f;

	bool bIsNowRagdollBlending = false;

	FTimerHandle HittedRagdollRestoreTimer;

	FTimerDelegate HittedRagdollRestoreTimerDelegate;



private:
	void TryFire();

	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnLandMine_Server();

	UFUNCTION(Server, Reliable)
	void SpawnWeaponInstance_Server();

	UFUNCTION(Server, Reliable)
	void DestroyWeaponInstance_Server();

	virtual void OnRep_WeaponInstance();

	UFUNCTION(Server, Unreliable)
	void UpdateInputValue_Server(const float& InForwardInputValue, const float& InRightInputValue);

	UFUNCTION(Server, Unreliable)
	void UpdateAimValue_Server(const float& InAimPitchValue, const float& InAimYawValue);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;

	UFUNCTION()
	void OnHittedRagdollRestoreTimerElapsed();

	UFUNCTION(Server, Unreliable)
	void PlayAttackMontage_Server();

	UFUNCTION(NetMulticast, Unreliable)
	void PlayAttackMontage_NetMulticast();

	UFUNCTION(Server, Reliable)
	void ApplyDamageAndDrawLine_Server(FHitResult HitResult);

	UFUNCTION(NetMulticast, Reliable)
	void DrawLine_NetMulticast(const FVector& InDrawStart, const FVector& InDrawEnd);

	UFUNCTION(NetMulticast, Unreliable)
	void PlayRagdoll_NetMulticast();
};
