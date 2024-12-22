// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"
#include "Controller/MyPlayerController.h"
#include "Character/SPawn.h"
#include "Game/SPlayerState.h"
#include "Game/SGameState.h"
#include "Kismet/GameplayStatics.h"

ASGameMode::ASGameMode()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = ASPawn::StaticClass();
}

void ASGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

    ASGameState* SGameState = GetGameState<ASGameState>();
    if (false == ::IsValid(SGameState))
    {
        return;
    }

    if (SGameState->MatchState != EMatchState::Waiting)
    {
        NewPlayer->SetLifeSpan(0.1f);
        return;
    }

	ASPlayerState* PlayerState = NewPlayer->GetPlayerState<ASPlayerState>();
	if (true == ::IsValid(PlayerState))
	{
		PlayerState->InitPlayerState();
	}

	AMyPlayerController* NewPlayerController = Cast<AMyPlayerController>(NewPlayer);
	if (true == ::IsValid(NewPlayerController))
	{
		AlivePlayerControllers.Add(NewPlayerController);
		NewPlayerController->NotificationText = FText::FromString(TEXT("Connected to the game server."));
	}
}

void ASGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AMyPlayerController* ExitingPlayerController = Cast<AMyPlayerController>(Exiting);
	if (true == ::IsValid(ExitingPlayerController) && INDEX_NONE != AlivePlayerControllers.Find(ExitingPlayerController))
	{
		AlivePlayerControllers.Remove(ExitingPlayerController);
		DeadPlayerControllers.Add(ExitingPlayerController);
	}
}

void ASGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MainTimerHandle, this, &ThisClass::OnMainTimerElapsed, 1.f, true);

	RemainWaitingTimeForPlaying = WaitingTime;
    RemainWaitingTimeForEnding = EndingTime;
}

void ASGameMode::OnControllerDead(AMyPlayerController* InDeadController)
{
    if (IsValid(InDeadController) == false || AlivePlayerControllers.Find(InDeadController) == INDEX_NONE)
    {
        return;
    }
    InDeadController->ShowLooserUI(AlivePlayerControllers.Num());
    AlivePlayerControllers.Remove(InDeadController);
    DeadPlayerControllers.Add(InDeadController);
}

void ASGameMode::OnMainTimerElapsed()
{
    ASGameState* SGameState = GetGameState<ASGameState>();
    if (false == ::IsValid(SGameState))
    {
        return;
    }

    switch (SGameState->MatchState)
    {
    case EMatchState::None:
        break;
    case EMatchState::Waiting:
    {
        FString NotificationString = FString::Printf(TEXT(""));

        if (AlivePlayerControllers.Num() < MinimumPlayerCountForPlaying)
        {
            NotificationString = FString::Printf(TEXT("Wait another players for playing."));

            RemainWaitingTimeForPlaying = WaitingTime; 
        }
        else
        {
            NotificationString = FString::Printf(TEXT("Wait %d seconds for playing."), RemainWaitingTimeForPlaying);

            --RemainWaitingTimeForPlaying;
        }

        if (0 == RemainWaitingTimeForPlaying)
        {
            NotificationString = FString::Printf(TEXT(""));

            SGameState->MatchState = EMatchState::Playing;
        }

        NotifyToAllPlayer(NotificationString);

        break;
    }
    case EMatchState::Playing:
    {
        if (IsValid(SGameState) == true)
        {
            SGameState->AlivePlayerControllerCount = AlivePlayerControllers.Num();

            FString NotificationString = FString::Printf(TEXT("%d / %d"), SGameState->AlivePlayerControllerCount, SGameState->AlivePlayerControllerCount + DeadPlayerControllers.Num());

            NotifyToAllPlayer(NotificationString);

            if (SGameState->AlivePlayerControllerCount <= 1)
            {
                SGameState->MatchState = EMatchState::Ending;
                AlivePlayerControllers[0]->ShowWinnerUI();
            }
        }
        break;
    }
        
    case EMatchState::Ending:
    {
        FString NotificationString = FString::Printf(TEXT("Waiting %d for returning to lobby."), RemainWaitingTimeForEnding);

        NotifyToAllPlayer(NotificationString);

        --RemainWaitingTimeForEnding;

        if (RemainWaitingTimeForEnding <= 0)
        {
            for (auto AliveController : AlivePlayerControllers)
            {
                AliveController->ReturnToLobby();
            }
            for (auto DeadController : DeadPlayerControllers)
            {
                DeadController->ReturnToLobby();
            }

            MainTimerHandle.Invalidate();

            FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(this));
            UGameplayStatics::OpenLevel(this, CurrentLevelName, true, FString(TEXT("listen")));
            return;
        }

        break;
    }
    case EMatchState::End:
        break;
    default:
        break;
    }
}

void ASGameMode::NotifyToAllPlayer(const FString& NotificationString)
{
    for (auto AlivePlayerController : AlivePlayerControllers)
    {
        AlivePlayerController->NotificationText = FText::FromString(NotificationString);
    }

    for (auto DeadPlayerController : DeadPlayerControllers)
    {
        DeadPlayerController->NotificationText = FText::FromString(NotificationString);
    }
}
