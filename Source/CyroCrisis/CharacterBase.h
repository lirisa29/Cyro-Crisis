#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "HealthBarWidget.h"
#include "SecondaryGun.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

// Forward declarations
class AWeaponsBase;
class AHUDBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthPickupEvent, float, HealthAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShotEvent, float, DamageAmount);

UCLASS()
class CYROCRISIS_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	// Class types for primary and secondary weapons that can be equipped
	UPROPERTY(EditAnywhere, Category = Weapons)
	TSubclassOf<class AWeaponsBase> PrimaryWeaponClass;

	UPROPERTY(EditAnywhere, Category = Weapons)
	TSubclassOf<class AWeaponsBase> SecondaryWeaponClass;

	// Default scale for gun mesh
	UPROPERTY()
	FVector DefaultScale = FVector(1.0f, 1.0f, 1.0f);

	// Scale for when method is not in use
	UPROPERTY()
	FVector OpenScale = FVector(0.0f, 0.0f, 0.0f);

	// Pointer to the currently equipped weapon
	UPROPERTY()
	class AWeaponsBase* CurrentWeapon;

	UFUNCTION()
	void AttachWeapon();

	// Index to track the currently selected weapon
	int32 WeaponIndex;
	// Array to store all equipped weapons
	TArray<AWeaponsBase*> WeaponArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPSCamera;

	UFUNCTION()
	void OnPickupTriggeredHandler(AAmmoBase* pickup);

	UFUNCTION()
	void OnShotTriggeredHandler(float Amount);

public:
	ACharacterBase();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthPickupEvent OnHealthPickup;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnShotEvent OnShot;

	UFUNCTION()
	void HandleHealthPickup(float Amount);

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* HandsMesh;

	class UAnimInstance* AnimInstance;

	void OnFire();
	
	void ReloadWeapon();

	// Health-related properties for the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthPercentage;

	// Class type for the health bar widget used in the UI
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHealthBarWidget> HealthWidgetClass;

	UPROPERTY()
	UHealthBarWidget* HealthWidget;

	AWeaponsBase* GetGun() const;

	AHUDBase* GetHUD() const;

	void ResetPlayerHealth();

protected:
	virtual void BeginPlay() override;

	void SwitchNextWeapon();

	void SwitchPreviousWeapon();

	// Ensure function runs only once
	bool hasFunctionRun = false;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void UpdateHealth(float HealthChange);
	void UpdateHealthUI();

	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetupStimulusSource();
	
};
