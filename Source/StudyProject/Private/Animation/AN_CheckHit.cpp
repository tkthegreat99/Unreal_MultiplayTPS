// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_CheckHit.h"
#include "Character/SPlayerCharacter.h"

void UAN_CheckHit::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (IsValid(MeshComp) == true)
	{
		//ASPlayerCharacter* AttackingCharacter = Cast<ASPlayerCharacter>(MeshComp->GetOwner());
		ASCharacter* AttackingCharacter = Cast<ASCharacter>(MeshComp->GetOwner());
		if (IsValid(AttackingCharacter) == true)
		{
			AttackingCharacter->OnCheckHit();
		}
	}
}
