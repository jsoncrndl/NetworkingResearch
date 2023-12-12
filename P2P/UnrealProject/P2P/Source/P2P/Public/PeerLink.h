// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkPacket.h"
#include "PeerLink.generated.h"

/**
 * 
 */
UCLASS()
class P2P_API UPeerLink : public UObject
{

	GENERATED_BODY()
	TSharedPtr<FInternetAddr> m_addr;
	TArray<uint8> readBuffer;

	EConnectionState connectionState;
	TSharedPtr<FInternetAddr> remoteAddress;

public:
	UPeerLink(const FObjectInitializer&);

	bool Send(UNetworkPacket packet);
	UNetworkPacket Receive();
	TSharedPtr<FInternetAddr> GetRemoteAddress();
};
