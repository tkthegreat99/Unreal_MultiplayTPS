// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API USWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	USWidgetComponent();

	virtual void InitWidget() override;
};
