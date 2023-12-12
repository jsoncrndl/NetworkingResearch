// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Networking.h"
#include "Engine/NetworkDelegates.h"
#include <PeerLink.h>
#include "NetworkPeer.generated.h"

enum EPeerState
{
	None,
	Lobby,
	Network
};

/**
 * 
 */
UCLASS(BlueprintType)
class P2P_API UNetworkPeer : public UObject
{
	GENERATED_BODY()

private:
	FSocket* m_socket;
	TArray<UPeerLink*> m_peers;
	void SetPeerState(EPeerState type);
	EPeerState m_peerState;

public:
	UFUNCTION(BlueprintCallable)
	bool ConnectToLobby(FString ip);
	UFUNCTION(BlueprintCallable)
	void SendTestMessageToLobby();
	EPeerState GetPeerState();
	void BeginDestroy() override;
	void Disconnect();

	void SendToPeers(TArray<uint8> data);
};