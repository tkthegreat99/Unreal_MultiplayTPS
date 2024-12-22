// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"

class AMyPlayerController;

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	virtual void BeginPlay() override;

	void OnControllerDead(AMyPlayerController* InDeadController);

private:
	UFUNCTION()
	void OnMainTimerElapsed();

	void NotifyToAllPlayer(const FString& NotificationString);


public:
	FTimerHandle MainTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASGameMode")
	int32 WaitingTime = 15;

	int32 RemainWaitingTimeForPlaying = 15;

	int32 MinimumPlayerCountForPlaying = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASGameMode")
	int32 EndingTime = 15;

	int32 RemainWaitingTimeForEnding = 15;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASGameMode", Meta = (AllowPrivateAccess))
	TArray<TObjectPtr<AMyPlayerController>> AlivePlayerControllers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASGameMode", Meta = (AllowPrivateAccess))
	TArray<TObjectPtr<AMyPlayerController>> DeadPlayerControllers;
	
};
