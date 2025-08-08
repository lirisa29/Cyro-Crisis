#include "AICharacter.h"

#include "AIControllerBase.h"
#include "AmmoBase.h"
#include "DefaultGameModeBase.h"
#include "WeaponsBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialise the capsule component for character collision
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	SecondaryWeaponAmmoMax = 20;

	SecondaryWeaponAmmo = SecondaryWeaponAmmoMax;

	// Initialise health properties
	FullHealth = 100.0f;
	Health = FullHealth;

	OnAIShot.AddDynamic(this, &AAICharacter::OnAIShotTriggeredHandler);
}

UBehaviorTree* AAICharacter::GetBehaviorTree() const
{
	return Tree;
}

UAnimMontage* AAICharacter::GetMontage() const
{
	return Montage;
}

int AAICharacter::Shoot_Implementation()
{
	if (CurrentWeapon)
	{
			CurrentWeapon->Fire();
	}
	
	if (Montage)
	{
		PlayAnimMontage(Montage);
	}
	return 0;
}

void AAICharacter::OnAIPickupTriggeredHandler(AAmmoBase* pickup)
{
	if (!hasFunctionRun)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
	
		AWeaponsBase* Weapon = GetWorld()->SpawnActor<AWeaponsBase>(SecondaryWeaponClass, SpawnParams);
		CurrentWeapon->GetWeaponMesh()->SetRelativeScale3D(OpenScale);
		CurrentWeapon = Weapon;
		CurrentWeapon->GetWeaponMesh()->SetRelativeScale3D(DefaultScale);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		hasFunctionRun = true;
	}

	if (CurrentWeapon->IsSecondaryWeapon())
	{
		CurrentWeapon->ReplenishAmmo();
	}
}

void AAICharacter::OnAIShotTriggeredHandler(float Amount)
{
	UpdateHealth(-Amount);
}

void AAICharacter::ResetBotHealth()
{
	Health = FullHealth;
}

float AAICharacter::GetHealth() const
{
	return Health;
}

void AAICharacter::CheckHealthAndAvoid()
{
	if (Health < 25.0f)
	{
		AvoidTarget();
	}
}

void AAICharacter::AvoidTarget()
{
	// Example: Move away from the target
	if (AAIControllerBase* AIController = Cast<AAIControllerBase>(GetController()))
	{
		UObject* TargetObject = AIController->GetBlackboardComponent()->GetValueAsObject("TargetActor");
		AActor* TargetActor = Cast<AActor>(TargetObject);
		if (TargetActor)
		{
			FVector DirectionAway = GetActorLocation() - TargetActor->GetActorLocation();
			DirectionAway.Normalize();
			FVector NewLocation = GetActorLocation() + (DirectionAway * 300.0f); // Move 300 units away

			// Move to the new location
			AIController->MoveToLocation(NewLocation);
		}
	}
}

void AAICharacter::UpdateHealth(float HealthChange)
{
	Health = FMath::Clamp(Health + HealthChange, 0.0f, FullHealth);

	if (Health <= 0.0f)
	{
		// Get the game mode and call the respawn function
		ADefaultGameModeBase* GameMode = Cast<ADefaultGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->RespawnBot(this);
		}
	}
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	// Ensure AIController is set after level transition
	if (AAIControllerBase* AIController = Cast<AAIControllerBase>(GetController()))
	{
		// AIController is already set, no need to possess again
	}
	else
	{
		// If the controller is not set, create a new one and possess this character
		AAIControllerBase* NewAIController = GetWorld()->SpawnActor<AAIControllerBase>(AAIControllerBase::StaticClass());
		if (NewAIController)
		{
			// Possess the character with the new AIController
			NewAIController->Possess(this);
		}
	}
	
	// Spawn primary weapon and attach it
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	
	CurrentWeapon = GetWorld()->SpawnActor<AWeaponsBase>(PrimaryWeaponClass, SpawnParams);
	if(CurrentWeapon)
	{
		AttachWeapon();
	}

	AnimInstance = GetMesh()->GetAnimInstance();

	// Bind the ammo pickup handler to the delegate
	AAmmoBase::OnAIPickupTriggeredDelagate.AddUObject(this, &AAICharacter::OnAIPickupTriggeredHandler);
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckHealthAndAvoid();
}

void AAICharacter::AttachWeapon()
{
	if(CurrentWeapon)
	{
		if(true|| IsLocallyControlled())
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}
		else
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}
	}
}

void AAICharacter::SwitchGun()
{
	
}
