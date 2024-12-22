// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/SUIPlayerController.h"
#include "SUIPlayerController_Loading.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASUIPlayerController_Loading : public ASUIPlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;
	
};
