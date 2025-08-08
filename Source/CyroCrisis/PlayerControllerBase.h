#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class ACharacterBase;
class UEnhancedInputComponent;
class UInputAction;
class UInputMappingContext;

UCLASS(Abstract)
class CYROCRISIS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PlayerInput/CharacterMovement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PlayerInput/CharacterMovement")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PlayerInput/CharacterMovement")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PlayerInput/CharacterMovement")
	UInputAction* ActionCrouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PlayerInput/CharacterMovement")
	UInputAction* ActionSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PlayerInput/CharacterMovement")
	UInputMappingContext* InputMappingContext = nullptr;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	ACharacterBase* PlayerCharacter = nullptr;

protected:
	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleJump();
	void HandleSprint();
	bool isSprinting = false;
	void HandleCrouch();
	bool isCrouching = false;
	
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
};
