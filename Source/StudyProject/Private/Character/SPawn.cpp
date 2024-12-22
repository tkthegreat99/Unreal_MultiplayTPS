


#include "Character/SPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


ASPawn::ASPawn()
{

	PrimaryActorTick.bCanEverTick = false;

	float CharacterHalfHeight = 90.f;
	float CharacterRadius = 40.f;

#pragma region InitializeCapsuleComponent

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetCapsuleHalfHeight(CharacterHalfHeight);
	CapsuleComponent->SetCapsuleRadius(CharacterRadius);

#pragma endregion

#pragma region InitializeSkeletalMeshComponent

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	FVector PivotPosition(0.f, 0.f, -CharacterHalfHeight);
	FRotator PivotRotation(0.f, -90.f, 0.f);
	SkeletalMeshComponent->SetRelativeLocationAndRotation(PivotPosition, PivotRotation);

#pragma endregion

#pragma region InitializeCamera

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->SetRelativeRotation(FRotator( - 15.f, 0.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

#pragma endregion

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

}


