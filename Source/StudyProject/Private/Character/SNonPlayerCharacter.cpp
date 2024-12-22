// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SNonPlayerCharacter.h"
#include "Controller/SAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/SAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/SStatComponent.h"
#include "UI/SW_HPBar.h"
#include "Component/SWidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Game/SPlayerState.h"

ASNonPlayerCharacter::ASNonPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	AIControllerClass = ASAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	WidgetComponent = CreateDefaultSubobject<USWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());
	WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (false == IsPlayerControlled())
	{
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

		GetCharacterMovement()->MaxWalkSpeed = 300.f;
	}
}

float ASNonPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (GetStatComponent()->GetCurrentHP() < KINDA_SMALL_NUMBER)
	{
		ASAIController* AIController = Cast<ASAIController>(GetController());
		if (true == ::IsValid(AIController))
		{
			AIController->EndAI();
		}

		ASPlayerCharacter* DamageCauserCharacter = Cast<ASPlayerCharacter>(DamageCauser);
		if (true == ::IsValid(DamageCauserCharacter))
		{
			ASPlayerState* SPlayerState = Cast<ASPlayerState>(DamageCauserCharacter->GetPlayerState());
			if (IsValid(SPlayerState) == true)
			{
				SPlayerState->AddCurrentKillCount(1);
			}
		}

		//Destroy();
		WidgetComponent->DestroyComponent();
	}

	return FinalDamageAmount;
}

void ASNonPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsValid(WidgetComponent) == true)
	{
		FVector WidgetComponentLocation = WidgetComponent->GetComponentLocation();
		FVector LocalPlayerCameraLocation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation();
		WidgetComponent->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(WidgetComponentLocation, LocalPlayerCameraLocation));
	}
}

void ASNonPlayerCharacter::SetWidget(UStudyWidget* InStudyWidget)
{
	Super::SetWidget(InStudyWidget);

	USW_HPBar* HPBarWidget = Cast<USW_HPBar>(InStudyWidget);
	if (IsValid(HPBarWidget) == true)
	{
		HPBarWidget->SetMaxHP(StatComponent->GetMaxHP());
		HPBarWidget->InitializeHPBarWidget(StatComponent);
		StatComponent->OnCurrentHPChangedDelegate.AddDynamic(HPBarWidget, &USW_HPBar::OnCurrentHPChange);
	}
}

void ASNonPlayerCharacter::BeginAttack()
{
	USAnimInstance* AnimInstance = Cast<USAnimInstance>(GetMesh()->GetAnimInstance());
	checkf(IsValid(AnimInstance) == true, TEXT("Invalid AnimInstance"));

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	bIsNowAttacking = true;
	AnimInstance->PlayAnimMontage(MeleeAttackMontage);

	if (OnMeleeAttackMontageEndedDelegate.IsBound() == false)
	{
		OnMeleeAttackMontageEndedDelegate.BindUObject(this, &ThisClass::EndAttack);
		AnimInstance->Montage_SetEndDelegate(OnMeleeAttackMontageEndedDelegate, MeleeAttackMontage);
	}
}

void ASNonPlayerCharacter::EndAttack(UAnimMontage* InMontage, bool bInterruped)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bIsNowAttacking = false;

	if (OnMeleeAttackMontageEndedDelegate.IsBound() == true)
	{
		OnMeleeAttackMontageEndedDelegate.Unbind();
	}
}
