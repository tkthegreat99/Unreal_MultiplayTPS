// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsInAttackRange.h"
#include "Controller/SAIController.h"
#include "Character/SNonPlayerCharacter.h"
#include "Character/SCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

const float UBTDecorator_IsInAttackRange::AttackRange(200.f);


UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("IsInAttackRange");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	checkf(bResult == true, TEXT("Super::CalculateRawConditionValue() function has returned false."));

	ASAIController* AIController = Cast<ASAIController>(OwnerComp.GetAIOwner());
	checkf(IsValid(AIController) == true, TEXT("Invalid AIController."));

	ASNonPlayerCharacter* NPC = Cast<ASNonPlayerCharacter>(AIController->GetPawn());
	checkf(IsValid(NPC) == true, TEXT("Invalid NPC."));

	ASCharacter* TargetPlayerCharacter = Cast<ASCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASAIController::TargetActorKey));
	if (IsValid(TargetPlayerCharacter) == true && TargetPlayerCharacter->IsPlayerControlled() == true)
	{
		return NPC->GetDistanceTo(TargetPlayerCharacter) <= AttackRange;
	}

	return false;
}
