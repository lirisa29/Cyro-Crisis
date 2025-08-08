#pragma once

#include "CoreMinimal.h"
#include "AmmoBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "AICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAIShotEvent, float, DamageAmount);

UCLASS()
class CYROCRISIS_API AAICharacter : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAICharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess= "true"))
	UBehaviorTree* Tree;

	// Ensure function runs only once
	bool hasFunctionRun = false;

public:	
	virtual void Tick(float DeltaTime) override;

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

	UFUNCTION()
	void SwitchGun();	

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* AIMesh;

	class UAnimInstance* AnimInstance;

	UBehaviorTree* GetBehaviorTree() const;

	UAnimMontage* GetMontage() const;

	int Shoot_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 SecondaryWeaponAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 SecondaryWeaponAmmoMax;

	// Health-related properties for the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UFUNCTION()
	void OnAIPickupTriggeredHandler(AAmmoBase* pickup);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAIShotEvent OnAIShot;

	void ResetBotHealth();

	float GetHealth() const;

	void CheckHealthAndAvoid();

	void AvoidTarget();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage;

	void UpdateHealth(float HealthChange);

	UFUNCTION()
	void OnAIShotTriggeredHandler(float Amount);

};
