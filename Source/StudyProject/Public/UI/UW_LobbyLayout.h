// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_LobbyLayout.generated.h"


class UButton;
class UEditableText;
struct FStreamableHandle;
class UMaterialInstance;
class UMaterial;

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API UUW_LobbyLayout : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void OnBlackTeamButtonClicked();

	UFUNCTION()
	void OnWhiteTeamButtonClicked();

	UFUNCTION()
	void OnSubmitButtonClicked();

protected:

	uint8 SelectedTeam = 1;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USLobbyLevelUI, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> BlackTeamButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USLobbyLevelUI, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> WhiteTeamButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USLobbyLevelUI, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UEditableText> EditPlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USLobbyLevelUI, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UButton> SubmitButton;

	TWeakObjectPtr<USkeletalMeshComponent> CurrentSkeletalMeshComponent;

	TArray<TSharedPtr<FStreamableHandle>> StreamableHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = USLobbyLevelUI, Meta = (AllowPrivateAccess))
	TObjectPtr<UMaterial> BlackMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = USLobbyLevelUI, Meta = (AllowPrivateAccess))
	TObjectPtr<UMaterial> WhiteMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USLobbyLevelUI, Meta = (AllowPrivateAccess, BindWidget))
	TObjectPtr<UEditableText> EditServerIP;
};
