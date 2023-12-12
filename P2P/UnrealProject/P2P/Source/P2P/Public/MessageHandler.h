// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionFactory.h"
#include "NetworkPeer.h"
#include "NetworkPacket.h"
#include "P2PSimulatedGameMode.h"
#include "MessageHandler.generated.h"

/**
 * The message handler receives packets from the P2P driver and runs code based on the received packets. 
 * By the time a message is received in this class, it can be assumed that every peer already has the message.
 * 
 * Sending ACKs and checking for out-of-order or duplicate packets is all handled by the P2P driver.
 */
UCLASS()
class P2P_API UMessageHandler : public UObject
{
	GENERATED_BODY()

private:
	TArray<TArray<uint8>> m_actionQueue;
	UNetworkPeer* m_peer;
	UActionFactory* m_actionFactory;
	AP2PSimulatedGameMode* m_gameMode;

	//If the message is an action, add it to the queue of pending actions and send an ACK
	void ReceiveAction(uint8 fromPlayer, UNetworkPacket packet);
	void BroadcastMessage(const UNetworkPacket& packet);

public:
	void EnqueueSerializedAction(const TArray<uint8>& packet);
	void ReceivePacket(uint8 fromPlayer, UNetworkPacket packet);
	void SetPeer(UNetworkPeer* peer);
	void SendAllActions();
	void SetActionFactory(UActionFactory* actionFactory);
	AP2PSimulatedGameMode* GetGameMode();
	void SetGameMode(AP2PSimulatedGameMode* gameMode);
	UNetworkPacket MakeActionPacket(UAction action);
	UNetworkPacket MakeACKPacket(UNetworkPacket receivedPacket);
};
