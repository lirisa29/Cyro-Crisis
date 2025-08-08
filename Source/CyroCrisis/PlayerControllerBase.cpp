#include "PlayerControllerBase.h"
#include "CharacterBase.h"
#include "GameManager.h"
#include "DefaultGameModeBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void APlayerControllerBase::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2d MoveVector = InputActionValue.Get<FVector2d>();

	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(),MoveVector.Y );
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MoveVector.X );
}

void APlayerControllerBase::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2d LookVector = InputActionValue.Get<FVector2d>();

	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void APlayerControllerBase::HandleJump()
{
	PlayerCharacter->UnCrouch();
	PlayerCharacter->Jump();
}

void APlayerControllerBase::HandleSprint()
{
	if(isSprinting == true)
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		isSprinting = false;
	}
	else
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 1500.0f;
		isSprinting = true;
	}
}

void APlayerControllerBase::HandleCrouch()
{
	if(isCrouching == true)
	{
		PlayerCharacter->UnCrouch();
		isCrouching = false;
	}
	else
	{
		PlayerCharacter->Crouch();
		isCrouching = true;
	}
}

void APlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<ACharacterBase>(aPawn);
	checkf(PlayerCharacter, TEXT("ACharacterBase derived classes should only posses ACharacterBase derived pawns"));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get a reference to EnhancedInputComponent"));

	// Linking up our mapping context to the possessed player controller
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get a reference to UEnhancedInputLocalPlayerSubsystem"));

	// Wipe any existing mapping and add our own mapping
	checkf(InputMappingContext, TEXT("InputMappingContext was not specified"));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	if(ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &APlayerControllerBase::HandleMove);
	}

	if(ActionLook)
	{
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &APlayerControllerBase::HandleLook);
	}

	if(ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &APlayerControllerBase::HandleJump);
	}

	if(ActionSprint)
	{
		EnhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Triggered, this, &APlayerControllerBase::HandleSprint);
	}

	if(ActionCrouch)
	{
		EnhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Triggered, this, &APlayerControllerBase::HandleCrouch);
	}
}

void APlayerControllerBase::OnUnPossess()
{
	Super::OnUnPossess();
}
