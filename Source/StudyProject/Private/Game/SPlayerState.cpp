// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SPlayerState.h"
#include "Character/SPlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ASPlayerState::ASPlayerState()
{

}

void ASPlayerState::InitPlayerState()
{
	SetPlayerName(TEXT("Player"));

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("InitPlayerState"), true, true, FLinearColor::Green, 2.f);
	CurrentKillCount = 0;
	MaxKillCount = 99;

	const FString SavedDirectoryPath = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	const FString SavedFileName(TEXT("PlayerInfo.txt"));
	FString AbsoluteFilePath = FPaths::Combine(*SavedDirectoryPath, *SavedFileName);
	FPaths::MakeStandardFilename(AbsoluteFilePath);

	FString PlayerInfoJsonString;
	FFileHelper::LoadFileToString(PlayerInfoJsonString, *AbsoluteFilePath);
	TSharedRef<TJsonReader<TCHAR>> JsonReaderArchive = TJsonReaderFactory<TCHAR>::Create(PlayerInfoJsonString);

	TSharedPtr<FJsonObject> PlayerInfoJsonObject = nullptr;
	if (FJsonSerializer::Deserialize(JsonReaderArchive, PlayerInfoJsonObject) == true)
	{
		FString PlayerNameString = PlayerInfoJsonObject->GetStringField(TEXT("playername"));
		SetPlayerName(PlayerNameString);

		uint8 PlayerTeamNumber = PlayerInfoJsonObject->GetIntegerField(TEXT("team"));
		PlayerTeam = static_cast<EPlayerTeam>(PlayerTeamNumber);
		ASPlayerCharacter* PlayerCharacter = Cast<ASPlayerCharacter>(GetPawn());
		if (IsValid(PlayerCharacter) == true)
		{
			PlayerCharacter->SetMeshMaterial(PlayerTeam);
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("SetMesh"), true, true, FLinearColor::Green, 2.f);
		}
	}
	
	
}

void ASPlayerState::AddCurrentKillCount(int32 InCurrentKillCount)
{
	OnCurrentKillCountChangedDelegate.Broadcast(CurrentKillCount, CurrentKillCount + InCurrentKillCount);

	CurrentKillCount = FMath::Clamp(CurrentKillCount + InCurrentKillCount, 0, MaxKillCount);

	ASPlayerCharacter* PlayerCharacter = Cast<ASPlayerCharacter>(GetPawn());
	checkf(IsValid(PlayerCharacter) == true, TEXT("Invalid PlayerCharacter"));
	PlayerCharacter->GetParticleSystem()->Activate(true);
}
