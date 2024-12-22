// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SStatComponent.h"
#include "Game/SGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

void USStatComponent::OnCurrentHPChanged_NetMulticast_Implementation(float InOldCurrentHP, float InNewCurrentHP)
{
	if (true == OnCurrentHPChangedDelegate.IsBound())
	{
		OnCurrentHPChangedDelegate.Broadcast(InOldCurrentHP, InNewCurrentHP);
	}

	if (InNewCurrentHP < KINDA_SMALL_NUMBER)
	{
		OnOutOfCurrentHPDelegate.Broadcast();
	}
}

USStatComponent::USStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = false;
}

void USStatComponent::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<USGameInstance>(GetWorld()->GetGameInstance());
	if (true == ::IsValid(GameInstance))
	{
		if (nullptr != GameInstance->GetCharacterStatDataTable() || nullptr != GameInstance->GetCharacterStatDataTableRow(1))
		{
			float NewMaxHP = GameInstance->GetCharacterStatDataTableRow(1)->MaxHP;
			SetMaxHP(NewMaxHP);
			UE_LOG(LogTemp, Log, TEXT("Hui"));
			SetCurrentHP(MaxHP);
		}
	}
}

void USStatComponent::SetMaxHP(float InMaxHP)
{
	if (true == OnMaxHPChangedDelegate.IsBound())
	{
		OnMaxHPChangedDelegate.Broadcast(MaxHP, InMaxHP);
	}

	MaxHP = FMath::Clamp<float>(InMaxHP, 0.f, 9999);
}

void USStatComponent::SetCurrentHP(float InCurrentHP)
{
	if (true == OnCurrentHPChangedDelegate.IsBound())
	{
		OnCurrentHPChangedDelegate.Broadcast(CurrentHP, InCurrentHP);
	}

	CurrentHP = FMath::Clamp<float>(InCurrentHP, 0.f, MaxHP);

	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		OnOutOfCurrentHPDelegate.Broadcast();
		CurrentHP = 0.f;
	}

	OnCurrentHPChanged_NetMulticast(CurrentHP, CurrentHP);
}

void USStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, MaxHP);
	DOREPLIFETIME(ThisClass, CurrentHP);
}


