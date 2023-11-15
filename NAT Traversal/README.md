# NAT Traversal
This is part of my research done on various networking techniques used in game development. In this project I look at using NAT traversal to allow two peers to connect directly to each other when they are both behind NAT. This is used by programs like Steam to allow friends to play together without going through the trouble of port-forwarding.

## NAT
Network address translation (NAT) maps one IP address space into another. It can translate a single IP address into another address, but the most common type is one-to-many NAT.

In one-to-many network address translation, many private addresses are hidden behind one public IP address. The NAT device maintains a table mapping the connections to the port it will send through.

## ICE
A system for finding the most direct way for two peers to communicate over the internet, taking into account NAT.
* https://datatracker.ietf.org/doc/html/rfc8445
* First use STUN, then use TURN

## STUN
Session Traversal Utilities for NAT (STUN) is a tool for discovering the ip of devices behind a NAT.

## TURN
In TURN all communications are sent through a relay server.