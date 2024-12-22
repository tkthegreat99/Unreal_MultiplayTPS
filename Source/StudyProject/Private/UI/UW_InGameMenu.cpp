// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_InGameMenu.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/MyPlayerController.h"

void UUW_InGameMenu::NativeConstruct()
{
	ResumeButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnResumeButtonClicked);
	ReturnTitleButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnReturnTitleButtonClicked);
	ExitButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnExitButtonClicked);
}

void UUW_InGameMenu::OnResumeButtonClicked()
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetOwningPlayer());
	if (true == ::IsValid(PlayerController))
	{
		PlayerController->ToggleInGameMenu();
	}
}

void UUW_InGameMenu::OnReturnTitleButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Loading")), true, FString(TEXT("NextLevel=Title")));
}

void UUW_InGameMenu::OnExitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
