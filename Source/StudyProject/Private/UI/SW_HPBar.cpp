// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SW_HPBar.h"
#include "Components/ProgressBar.h"
#include "Character/SCharacter.h"
#include "Component/SStatComponent.h"

void USW_HPBar::SetMaxHP(float InMaxHP)
{
	SetMaxFigure(InMaxHP);
}

void USW_HPBar::InitializeHPBarWidget(USStatComponent* NewStatComponent)
{
	if (IsValid(NewStatComponent) == true)
	{
		OnCurrentHPChange(0.f, NewStatComponent->GetCurrentHP());
	}
}

void USW_HPBar::OnMaxHPChange(float InOldMaxHP, float InNewMaxHP)
{
	SetMaxFigure(InNewMaxHP);

	OnCurrentHPChange(0.f, InNewMaxHP);
}

void USW_HPBar::OnCurrentHPChange(float InOldHP, float InNewHP)
{
	if (IsValid(Bar) == true)
	{
		if (KINDA_SMALL_NUMBER < MaxFigure)
		{
			Bar->SetPercent(InNewHP / MaxFigure);
		}
		else
		{
			Bar->SetPercent(0.f);
		}
	}
}

void USW_HPBar::NativeConstruct()
{
	Super::NativeConstruct();

	ASCharacter* OwningCharacter = Cast<ASCharacter>(OwningActor);
	if (true == ::IsValid(OwningCharacter))
	{
		OwningCharacter->SetWidget(this);
	}
}
