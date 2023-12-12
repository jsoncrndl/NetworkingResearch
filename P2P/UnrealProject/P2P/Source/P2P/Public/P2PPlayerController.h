// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <NetworkPeer.h>
#include <MessageHandler.h>
#include <Actions.h>
#include "P2PPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class P2P_API AP2PPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UNetworkPeer* m_peer;
	UMessageHandler* m_messenger;
	UActionFactory* m_actionFactory;

public:
	AP2PPlayerController(const FObjectInitializer& init);
	void EnqueueAction(UAction action);
	UActionFactory* GetActionFactory();
};
