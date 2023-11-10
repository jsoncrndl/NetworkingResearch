using System.Net;

namespace Packets
{
    public struct PeerInfo
    {
        public IPEndPoint endpoint;

        public byte[] Serialize()
        {
            byte[] bytes = new byte[16];
            using (MemoryStream ms = new MemoryStream(bytes))
            {
                ms.Write(endpoint.Address.MapToIPv4().GetAddressBytes(), 0, 4);
                ms.Write(BitConverter.GetBytes(endpoint.Port));
            }

            return bytes;
        }

        public static PeerInfo Deserialize(byte[] bytes)
        {
            PeerInfo info = new PeerInfo();
            info.endpoint = new IPEndPoint(new IPAddress(bytes.Take(4).ToArray()), BitConverter.ToInt32(bytes, 4));
            return info;
        }

        public const int PacketSize = 8;
    }
}
