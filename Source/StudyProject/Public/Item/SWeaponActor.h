// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeaponActor.generated.h"

class UAnimMontage;
class UAnimInstance;

UCLASS()
class STUDYPROJECT_API ASWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASWeaponActor();

	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	UAnimMontage* GetMeleeAttackMontage() const { return MeleeAttackMontage; }

	TSubclassOf<UAnimInstance> GetUnarmedCharacterAnimLayer() const { return UnarmedCharacterAnimLayer; }

	TSubclassOf<UAnimInstance> GetArmedCharacterAnimLayer() const { return ArmedCharacterAnimLayer; }

	UAnimMontage* GetEquipAnimMontage() const { return EquipAnimMontage; }

	UAnimMontage* GetUnequipAnimMontage() const { return UnequipAnimMontage; }

	float GetMaxRange() const { return MaxRange; }

	UAnimMontage* GetRifleFireAnimMontage() const { return RifleFireAnimMontage; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> MeleeAttackMontage;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASWeaponActor|AnimLayer", meta = (AllowPrivateAccess))
	TSubclassOf<UAnimInstance> UnarmedCharacterAnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASWeaponActor|AnimLayer", meta = (AllowPrivateAccess))
	TSubclassOf<UAnimInstance> ArmedCharacterAnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> EquipAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> UnequipAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess, Units = cm))
	float MaxRange = 25000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> RifleFireAnimMontage;

};
