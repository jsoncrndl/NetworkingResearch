# Unity UTP and NGO
This page includes information on Unity's networking system: the low-level UTP package, and high-level NGO package.

## UTP
Unity Transport (UTP) provides some basic customizable networking features:
* Abstraction over UDP and WebSockets
* Manages connections
    * Connect/accept messages
    * Disconnect message
* Customizable network pipeline for reliable packet sending, breaking up big packets, and simulating network conditions
* Optional packet encryption

## NGO
Netcode for GameObjects (NGO) is a high-level networking library built on UTP. It provides several useful features for programming in a client-server architecture:
* Remote Procedure Calls (RPCs)
* Synced network variables
* Object ownership
* Scene management
* Synced components:
    * NetworkTransform
    * NetworkRigidbody
    * NetworkAnimator

## Links
* [UTP Documentation](https://docs.unity3d.com/Packages/com.unity.transport@2.0/manual/index.html)
* [NGO Documentation](https://docs-multiplayer.unity3d.com/netcode/current/about/)