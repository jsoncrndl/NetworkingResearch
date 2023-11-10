using Packets;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace HolePunching
{
    public class Peer
    {
        public enum PeerState { SERVER, CONNECTING, CONNECTED };
        private PeerState state;
        
        TcpClient tcpClient;
        Socket udpSocket;

        IPEndPoint peerEndpoint;

        float accumulatedTime;
        bool receiving;
        public bool isConnected { get; private set; }

        public event Action<Message> onReceiveMessage;

        public Peer(IPEndPoint endPoint)
        {
            state = PeerState.SERVER;
            tcpClient = new TcpClient();
            tcpClient.Connect(endPoint);
        }

        public void Update(float elapsedSeconds)
        {
            switch (state)
            {
                case PeerState.SERVER:
                    StartP2P();
                    break;
                case PeerState.CONNECTING:
                    UpdateConnecting(elapsedSeconds);
                    break;
                case PeerState.CONNECTED:
                    UpdateConnected(elapsedSeconds);
                    break;
            }

            if (!receiving)
            {
                ReceivePacket();
            }
        }

        private void StartP2P()
        {
            byte[] buffer = new byte[8];
            tcpClient.GetStream().Read(buffer, 0, 8);
            
            PeerInfo info = PeerInfo.Deserialize(buffer);
            peerEndpoint = info.endpoint;
            EndPoint port = tcpClient.Client.LocalEndPoint;

            tcpClient.Close();
            state = PeerState.CONNECTING;
            Console.WriteLine("Connecting to " + peerEndpoint);
            udpSocket = new Socket(SocketType.Dgram, ProtocolType.Udp);
            udpSocket.Bind(port);
        }
        private void UpdateConnecting(float elapsedSeconds)
        {
            accumulatedTime += elapsedSeconds;
            if (accumulatedTime > .5f)
            {
                accumulatedTime = 0;
                // Send connect packet
                udpSocket.SendTo(Encoding.UTF8.GetBytes("Connect"), peerEndpoint);
            }
        }

        private async void ReceivePacket()
        {
            receiving = true;
            byte[] buffer = new byte[1048];

            string message = "Error";
            
            while (udpSocket.Available > 0)
            {
                try
                {
                    int bytes = await udpSocket.ReceiveAsync(buffer, SocketFlags.None);
                    message = Encoding.UTF8.GetString(buffer, 0, bytes);
                }
                catch (SocketException e)
                {
                    Console.WriteLine(e.SocketErrorCode);
                }

                HandlePacket(message);
            }

            receiving = false;
        }

        private void HandlePacket(string message)
        {
            if (state == PeerState.CONNECTING)
            {
                if (message == "Connect" || message == "Accept")
                {
                    Accept();
                }
            }
            else if (isConnected)
            {
                Console.WriteLine("Received " + message);
                if (message.StartsWith("[Message]"))
                {
                    onReceiveMessage?.Invoke(new Message(peerEndpoint.ToString(), message.Substring(9)));
                }
            }
        }

        private void Accept()
        {
            udpSocket.SendTo(Encoding.UTF8.GetBytes("Accept"), peerEndpoint);
            isConnected = true;
            state = PeerState.CONNECTED;
            Console.Clear();
            accumulatedTime = 0;
        }

        private void UpdateConnected(float elapsedSeconds)
        {
            accumulatedTime += elapsedSeconds;

            if (accumulatedTime > 5)
            {
                udpSocket.SendTo(Encoding.UTF8.GetBytes("Keep-Alive"), peerEndpoint);
                accumulatedTime = 0;
            }

            if (!receiving)
            {
                ReceivePacket();
            }
        }


        public void ConnectToPeer(PeerInfo peer)
        {
            state = PeerState.CONNECTING;
        }

        public void SendMessage(string message)
        {
            udpSocket.SendTo(Encoding.UTF8.GetBytes("[Message]" + message), peerEndpoint);
        }
    }
}
