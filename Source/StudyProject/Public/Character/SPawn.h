

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SPawn.generated.h"


class UCapsuleComponent;
class USkeletalMeshComponent;
class UFloatingPawnMovement;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class STUDYPROJECT_API ASPawn : public APawn
{
	GENERATED_BODY()

public:
	
	ASPawn();

protected:

	UPROPERTY(EditAnywhere, Category = "SPawn", Meta = (AllowPrivateAccess))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = "SPawn", Meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, Category = "SPawn", Meta = (AllowPrivateAccess))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(EditAnywhere, Category = "SPawn", Meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "SPawn", Meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;
};
