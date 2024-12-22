// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_LobbyLayout.h"
#include "SPlayerCharacterSettings.h"
#include "GameFramework/Character.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Controller/SUIPlayerController.h"

void UUW_LobbyLayout::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    ACharacter* Character = Cast<ACharacter>(GetOwningPlayerPawn());
    CurrentSkeletalMeshComponent = Character->GetMesh();

    BlackTeamButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnBlackTeamButtonClicked);
    WhiteTeamButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnWhiteTeamButtonClicked);
    SubmitButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnSubmitButtonClicked);

    
}

void UUW_LobbyLayout::NativeDestruct()
{
    for (auto Handle : StreamableHandles)
    {
        if (Handle.IsValid() == true)
        {
            Handle->ReleaseHandle();
        }
    }

    Super::NativeDestruct();
}

void UUW_LobbyLayout::OnBlackTeamButtonClicked()
{
    CurrentSkeletalMeshComponent->SetMaterial(0, BlackMaterial);
    SelectedTeam = 1;
}

void UUW_LobbyLayout::OnWhiteTeamButtonClicked()
{
    CurrentSkeletalMeshComponent->SetMaterial(0, WhiteMaterial);
    SelectedTeam = 2;
}

void UUW_LobbyLayout::OnSubmitButtonClicked()
{
    FString PlayerName = EditPlayerName->GetText().ToString();
    if (PlayerName.Len() <= 0 || 10 <= PlayerName.Len())
    {
        return;
    }
    
    const FString SavedDirectoryPath = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
    const FString SavedFileName(TEXT("PlayerInfo.txt"));
    FString AbsoluteFilePath = FPaths::Combine(*SavedDirectoryPath, *SavedFileName);
    FPaths::MakeStandardFilename(AbsoluteFilePath);

    TSharedRef<FJsonObject> PlayerInfoJsonObject = MakeShared<FJsonObject>();
    PlayerInfoJsonObject->SetStringField("playername", PlayerName);
    PlayerInfoJsonObject->SetNumberField("team", SelectedTeam);

    FString PlayerInfoJsonString;
    TSharedRef<TJsonWriter<TCHAR>> JsonWriterArchive = TJsonWriterFactory<TCHAR>::Create(&PlayerInfoJsonString);
    if (FJsonSerializer::Serialize(PlayerInfoJsonObject, JsonWriterArchive) == true)
    {
        FFileHelper::SaveStringToFile(PlayerInfoJsonString, *AbsoluteFilePath);
    }

    ASUIPlayerController* PlayerController = GetOwningPlayer<ASUIPlayerController>();
    if (true == ::IsValid(PlayerController))
    {
        FText ServerIP = EditServerIP->GetText();
        PlayerController->JoinServer(ServerIP.ToString());
    }

    UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Server Login"), true, true, FLinearColor::Blue, 2.0f);
}
