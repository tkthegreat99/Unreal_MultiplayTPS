// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SUIPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ASUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (true == ::IsValid(UIWidgetClass))
	{
		UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
		if (true == ::IsValid(UIWidgetInstance))
		{
			UIWidgetInstance->AddToViewport();

			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
			SetInputMode(Mode);

			bShowMouseCursor = true;
		}
	}
}

void ASUIPlayerController::JoinServer(const FString& InIPAddress)
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Loading"), true, FString::Printf(TEXT("NextLevel=%s?Saved=false"), *InIPAddress));
}

