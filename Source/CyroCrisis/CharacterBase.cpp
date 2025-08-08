#include "CharacterBase.h"

#include "AmmoBase.h"
#include "DeathmatchGameState.h"
#include "DefaultGameModeBase.h"
#include "HUDBase.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "WeaponsBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

class AHUDBase;

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialise the capsule component for character collision
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	// Set-up for First Person Camera
	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FPSCamera->SetupAttachment(GetCapsuleComponent());
	FPSCamera->AddRelativeLocation(FVector(-39.56f, 1.75f, 64.0f));
	FPSCamera->bUsePawnControlRotation = true;

	// Set-up for hands mesh
	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));
	HandsMesh->SetOnlyOwnerSee(true);
	HandsMesh->SetupAttachment(FPSCamera);
	HandsMesh->bCastDynamicShadow = false;
	HandsMesh->CastShadow = false;
	HandsMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	HandsMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Initialises weapon index for switching weapons
	WeaponIndex = 0;

	// Initialise health properties
	FullHealth = 100.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;
	
	OnHealthPickup.AddDynamic(this, &ACharacterBase::HandleHealthPickup);
	OnShot.AddDynamic(this, &ACharacterBase::OnShotTriggeredHandler);

	SetupStimulusSource();
}

void ACharacterBase::HandleHealthPickup(float Amount)
{
	UpdateHealth(+Amount);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Set movement capabilities for the character 
	if(GetMovementComponent())
	{
		GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
		GetMovementComponent()->GetNavAgentPropertiesRef().bCanWalk = true;
	}

	// Spawn primary weapon and attach it
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	
	CurrentWeapon = GetWorld()->SpawnActor<AWeaponsBase>(PrimaryWeaponClass, SpawnParams);
	if(CurrentWeapon)
	{
		WeaponArray.Add(CurrentWeapon); // Add weapon to inventory
		AttachWeapon();
	}

	// Bind the ammo pickup handler to the delegate
	AAmmoBase::OnPickupTriggeredDelagate.AddUObject(this, &ACharacterBase::OnPickupTriggeredHandler);

	AnimInstance = HandsMesh->GetAnimInstance();
	
	UpdateHealthUI();
}

// Function to get the currently equipped gun
AWeaponsBase* ACharacterBase::GetGun() const
{
	return CurrentWeapon;
}

AHUDBase* ACharacterBase::GetHUD() const
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	return PlayerController ? Cast<AHUDBase>(PlayerController->GetHUD()) : nullptr;
}

void ACharacterBase::ResetPlayerHealth()
{
	Health = FullHealth;
	HealthPercentage = 1.0f;
	UpdateHealthUI();
}

// Function to fire the currently equipped weapon
void ACharacterBase::OnFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}

// Function to reload currently equipped weapon
void ACharacterBase::ReloadWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Reload();
	}
}

// Function to attach currently equipped weapon to the character's hands
void ACharacterBase::AttachWeapon()
{
	if(CurrentWeapon)
	{
		if(true|| IsLocallyControlled())
		{
			CurrentWeapon->AttachToComponent(HandsMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}
		else
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}
	}
}

// Switch to the next weapon in the inventory
void ACharacterBase::SwitchNextWeapon()
{
	if(CurrentWeapon)
	{
		if(WeaponArray.Num() > WeaponIndex + 1)
		{
			++WeaponIndex;
			if(AWeaponsBase* NextWeapon = WeaponArray[WeaponIndex])
			{
				CurrentWeapon->GetWeaponMesh()->SetRelativeScale3D(OpenScale);
				CurrentWeapon = NextWeapon;
				CurrentWeapon->GetWeaponMesh()->SetRelativeScale3D(DefaultScale);
			}
		}
		else
		{
			if (WeaponIndex > 0)
			{
				WeaponIndex = 0;
			}
		}
	}
}

// Switch to previous weapon in the inventory
void ACharacterBase::SwitchPreviousWeapon()
{
	if(CurrentWeapon)
	{
		if(WeaponIndex - 1 >= 0)
		{
			--WeaponIndex;
			if(AWeaponsBase* NextWeapon = WeaponArray[WeaponIndex])
			{
				CurrentWeapon->GetWeaponMesh()->SetRelativeScale3D(OpenScale);
				CurrentWeapon = NextWeapon;
				CurrentWeapon->GetWeaponMesh()->SetRelativeScale3D(DefaultScale);
			}
		}
		else
		{
			if (WeaponIndex > 0)
			{
				WeaponIndex = 0;
			}
		}
	}
}

// Update health and UI based on health changes
void ACharacterBase::UpdateHealth(float HealthChange)
{
	Health = FMath::Clamp(Health + HealthChange, 0.0f, FullHealth);
	UE_LOG(LogTemp, Display, TEXT("HealthChanged"));
	HealthPercentage = Health / FullHealth;
	UpdateHealthUI(); // Update the UI whenever health changes

	if (Health <= 0.0f)
	{
		// Get the game mode and call the respawn function
		ADefaultGameModeBase* GameMode = Cast<ADefaultGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->RespawnPlayer(this);
		}
	}
}

// Update the health UI to reflect current health status
void ACharacterBase::UpdateHealthUI()
{
		// Get the player controller and HUD
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			AHUDBase* HUD = Cast<AHUDBase>(PlayerController->GetHUD());
			if (HUD && HUD->HealthBarWidget)
			{
				int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100 );
				FText HPText = FText::FromString(FString::Printf(TEXT("%d%%"), HP));
				HUD->HealthBarWidget->UpdateHealthBar(HealthPercentage, HPText);
			}
		}
}

void ACharacterBase::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

// Handler for when an ammo pickup is triggered
void ACharacterBase::OnPickupTriggeredHandler(AAmmoBase* pickup)
{
	if (!hasFunctionRun)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
	
		AWeaponsBase* Weapon = GetWorld()->SpawnActor<AWeaponsBase>(SecondaryWeaponClass, SpawnParams);
		CurrentWeapon->GetWeaponMesh()->SetRelativeScale3D(OpenScale);
		CurrentWeapon = Weapon;
		CurrentWeapon->GetWeaponMesh()->SetRelativeScale3D(DefaultScale);
		Weapon->AttachToComponent(HandsMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		WeaponArray.Add(Weapon);
		hasFunctionRun = true;
	}

	if (CurrentWeapon->IsSecondaryWeapon())
	{
		CurrentWeapon->ReplenishAmmo();
	}
}

void ACharacterBase::OnShotTriggeredHandler(float Amount)
{
	UpdateHealth(-Amount);
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Set up player input bindings
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacterBase::OnFire);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACharacterBase::ReloadWeapon);

	PlayerInputComponent->BindAction("SwitchNextWeapon", IE_Pressed, this, &ACharacterBase::SwitchNextWeapon);

	PlayerInputComponent->BindAction("SwitchPreviousWeapon", IE_Pressed, this, &ACharacterBase::SwitchPreviousWeapon);
}