// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SCharacter.h"
#include "Character/SPlayerCharacter.h"
#include "SNonPlayerCharacter.generated.h"


class UAnimMontage;
class USWidgetComponent;

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASNonPlayerCharacter : public ASCharacter
{
	GENERATED_BODY()

	friend class UBTTask_Attack;


public:
	ASNonPlayerCharacter();

	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetWidget(UStudyWidget* InStudyWidget) override;

protected:
	virtual void BeginAttack() override;

	virtual void EndAttack(UAnimMontage* InMontage, bool bInterruped) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> MeleeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USWidgetComponent> WidgetComponent;
};
