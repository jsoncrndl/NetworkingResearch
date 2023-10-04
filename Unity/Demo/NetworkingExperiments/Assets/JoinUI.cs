using TMPro;
using UnityEngine;

public class JoinUI : MonoBehaviour
{
    public TMP_InputField portField;
    public ConnectionManager networkManager;

    private void Start()
    {
        networkManager = GetComponent<ConnectionManager>();
    }

    public void ConnectToPort()
    {
        networkManager.ConnectToLocalServer(portField.text);
    }

    public void StartServer()
    {
        networkManager.StartServer(portField.text);
    }
}

