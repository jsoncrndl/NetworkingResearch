// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PeerLink.h"
#include "NetworkPacket.h"
#include "Sockets.h"
#include "P2PDriver.generated.h"

/**
 * This is the main interface used to communicate with other peers. It is initialized 
 */
UCLASS()
class P2P_API UP2PDriver : public UObject
{
	GENERATED_BODY()
public:
	using AddressMap = TMap<TSharedPtr<FInternetAddr>, void*, FDefaultSetAllocator, FInternetAddrKeyMapFuncs<void*>>;

private:

	AddressMap addressMap;
	FSocket* socket;

	void ACKPacket(const UNetworkPacket& packet);
	UNetworkPacket MakeACKPacket(const UNetworkPacket& packet);

public:

	UP2PDriver(const FObjectInitializer&)
	{
	}

	UPeerLink* Connect(const FInternetAddr& addr);
	void Disconnect(UPeerLink* peer);
	void Send(UNetworkPacket packet);
	void Tick(float deltaSeconds);
};
