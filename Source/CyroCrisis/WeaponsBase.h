#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponsBase.generated.h"

class ACharacterBase;
UCLASS()
class CYROCRISIS_API AWeaponsBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USceneComponent* MuzzleLocation;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector GunOffset;
	
	UPROPERTY(EditAnywhere, Category = Weapon)
	int32 WeaponMaxAmmo;

	UPROPERTY(EditAnywhere, Category = Weapon)
	int32 MagazineMaxAmmo;

	UPROPERTY(EditAnywhere, Category = Weapon)
	FString WeaponName;

	UPROPERTY(EditAnywhere, Category = Weapon)
	int32 BaseDamage;
	
	int32 CurrentTotalAmmo;
	int32 CurrentMagazineAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FLinearColor GunColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UMaterial* GunMaterial;

	UPROPERTY()
	ACharacterBase* PlayerCharacter = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> Projectile;

	class UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;
	
public:	
	AWeaponsBase();

	virtual void Fire();

	virtual void Reload();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float reloadTime;
	
	class USkeletalMeshComponent* GetWeaponMesh() {return GunMesh;}

	FRotator SpawnRotation;
	FVector SpawnLocation;

	void ReplenishAmmo();

	virtual bool IsSecondaryWeapon() const;

protected:
	virtual void BeginPlay() override;

};
