//SLandMine.cpp

#include "WorldStatic/SLandMine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

ASLandMine::ASLandMine() : bIsExploded(false)
{
	PrimaryActorTick.bCanEverTick = true;

	BodyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyBoxComponent"));
	SetRootComponent(BodyBoxComponent);

	BodyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyStaticMeshComponent"));
	BodyStaticMeshComponent->SetupAttachment(GetRootComponent());

	bReplicates = true;

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(GetRootComponent());
    ParticleSystemComponent->SetAutoActivate(false);
}

void ASLandMine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, bIsExploded);
}

void ASLandMine::OnRep_IsExploded()
{
    if (true == bIsExploded)
    {
        BodyStaticMeshComponent->SetMaterial(0, ExplodedMaterial);
    }
}

void ASLandMine::BeginPlay()
{
	Super::BeginPlay();

        if (false == OnActorBeginOverlap.IsAlreadyBound(this, &ThisClass::OnLandMineBeginOverlap))
    {
        OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnLandMineBeginOverlap);
    }

	
}

void ASLandMine::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

    if (true == OnActorBeginOverlap.IsAlreadyBound(this, &ThisClass::OnLandMineBeginOverlap))
    {
        OnActorBeginOverlap.RemoveDynamic(this, &ThisClass::OnLandMineBeginOverlap);
    }
}

void ASLandMine::OnLandMineBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (true == HasAuthority())
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::OnLandMineBeginOverlap() has been called in Server PC.")));
    }
    else
    {
        if (GetOwner() == UGameplayStatics::GetPlayerController(this, 0))
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::OnLandMineBeginOverlap() has been called in OwningClient PC.")));
        }
        else
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::OnLandMineBeginOverlap() has been called in OtherClient PC.")));
        }
    }

    if (true == HasAuthority() && false == bIsExploded)
    {
        SpawnEffect_NetMulticast();
        bIsExploded = true;
    }
}

void ASLandMine::SpawnEffect_NetMulticast_Implementation()
{
    ParticleSystemComponent->Activate(true);

    if (true == ::IsValid(ExplodedMaterial))
    {
        BodyStaticMeshComponent->SetMaterial(0, ExplodedMaterial);
    }
}

void ASLandMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

