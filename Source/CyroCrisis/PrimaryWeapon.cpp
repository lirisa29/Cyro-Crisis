#include "PrimaryWeapon.h"

#include "CharacterBase.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

APrimaryWeapon::APrimaryWeapon()
{
	WeaponName = "Primary Weapon";
	WeaponMaxAmmo = 0;
	MagazineMaxAmmo = 0;
	BaseDamage = 3.0f;

	CurrentTotalAmmo = WeaponMaxAmmo;
	CurrentMagazineAmmo = MagazineMaxAmmo;
}

void APrimaryWeapon::Fire()
{
	Super::Fire();

	if(Projectile != NULL)
	{
		UWorld* const world = GetWorld();
		if(world != NULL)
		{
			FVector MuzzlePos = (MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation();

        // Initialize the aim direction
        FVector AimDirection;

        // Target to aim at - default is forward direction
        FVector TargetLocation = MuzzlePos + AimDirection * 10000.0f; // Default to far range

        if (PlayerCharacter != nullptr)
        {
            // Use player's control rotation for aiming direction
            SpawnRotation = PlayerCharacter->GetControlRotation();
            AimDirection = SpawnRotation.Vector();
        }
        else
        {
            SpawnRotation = GetOwner()->GetActorRotation();
        	AimDirection = SpawnRotation.Vector();
        }

			float SpawnOffsetDistance = 200.0f;
			SpawnLocation = MuzzlePos + (AimDirection * SpawnOffsetDistance);

        // Spawn parameters
        FActorSpawnParameters ActorSpawnParams;
        ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        // Spawn the projectile with the adjusted direction
        AProjectile* SpawnedProjectile = world->SpawnActor<AProjectile>(Projectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
			
				if(FireSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
				}

				if(FireAnimation != NULL && AnimInstance != NULL)
				{
					AnimInstance->Montage_Play(FireAnimation, 1.0f);
				}
		}
	}
}
