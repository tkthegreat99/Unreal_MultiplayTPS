// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfCurrentHPDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentHPChangeDelegate, float, InOldCurrentHP, float, InNewCurrentHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxHPChangeDelegate, float, InOldMaxHP, float, InNewMaxHP);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUDYPROJECT_API USStatComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UFUNCTION(NetMulticast, Reliable)
	void OnCurrentHPChanged_NetMulticast(float InOldCurrentHP, float InNewCurrentHP);

public:	
	USStatComponent();

	virtual void BeginPlay() override;

	float GetMaxHP() const { return MaxHP; }

	void SetMaxHP(float InMaxHP);

	float GetCurrentHP() const { return CurrentHP; }

	void SetCurrentHP(float InCurrentHP);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:
	FOnOutOfCurrentHPDelegate OnOutOfCurrentHPDelegate;

	FOnCurrentHPChangeDelegate OnCurrentHPChangedDelegate;

	FOnMaxHPChangeDelegate OnMaxHPChangedDelegate;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "USStatComponent", Meta = (AllowPrivateAccess))
	TObjectPtr<class USGameInstance> GameInstance;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadOnly, Category = "USStatComponent", Meta = (AllowPrivateAccess))
	float MaxHP;

	UPROPERTY(Replicated, Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "USStatComponent", Meta = (AllowPrivateAccess))
	float CurrentHP;

		
};
