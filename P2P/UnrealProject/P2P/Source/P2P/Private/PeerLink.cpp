// Fill out your copyright notice in the Description page of Project Settings.


#include "PeerLink.h"

UPeerLink::UPeerLink(const FObjectInitializer&)
{
}


bool UPeerLink::Send(UNetworkPacket packet)
{
    return false;
}

UNetworkPacket UPeerLink::Receive()
{
    /*const int32 bufferSize = 1028;
    uint8 buffer[bufferSize];
    int32 bytesRead;*/

    //m_socket->RecvFrom(buffer, bufferSize, bytesRead, fromAddr)
    return UNetworkPacket();
}

TSharedPtr<FInternetAddr> UPeerLink::GetRemoteAddress()
{
    return m_addr;
}
