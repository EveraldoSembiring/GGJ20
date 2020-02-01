// Fill out your copyright notice in the Description page of Project Settings.


#include "ABullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AABullet::AABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->InitialSpeed = 3000;

}

// Called when the game starts or when spawned
void AABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}