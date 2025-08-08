#include "WeaponsBase.h"

#include "CharacterBase.h"
#include "HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

AWeaponsBase::AWeaponsBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetOnlyOwnerSee(false);
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;
	GunMesh->SetupAttachment(RootComponent);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
	
	WeaponName = "Default Weapon";
	WeaponMaxAmmo = 999;
	MagazineMaxAmmo = 30;
	BaseDamage = 3.0f;

	CurrentTotalAmmo = WeaponMaxAmmo;
	CurrentMagazineAmmo = MagazineMaxAmmo;
	
	reloadTime = 1.0f;
}

void AWeaponsBase::BeginPlay()
{
	Super::BeginPlay();

	if (GunMesh)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(GunMaterial, this);
		DynamicMaterial->SetVectorParameterValue(TEXT("BodyColor"), GunColour);
		GunMesh->SetMaterial(0, DynamicMaterial);
	}

	PlayerCharacter = Cast<ACharacterBase>(GetOwner());
	if(PlayerCharacter)
	{
		PlayerCharacter->GetHUD()->SetAmmo(CurrentMagazineAmmo, CurrentTotalAmmo);
	}
}

void AWeaponsBase::ReplenishAmmo()
{
	CurrentTotalAmmo = WeaponMaxAmmo;
}

bool AWeaponsBase::IsSecondaryWeapon() const
{
	return false;
}

void AWeaponsBase::Fire()
{
	if(Projectile != NULL)
	{
		UWorld* const world = GetWorld();
		if(world != NULL)
		{
			if (CurrentMagazineAmmo > 0)
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
            // For AI, aim directly at the player's current location
            if (PlayerCharacter != nullptr)
            {
                // Get the player's location
                TargetLocation = PlayerCharacter->GetActorLocation();
            }

            // Calculate the direction to the player
            AimDirection = (TargetLocation - MuzzlePos).GetSafeNormal();
            SpawnRotation = AimDirection.Rotation();
        }

			float SpawnOffsetDistance = 200.0f;
			SpawnLocation = MuzzlePos + (AimDirection * SpawnOffsetDistance);

        // Spawn parameters
        FActorSpawnParameters ActorSpawnParams;
        ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        // Spawn the projectile with the adjusted direction
        AProjectile* SpawnedProjectile = world->SpawnActor<AProjectile>(Projectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
				
				--CurrentMagazineAmmo;

				if(PlayerCharacter)
				{
					PlayerCharacter->GetHUD()->SetAmmo(CurrentMagazineAmmo, CurrentTotalAmmo);
				}
				
				if(FireSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
				}

				if(FireAnimation != NULL && AnimInstance != NULL)
				{
					AnimInstance->Montage_Play(FireAnimation, 1.0f);
				}
			}
			else
				if (CurrentTotalAmmo > 0)
				{
					Reload();
				}
		}
	}
}

void AWeaponsBase::Reload()
{
	if (GunMesh)
	{
		if (CurrentMagazineAmmo != MagazineMaxAmmo)
		{
			if (CurrentTotalAmmo - (MagazineMaxAmmo - CurrentMagazineAmmo) >= 0)
			{
				CurrentTotalAmmo -= (MagazineMaxAmmo - CurrentMagazineAmmo);
				CurrentMagazineAmmo = MagazineMaxAmmo;
			}
			else
			{
				CurrentMagazineAmmo += CurrentTotalAmmo;
				CurrentTotalAmmo = 0;
			}
		}
	}

	if(PlayerCharacter)
	{
		PlayerCharacter->GetHUD()->SetAmmo(CurrentMagazineAmmo, CurrentTotalAmmo);
	}
}
