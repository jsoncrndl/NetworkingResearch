// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyServer.h"
#include <IPAddress.h>
#include "Common/UdpSocketBuilder.h"

void ULobbyServer::AddConnection(FSocket* connection)
{
	if (connection == nullptr)
	{
		return;
	}

	TSharedPtr<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	connection->GetPeerAddress(*RemoteAddress);

	UE_LOG(LogTemp, Warning, TEXT("Added connection from %s"), *RemoteAddress->ToString(true));
}

void ULobbyServer::RemoveConnection(FSocket* connection)
{
	m_connections.Remove(connection);
}

// Turn on the server
void ULobbyServer::Start(FString address)
{
	if (m_listenSocket != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Server is already started! Ignoring..."));
		return;
	}

	FIPv4Endpoint endpoint;
	bool validIp = FIPv4Endpoint::Parse(address, endpoint);

	if (validIp)
	{
		m_listenSocket = FTcpSocketBuilder("Lobby Server").AsNonBlocking().BoundToEndpoint(endpoint).Listening(10);
		UE_LOG(LogTemp, Warning, TEXT("Initializing lobby at %s"), *endpoint.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid IP address"));
	}

}



void ULobbyServer::Stop()
{
	if (m_listenSocket != nullptr)
	{
		m_listenSocket->Close();
		m_listenSocket = nullptr;
	}

	for (auto& connection : m_connections)
	{
		connection.Key->Close();
	}
	m_connections.Empty();
}

void ULobbyServer::Tick()
{
	if (m_listenSocket == nullptr)
	{
		return;
	}

	if (bool hasConnection; m_listenSocket->HasPendingConnection(hasConnection) && hasConnection)
	{
		FString description;

		AddConnection(m_listenSocket->Accept(description));
		UE_LOG(LogTemp, Warning, TEXT("Accepted connection with description %s"), *description);
	}

}

void ULobbyServer::BeginDestroy()
{
	Super::BeginDestroy();
	Stop();
}