// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SHUD.generated.h"

class USStatComponent;
class ASPlayerState;
class UTextBlock;
class USW_HPBar;

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindStatComponent(class USStatComponent* InStatComponent);

	void BindPlayerState(class ASPlayerState* InPlayerState);

protected:
	UFUNCTION()
	void OnKillCountChanged(int32 InOldKillCount, int32 InNewKillCount);

protected:
	TWeakObjectPtr<USStatComponent> StatComponent;

	TWeakObjectPtr<ASPlayerState> PlayerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> KillCountText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerNameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USW_HPBar> HPBar;
};
