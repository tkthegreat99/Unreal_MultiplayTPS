// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "SGameInstance.generated.h"

class UDataTable;

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSStatTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSStatTableRow()
	{
		MaxHP = 100.f;
		MaxKillCount = 100.f;
	}

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxKillCount;

};

UCLASS()
class STUDYPROJECT_API USGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	virtual void Init() override;

	virtual void Shutdown() override;

	const UDataTable* GetCharacterStatDataTable() const { return CharacterStatDataTable; }

	FSStatTableRow* GetCharacterStatDataTableRow(int32 InLevel);
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UDataTable> CharacterStatDataTable;
};
