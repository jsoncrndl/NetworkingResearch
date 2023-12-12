// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameSimulation.h"
#include "P2PSimulatedGameMode.generated.h"

class AP2PPlayerController;
/**
 * 
 */
UCLASS()
class P2P_API AP2PSimulatedGameMode : public AGameModeBase
{
	GENERATED_BODY()
	UGameSimulation* m_simulation;
	AP2PPlayerController* m_playerController;

public:
	AP2PSimulatedGameMode();
	virtual void BeginPlay() override;

	int32 GetSequence();
	int32 GetLocalPlayerID();
	void RegisterActor(ASimulatedActor* actor);
};
