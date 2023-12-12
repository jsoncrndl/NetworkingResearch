// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <ActionFactory.h>
#include <SimulatedActor.h>
#include "GameSimulation.generated.h"

const uint32 TURN_TIME = 50;

/**
 * 
 */
UCLASS()
class P2P_API UGameSimulation : public UObject, public FRunnable
{
	GENERATED_BODY()
	
private:
	TQueue<UAction> m_actionQueue;
	TArray<ASimulatedActor*> m_actors;
	uint32 m_turn;
	uint32 m_elapsedTime;
	bool m_turnDone;
	uint8 m_numPlayers;
	TArray<uint8> m_donePlayers;

	void Simulate();
	void ExecuteAction(const UAction& action);

	void StartTurn();
	bool AllPlayersDone();
	void Tick(float deltaTime);

public:
	uint32 GetTurn();
	void AddSimulatedActor(ASimulatedActor* actor);

	bool Init() override;
	uint32 Run() override;
	void Stop() override;
};
