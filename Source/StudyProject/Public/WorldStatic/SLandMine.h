// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLandMine.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UMaterial;

UCLASS()
class STUDYPROJECT_API ASLandMine : public AActor
{
	GENERATED_BODY()
	
public:	
	ASLandMine();

	UFUNCTION()
	void OnLandMineBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(NetMulticast, Unreliable)
	void SpawnEffect_NetMulticast();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_IsExploded();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
public:	
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASLandMine", Meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> BodyBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASLandMine", Meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> BodyStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASLandMine", meta = (AllowPrivateAccess))
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;

	UPROPERTY(ReplicatedUsing = OnRep_IsExploded, VisibleAnywhere, BlueprintReadOnly, Category = "ASLandMine", meta = (AllowPrivateAccess))
	uint8 bIsExploded : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASLandMine", meta = (AllowPrivateAccess))
	TObjectPtr<UMaterial> ExplodedMaterial;

};
