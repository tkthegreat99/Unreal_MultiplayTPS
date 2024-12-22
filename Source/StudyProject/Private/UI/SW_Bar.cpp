// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SW_Bar.h"
#include "Components/ProgressBar.h"

USW_Bar::USW_Bar(const FObjectInitializer& ObjectInitializer)
{

}

void USW_Bar::SetMaxFigure(float InMaxFigure)
{
	if (InMaxFigure < KINDA_SMALL_NUMBER)
	{
		MaxFigure = 0.f;
		return;
	}

	MaxFigure = InMaxFigure;
}

void USW_Bar::NativeConstruct()
{
	Super::NativeConstruct();

	Bar = Cast<UProgressBar>(GetWidgetFromName("BarWidget"));
	// 하드코딩으로
	checkf(IsValid(Bar) == true, TEXT("Invalid Bar"));
}
