#include "HealthPickup.h"

#include "AICharacter.h"
#include "CharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"

AHealthPickup::AHealthPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->InitSphereRadius(50.0f);

	HealthAmount = 25.0f;
	RespawnTime = 10.0f;

	// Initialise rotation values
	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 0.f;

}

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();

	if(CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnBeginOverlp);
	}
	
}

void AHealthPickup::Respawn()
{
	PickupMesh->SetRelativeScale3D(DefaultScale);
	SetActorEnableCollision(true);
}

void AHealthPickup::OnPickedUp()
{
	PickupMesh->SetRelativeScale3D(OpenScale);
	SetActorEnableCollision(false);
	
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AHealthPickup::Respawn, RespawnTime, false);
}

void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Create a new rotator from the defined pitch, yaw and roll values
	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);

	// Convert the rotator to a quaternion for smooth rotation
	FQuat QuatRotation = FQuat(NewRotation);

	// Apply local rotation to actor
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

}

void AHealthPickup::OnBeginOverlp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(OtherActor);
	AAICharacter* AICharacter = Cast<AAICharacter>(OtherActor);
	
	if (PlayerCharacter)
	{
		PlayerCharacter->OnHealthPickup.Broadcast(HealthAmount);
		OnPickedUp();
	}
}

