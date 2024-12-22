// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class ASWeaponActor;
class USpringArmComponent;
class USStatComponent;
class UStudyWidget;

UCLASS()
class STUDYPROJECT_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

	friend class UAN_CheckHit;

public:

	USStatComponent* GetStatComponent() const { return StatComponent; }

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetWidget(UStudyWidget* InStudyWidget) {}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UFUNCTION()
	virtual void OnRep_WeaponInstance() {}



public:
	
	ASCharacter();

	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UFUNCTION()
	void OnMeleeAttackMontageEnded(UAnimMontage* InMontage, bool bInterruped);

	UFUNCTION()
	void OnCheckHit();

	virtual void BeginAttack(); 

	UFUNCTION()
	void OnCheckAttackInput();

	UFUNCTION()
	virtual void EndAttack(UAnimMontage* InMontage, bool bInterruped);

	UFUNCTION()
	void OnCharacterDeath();

public:
	static int32 ShowAttackDebug;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TSubclassOf<ASWeaponActor> WeaponClass;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<ASWeaponActor> WeaponInstance;

	bool bIsNowAttacking = false;

	FString AttackAnimMontageSectionName = FString(TEXT("Attack"));

	int32 MaxComboCount = 3;

	int32 CurrentComboCount = 0;

	bool bIsAttackKeyPressed = false;

	FOnMontageEnded OnMeleeAttackMontageEndedDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float MeleeAttackRange = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float MeleeAttackRadius = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<USStatComponent> StatComponent;
};
