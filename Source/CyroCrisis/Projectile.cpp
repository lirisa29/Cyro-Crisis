#include "Projectile.h"

#include "AICharacter.h"
#include "CharacterBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionSphere->InitSphereRadius(20.0f);
	CollisionSphere->SetCollisionProfileName("Bullet");
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	RootComponent = CollisionSphere;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwnerActor = GetOwner();

	if (OwnerActor)
	{
		CollisionSphere->IgnoreActorWhenMoving(OwnerActor, true);
	}

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* const OverlappedComponent, AActor* const OtherActor,
	UPrimitiveComponent* const OtherComp, int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if(OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		ACharacterBase* PlayerCharacter = Cast<ACharacterBase>(OtherActor);
		AAICharacter* AICharacter = Cast<AAICharacter>(OtherActor);
		
		if (OtherActor->IsA(ACharacterBase::StaticClass()))
		{
			PlayerCharacter->OnShot.Broadcast(DamageValue);
		}

		if (OtherActor->IsA(AAICharacter::StaticClass()))
		{
			AICharacter->OnAIShot.Broadcast(DamageValue);
		}
	}
}

