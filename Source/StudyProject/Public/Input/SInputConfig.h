// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SInputConfig.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> ChangeView;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Jump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> QuickSlot01;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> QuickSlot02;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Menu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> IronSight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> LandMine;
	
};
