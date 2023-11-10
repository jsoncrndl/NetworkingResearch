using Packets;
using System.Net;
using System.Net.Sockets;

namespace STUN
{
    internal class Server
    {
        TcpListener server;
        TcpClient client1;
        TcpClient client2;

        int port;

        public Server(int port) 
        {
            server = new TcpListener(IPAddress.Any, port);
        }

        public void Listen()
        {
            server.Start();
        }

        public async void GetClients()
        {
            Console.WriteLine("Waiting for clients...");

            client1 = await server.AcceptTcpClientAsync();
            Console.WriteLine("Client 1 connected from " + client1.Client.RemoteEndPoint);

            client2 = await server.AcceptTcpClientAsync();
            Console.WriteLine("Client 2 connected from " + client2.Client.RemoteEndPoint);

            await client1.GetStream().WriteAsync(new PeerInfo() { endpoint = client2.Client.RemoteEndPoint as IPEndPoint }.Serialize());
            await client2.GetStream().WriteAsync(new PeerInfo() { endpoint = client1.Client.RemoteEndPoint as IPEndPoint }.Serialize());

            Console.ReadKey();
            Environment.Exit(0);
        }
    }
}
