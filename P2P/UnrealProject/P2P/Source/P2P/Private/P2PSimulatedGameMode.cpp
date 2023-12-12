// Fill out your copyright notice in the Description page of Project Settings.


#include "P2PSimulatedGameMode.h"

AP2PSimulatedGameMode::AP2PSimulatedGameMode()
{
	bPauseable = false;
	m_simulation = NewObject<UGameSimulation>();
}

void AP2PSimulatedGameMode::BeginPlay()
{

}

int32 AP2PSimulatedGameMode::GetSequence()
{
	return 0;
}

int32 AP2PSimulatedGameMode::GetLocalPlayerID()
{
	return 0;
}

void AP2PSimulatedGameMode::RegisterActor(ASimulatedActor* actor)
{
	m_simulation->AddSimulatedActor(actor);
}
