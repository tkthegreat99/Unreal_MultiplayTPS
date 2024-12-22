// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyProject/Game/SGameMode.h"
#include "Controller/MyPlayerController.h"
#include "UI/SHUD.h"
#include "Game/SPlayerState.h"
#include "Component/SStatComponent.h"
#include "Character/SCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Character/SPlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SGameResultWidget.h"
#include "Components/TextBlock.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

    FInputModeGameOnly InputModeGameOnly;
    SetInputMode(InputModeGameOnly);

    if (!(GetWorld()->GetFirstPlayerController()->IsLocalController()))
    {
        return;
    }
    

    if (IsValid(HUDWidgetClass) == true)
    {
        HUDWidget = CreateWidget<USHUD>(this, HUDWidgetClass);
        if (IsValid(HUDWidget) == true)
        {
            HUDWidget->AddToViewport();

            ASPlayerState* SPlayerState = GetPlayerState<ASPlayerState>();
            if (IsValid(SPlayerState) == true)
            {
                
                HUDWidget->BindPlayerState(SPlayerState);
            }

            ASCharacter* PC = GetPawn<ASCharacter>();
            if (IsValid(PC) == true)
            {
                USStatComponent* StatComponent = PC->GetStatComponent();
                if (IsValid(StatComponent) == true)
                {
                    HUDWidget->BindStatComponent(StatComponent);
                }
            }
        }
    }

    if (IsValid(InGameMenuClass) == true)
    {
        InGameMenuInstance = CreateWidget<UUserWidget>(this, InGameMenuClass);
        if (IsValid(InGameMenuInstance) == true)
        {
            InGameMenuInstance->AddToViewport(3); // »óÀ§¿¡ ¶ç¿ò.

            InGameMenuInstance->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    if (IsValid(CrosshairUIClass) == true)
    {
        UUserWidget* CrosshairUIInstance = CreateWidget<UUserWidget>(this, CrosshairUIClass);
        if (IsValid(CrosshairUIInstance) == true)
        {
            CrosshairUIInstance->AddToViewport(1);

            CrosshairUIInstance->SetVisibility(ESlateVisibility::Visible);
        }
    }

    if (IsValid(NotificationTextUIClass) == true)
    {
        UUserWidget* NotificationTextUI = CreateWidget<UUserWidget>(this, NotificationTextUIClass);
        if (IsValid(NotificationTextUI) == true)
        {
            NotificationTextUI->AddToViewport(1);

            NotificationTextUI->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void AMyPlayerController::ToggleInGameMenu()
{
    checkf(IsValid(InGameMenuInstance) == true, TEXT("Invalid InGameMenuInstance"));

    if (false == bIsInGameMenuOn)
    {
        InGameMenuInstance->SetVisibility(ESlateVisibility::Visible);

        FInputModeUIOnly Mode;
        SetInputMode(Mode);
        Mode.SetWidgetToFocus(InGameMenuInstance->GetCachedWidget());
      
        SetPause(true); 
     
        bShowMouseCursor = true;
    }
    else
    {
        InGameMenuInstance->SetVisibility(ESlateVisibility::Collapsed);

        FInputModeGameOnly InputModeGameOnly;
        SetInputMode(InputModeGameOnly);

        SetPause(false);
        bShowMouseCursor = false;
    }

    bIsInGameMenuOn = !bIsInGameMenuOn;
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, NotificationText);
}

void AMyPlayerController::OnOwningCharacterDead()
{
    ASGameMode* GameMode = Cast<ASGameMode>(UGameplayStatics::GetGameMode(this));
    if ((GetWorld()->GetFirstPlayerController()->IsLocalController()) == false && IsValid(GameMode) == true)
    {
        GameMode->OnControllerDead(this);
    }
}

void AMyPlayerController::ReturnToLobby_Implementation()
{
    if ((GetWorld()->GetFirstPlayerController()->IsLocalController()) == true)
    { 
        UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Loading")), true, FString(TEXT("NextLevel=Lobby?Saved=false")));
    }
}

void AMyPlayerController::ShowLooserUI_Implementation(int32 InRanking)
{
    if ((GetWorld()->GetFirstPlayerController()->IsLocalController()) == true)
    {
        if (IsValid(LooserUIClass) == true)
        {
            USGameResultWidget* LooserUI = CreateWidget<USGameResultWidget>(this, LooserUIClass);
            if (IsValid(LooserUI) == true)
            {
                LooserUI->AddToViewport(3);
                FString RankingString = FString::Printf(TEXT("#%02d"), InRanking);
                LooserUI->RankingText->SetText(FText::FromString(RankingString));

                FInputModeUIOnly Mode;
                Mode.SetWidgetToFocus(LooserUI->GetCachedWidget());
                SetInputMode(Mode);

                bShowMouseCursor = true;
            }
        }
    }
}

void AMyPlayerController::ShowWinnerUI_Implementation()
{
    if ((GetWorld()->GetFirstPlayerController()->IsLocalController()) == true)
    {
        if (IsValid(WinnerUIClass) == true)
        {
            USGameResultWidget* WinnerUI = CreateWidget<USGameResultWidget>(this, WinnerUIClass);
            if (IsValid(WinnerUI) == true)
            {
                WinnerUI->AddToViewport(3);
                WinnerUI->RankingText->SetText(FText::FromString(TEXT("#01")));

                FInputModeUIOnly Mode;
                Mode.SetWidgetToFocus(WinnerUI->GetCachedWidget());
                SetInputMode(Mode);

                bShowMouseCursor = true;
            }
        }
    }
}
