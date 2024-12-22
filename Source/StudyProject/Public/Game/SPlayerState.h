// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentKillCountChangedDelegate, int32, InOldCurrentKillCount, int32, InNewCurrentKillCount);

UENUM(BlueprintType)
enum class EPlayerTeam : uint8
{
	None,
	Black,
	White,
	End
};

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASPlayerState();

	EPlayerTeam GetPlayerTeam() const { return PlayerTeam; }

	void InitPlayerState();

	int32 GetMaxKillCount() const { return MaxKillCount; }

	void SetMaxKillCount(int32 InMaxKillCount) { MaxKillCount = InMaxKillCount; }

	int32 GetCurrentKillCount() const { return CurrentKillCount; }

	void AddCurrentKillCount(int32 InCurrentKillCount);

public:
	FOnCurrentKillCountChangedDelegate OnCurrentKillCountChangedDelegate;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	int32 CurrentKillCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	int32 MaxKillCount = 99;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	EPlayerTeam PlayerTeam = EPlayerTeam::None;
	
};
