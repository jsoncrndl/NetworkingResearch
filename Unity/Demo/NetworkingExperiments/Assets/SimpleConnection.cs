using UnityEngine;
using Unity.Collections;
using Unity.Networking.Transport;
using System;

public class SimpleConnection : ConnectionManager
{
    NetworkDriver m_Driver;
    private NativeList<NetworkConnection> m_Connections;
    private NetworkConnection serverConnection => m_Connections[0];
    public bool isServer { get; private set; }
    public bool isClient { get; private set; }

    public override void StartServer(string port)
    {
        if (m_Driver.IsCreated)
        {
            Debug.LogWarning("Network driver already created! Skipping...");
            return;
        }

        ushort outPort;
        bool valid = ushort.TryParse(port, out outPort);
        if (!valid) return;

        m_Driver = NetworkDriver.Create();

        isServer = true;

        m_Connections = new NativeList<NetworkConnection>(16, Allocator.Persistent);

        var endpoint = NetworkEndpoint.AnyIpv4.WithPort(outPort);
        if (m_Driver.Bind(endpoint) != 0)
        {
            Debug.LogError("Failed to bind to port " + outPort);
            return;
        }
        m_Driver.Listen();
        Debug.Log("Listening on port " + outPort);
    }

    public override void ConnectToLocalServer(string port)
    {
        if (m_Driver.IsCreated)
        {
            Debug.LogWarning("Network driver already created! Skipping...");
            return;
        }

        ushort outPort;
        bool valid = ushort.TryParse(port, out outPort);

        if (!valid) return;

        m_Connections = new NativeList<NetworkConnection>(1, Allocator.Persistent);

        isClient = true;
        m_Driver = NetworkDriver.Create();
        Debug.Log("Created client on port " + m_Driver.GetLocalEndpoint().Port);

        NetworkEndpoint endpoint = NetworkEndpoint.LoopbackIpv4.WithPort(outPort);
        m_Connections.Add(m_Driver.Connect(endpoint));
    }

    private void Update()
    {
        if (isServer)
        {
            UpdateServer();
        }
        if (isClient)
        {
            UpdateClient();
        }
    }


    // Update is called once per frame
    void UpdateServer()
    {
        m_Driver.ScheduleUpdate().Complete();

        // Clean up connections.
        for (int i = 0; i < m_Connections.Length; i++)
        {
            if (!m_Connections[i].IsCreated)
            {
                m_Connections.RemoveAtSwapBack(i);
                i--;
            }
        }

        NetworkConnection c;
        while ((c = m_Driver.Accept()) != default)
        {
            m_Connections.Add(c);
            Debug.Log("Accepted a connection.");
        }

        for (int i = 0; i < m_Connections.Length; i++)
        {
            DataStreamReader stream;
            NetworkEvent.Type cmd;
            while ((cmd = m_Driver.PopEventForConnection(m_Connections[i], out stream)) != NetworkEvent.Type.Empty)
            {
                if (cmd == NetworkEvent.Type.Data)
                {
                    uint number = stream.ReadUInt();
                    Debug.Log($"Got {number} from a client, adding 2 to it.");
                    number += 2;

                    m_Driver.BeginSend(NetworkPipeline.Null, m_Connections[i], out var writer);
                    writer.WriteUInt(number);
                    m_Driver.EndSend(writer);
                }
                else if (cmd == NetworkEvent.Type.Disconnect)
                {
                    Debug.Log("Client disconnected from the server.");
                    m_Connections[i] = default;
                    break;
                }
            }

        }
    }

    void UpdateClient()
    {
        m_Driver.ScheduleUpdate().Complete();

        if (!serverConnection.IsCreated)
        {
            return;
        }

        Unity.Collections.DataStreamReader stream;
        NetworkEvent.Type cmd;
        while ((cmd = serverConnection.PopEvent(m_Driver, out stream)) != NetworkEvent.Type.Empty)
        {
            if (cmd == NetworkEvent.Type.Connect)
            {
                Debug.Log("We are now connected to the server.");

                uint value = 1;
                m_Driver.BeginSend(serverConnection, out var writer);
                writer.WriteUInt(value);
                m_Driver.EndSend(writer);
            }
            else if (cmd == NetworkEvent.Type.Data)
            {
                uint value = stream.ReadUInt();
                Debug.Log($"Got the value {value} back from the server.");

                serverConnection.Disconnect(m_Driver);
                m_Connections[0] = default;
            }
            else if (cmd == NetworkEvent.Type.Disconnect)
            {
                Debug.Log("Client got disconnected from server.");
                m_Connections[0] = default;
            }
        }
    }
    void OnDestroy()
    {
        if (m_Driver.IsCreated)
        {
            m_Driver.Dispose();
            m_Connections.Dispose();
        }
    }
}
