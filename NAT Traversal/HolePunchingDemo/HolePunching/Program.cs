using System.Net;
using System.Net.Sockets;
using System.Text;
using HolePunching;
using Packets;

public class Program
{
    public static void Main(string[] args)
    {
        string input;
        // Get IP
        while (true)
        {
            try
            {
                Console.WriteLine("Enter an IP");
                input = Console.ReadLine();
                
                break;
            }
            catch
            {
                Console.WriteLine("Invalid IP");
            }
        }
        Peer peer = new Peer(IPEndPoint.Parse(input));

        TimeSpan elapsedTime = TimeSpan.Zero;

        MessagingConsole console = new MessagingConsole();

        console.onMessageSent += peer.SendMessage;
        peer.onReceiveMessage += console.ReceiveMessage;

        while (true)
        {
            DateTime time = DateTime.Now;
            peer.Update((float)elapsedTime.TotalSeconds);

            if (peer.isConnected)
            {
                console.Update();
            }

            elapsedTime = DateTime.Now - time;
        }
    }
}