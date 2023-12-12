// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkPeer.h"
#include <IPAddress.h>
#include "Common/UdpSocketBuilder.h"
#include <IpNetDriver.h>

bool UNetworkPeer::ConnectToLobby(FString addr)
{
	if (m_socket != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Client is already in a lobby state..."));
		return false;
	}

	FIPv4Endpoint endpoint;
	bool validIp = FIPv4Endpoint::Parse(addr, endpoint);

	m_socket = FTcpSocketBuilder("Peer").AsNonBlocking().BoundToAddress(FIPv4Address::InternalLoopback);
	
	TSharedPtr<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	m_socket->GetAddress(*RemoteAddress);

	UE_LOG(LogTemp, Warning, TEXT("Creating peer socket at %s"), *RemoteAddress->ToString(true));

	bool success = m_socket->Connect(*endpoint.ToInternetAddr());

	if (!success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't connect. Error: %s"), ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetSocketError());
	}

	return success;
}

void UNetworkPeer::SendTestMessageToLobby()
{
}

void UNetworkPeer::BeginDestroy()
{
	Super::BeginDestroy();
	Disconnect();
}

void UNetworkPeer::Disconnect()
{
	//if (m_lobbyConnection != nullptr)
	//{
	//	m_lobbyConnection->Close();
	//	m_lobbyConnection = nullptr;
	//}

	//for (auto& connection : m_peers)
	//{
	//	connection->Close();
	//}
	//m_peers.Empty();
}

void UNetworkPeer::SendToPeers(TArray<uint8> data)
{
	//for (FSocket* peer : m_peers)
	//{
	//	int32 bytesSent;
	//	bool success = peer->Send(data.GetData(), data.Num(), bytesSent);

	//	if (!success)
	//	{
	//		UE_LOG(LogTemp, Fatal, TEXT("Failed to send!"));
	//	}
	//}
}

EPeerState UNetworkPeer::GetPeerState()
{
	return m_peerState;
}

void UNetworkPeer::SetPeerState(EPeerState state)
{
	// Clean up previous state and stuff
	m_peerState = state;
}