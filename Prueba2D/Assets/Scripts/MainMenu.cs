using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Net.Sockets;

public class MainMenu : MonoBehaviour
{
    public Text status;

    public void playGame()
    {
        status.text = "Conectandose al servidor...";
        Client.Instance.ConnectTCP();
        try
        {
            if (Client.Instance.isConnected())
            {
                SceneManager.LoadScene(3);
            }
            else
            {
                status.text = "Servidor no encontrado.";
            }
        }
        catch (SocketException)
        {
            status.text = "Error en la creacion del socket.";
        }
    }

    public void quitGame()
    {
        Application.Quit();
    }
}