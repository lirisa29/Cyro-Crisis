#include "AmmoBase.h"

#include "AICharacter.h"
#include "CharacterBase.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

// Delegate signature for when the ammo pickup is triggered
FOnPickupTriggeredSignature AAmmoBase::OnPickupTriggeredDelagate;
FOnAIPickupTriggered AAmmoBase::OnAIPickupTriggeredDelagate;

AAmmoBase::AAmmoBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set initial ammo amount for this pickup
	ammoAmount = 64;

	// Initialise rotation values
	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 0.f;
}

void AAmmoBase::BeginPlay()
{
	Super::BeginPlay();

	// Get the sphere collider component for overlap detection
	SphereTrigger = Cast<USphereComponent>(GetDefaultSubobjectByName("SphereCollider"));

	// Check if the sphere trigger was found
	if(SphereTrigger)
	{
		// Bind the overlap event to the OnBeginOverlap function
		SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBase::OnBeginOverlp);
	}
}

void AAmmoBase::OnBeginOverlp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Ensure the overlapping actor is valid and not this pickup
	if(OtherActor && OtherActor != this)
	{
		ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(OtherActor);
		AAICharacter* AICharacter = Cast<AAICharacter>(OtherActor);

		// Check if the overlapping actor is a player character
		if(PlayerCharacter)
		{
			// Broadcast the pickup event to the listeners
			OnPickupTriggeredDelagate.Broadcast(this);
		}

		if(AICharacter)
		{
			// Broadcast the pickup event to the listeners
			OnAIPickupTriggeredDelagate.Broadcast(this);
		}
	}
}

void AAmmoBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Create a new rotator from the defined pitch, yaw and roll values
	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);

	// Convert the rotator to a quaternion for smooth rotation
	FQuat QuatRotation = FQuat(NewRotation);

	// Apply local rotation to actor
	
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

