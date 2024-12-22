// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SWeaponActor.h"


ASWeaponActor::ASWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bReplicates = true;
}
