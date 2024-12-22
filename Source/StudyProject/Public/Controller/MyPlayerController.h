// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class USHUD;
class USGameResultWidget;
/**
 * 
 */
UCLASS()
class STUDYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
		USHUD* GetHUDWidget() const { return HUDWidget; };

		virtual void BeginPlay() override;

		void ToggleInGameMenu();

		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

		void OnOwningCharacterDead();



private:
	UPROPERTY();
	TObjectPtr<USHUD> HUDWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess));
	TSubclassOf<USHUD> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
	TSubclassOf<UUserWidget> InGameMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
	TObjectPtr<UUserWidget> InGameMenuInstance;

	bool bIsInGameMenuOn = false;

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ASPlayerController", Meta = (AllowPrivateAccess))
	FText NotificationText;

	UFUNCTION(Client, Reliable)
	void ShowWinnerUI();

	UFUNCTION(Client, Reliable)
	void ShowLooserUI(int32 InRanking);

	UFUNCTION(Client, Reliable)
	void ReturnToLobby();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
	TSubclassOf<UUserWidget> CrosshairUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
	TSubclassOf<UUserWidget> NotificationTextUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
	TSubclassOf<USGameResultWidget> WinnerUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
	TSubclassOf<USGameResultWidget> LooserUIClass;
};
