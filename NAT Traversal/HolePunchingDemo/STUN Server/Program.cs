using System.Net;
using System.Net.Sockets;
using System.Text;
using Packets;
using STUN;

public class Program
{
    public static void Main(string[] args)
    {
        Server server = new Server(25565);
        server.Listen();

        server.GetClients();

        while(true)
        {

        }
    }
}