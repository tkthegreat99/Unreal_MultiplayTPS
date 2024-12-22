// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UW_TitleLayout.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UUW_TitleLayout::UUW_TitleLayout(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UUW_TitleLayout::NativeConstruct()
{
	PlayButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnPlayButtonClicked);
	ExitButton.Get()->OnClicked.AddDynamic(this, &ThisClass::OnExitButtonClicked);
}

void UUW_TitleLayout::OnPlayButtonClicked()
{
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("ThirdPersonMap"));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Loading")), true, FString(TEXT("NextLevel=Lobby")));
}

void UUW_TitleLayout::OnExitButtonClicked()	
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
