// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "Engine/NetDriver.h"
#include "Engine/NetworkDelegates.h"
#include "LobbyServer.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class LOBBYSERVER_API ULobbyServer : public UObject
{
	GENERATED_BODY()

protected:
	FSocket* m_listenSocket;
	TMap<FSocket*, bool> m_connections;

	virtual void AddConnection(FSocket* connection);
	virtual void RemoveConnection(FSocket* connection);

public:
	// The status of a connection when it first connects. Does it need to send a ready message?
	bool defaultConnectionReadyStatus = false;
	uint8 maxConnections;

	UFUNCTION(BlueprintCallable)
	virtual void Start(FString address);
	UFUNCTION(BlueprintCallable)
	virtual void Stop();
	UFUNCTION(BlueprintCallable)
	virtual void Tick();
	virtual void BeginDestroy() override;
};