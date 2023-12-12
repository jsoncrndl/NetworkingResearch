// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulatedActor.h"
#include <P2PSimulatedGameMode.h>

// Sets default values
ASimulatedActor::ASimulatedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Register this actor with the simulation
	if (GetWorld() != nullptr)
	{
		AP2PSimulatedGameMode* gameMode = Cast<AP2PSimulatedGameMode>(GetWorld()->GetAuthGameMode());
		if (gameMode != nullptr)
		{
			gameMode->RegisterActor(this);
		}

	}

	m_sceneComponent = CreateDefaultSubobject<USimulatedSceneComponent>(FName("P2P Scene Component"));
	CreateDefaultSubobject<USceneComponent>(FName("Scene Component"));
}

// Called when the game starts or when spawned
void ASimulatedActor::BeginPlay()
{
	Super::BeginPlay();
	for (UActorComponent* component : GetComponents())
	{
		USimulatedActorComponent* simulatedComponent = Cast<USimulatedActorComponent>(component);
		if (simulatedComponent != nullptr)
		{
			m_simulatedComponents.Add(simulatedComponent);
		}
	}
}

// Called every frame
void ASimulatedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimulatedActor::SimulateStep()
{
	for (USimulatedActorComponent* component : m_simulatedComponents)
	{
		component->SimulateStep();
	}
}

