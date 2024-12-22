// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"

class UBlackboardData;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API ASAIController : public AAIController
{
	GENERATED_BODY()

	friend class ASNonPlayerCharacter;
	
public:
	ASAIController();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void BeginAI(APawn* InPawn);

	void EndAI();

public:
	static const float PatrolRadius;

	static int32 ShowAIDebug;

	static const FName StartPatrolPositionKey;

	static const FName EndPatrolPositionKey;

	static const FName TargetActorKey;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBlackboardData> BlackboardDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBehaviorTree> BehaviorTree;


};
