using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;

public abstract class ConnectionManager : MonoBehaviour
{
    public abstract void StartServer(string port);
    public abstract void ConnectToLocalServer(string port);
}
