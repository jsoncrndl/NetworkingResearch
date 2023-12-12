// Fill out your copyright notice in the Description page of Project Settings.


#include "P2PDriver.h"

UP2PDriver::UP2PDriver(const FObjectInitializer& initializer)
{
	
}

void UP2PDriver::ACKPacket(const UNetworkPacket& packet)
{

}

UNetworkPacket UP2PDriver::MakeACKPacket(const UNetworkPacket& receivedPacket)
{
	UNetworkPacket packet;

	packet.SetFlag(EPacketFlags::ACK);
	packet.senderID = receivedPacket.senderID;
	packet.sequence = receivedPacket.sequence;

	return packet;
}

UPeerLink* UP2PDriver::Connect(const FInternetAddr& addr)
{
	return nullptr;
}

void UP2PDriver::Disconnect(UPeerLink* peer)
{
}

void UP2PDriver::Send(UNetworkPacket packet)
{
	// for each peerLink, send to peer;
	UPeerLink* link;

	int32 bytesSent;
	socket->SendTo(packet.data.GetData(), packet.data.Num(), bytesSent, *link->GetRemoteAddress());
	//Snapshot of

}

void UP2PDriver::Tick(float deltaSeconds)
{
	for (uint32 dataSize; socket->HasPendingData(dataSize);)
	{
		socket->RecvFrom()
	}

}
