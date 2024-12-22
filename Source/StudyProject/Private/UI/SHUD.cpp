// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SHUD.h"
#include "Component/SStatComponent.h"
#include "Game/SPlayerState.h"
#include "UI/SW_HPBar.h"
#include "Components/TextBlock.h"
#include "Game/SGameInstance.h"

void USHUD::BindStatComponent(USStatComponent* InStatComponent)
{
	if (IsValid(InStatComponent) == true)
	{
		StatComponent = InStatComponent;
		StatComponent->OnCurrentHPChangedDelegate.AddDynamic(HPBar, &USW_HPBar::OnCurrentHPChange);
		StatComponent->OnMaxHPChangedDelegate.AddDynamic(HPBar, &USW_HPBar::OnMaxHPChange);

		USGameInstance* GameInstance = Cast<USGameInstance>(GetWorld()->GetGameInstance());
		if (IsValid(GameInstance) == true)
		{
			if (GameInstance->GetCharacterStatDataTable() != nullptr || GameInstance->GetCharacterStatDataTableRow(1) != nullptr)
			{
				float MaxHP = GameInstance->GetCharacterStatDataTableRow(1)->MaxHP;
				HPBar->SetMaxHP(MaxHP);
				HPBar->InitializeHPBarWidget(StatComponent.Get());
			}
		}
	}
}

void USHUD::BindPlayerState(ASPlayerState* InPlayerState)
{
	if (IsValid(InPlayerState) == true)
	{
		PlayerState = InPlayerState;
		PlayerState->OnCurrentKillCountChangedDelegate.AddDynamic(this, &ThisClass::OnKillCountChanged);

		PlayerNameText->SetText(FText::FromString(PlayerState->GetPlayerName()));
		OnKillCountChanged(0, PlayerState->GetCurrentKillCount());
	}
}

void USHUD::OnKillCountChanged(int32 InOldKillCount, int32 InNewKillCount)
{
	FString KillCountString = FString::Printf(TEXT("%d"), InNewKillCount);
	KillCountText->SetText(FText::FromString(KillCountString));
}
