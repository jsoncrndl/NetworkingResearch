# Hole Punching Demo

This project is a simple P2P messaging app made in c#. It uses a public STUN server to retreive and send the publicly visible IP address of a two clients. The two clients then connect to each other directly, punching a hole through NAT if needed.

## Usage
The server currently is hard-coded to use port 25565, but it will be updated to allow any port shortly.

Run STUN Server project, then run two instances of the HolePunching project. Enter the IP of the public server followed by ":25565" to connect. The clients will then attempt to directly connect to each other.