using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System;

public class MainMenu : MonoBehaviour
{
    public Text status;

    public void playGame()
    {
        status.text = "Conectandose al servidor...";
        Client.Instance.ConnectTCP();
        try
        {
            if (Client.Instance.getClient().Connected)
            {
                SceneManager.LoadScene(1);
            }
            else
            {
                status.text = "Servidor no encontrado.";
            }
        }
        catch (SocketException)
        {
            status.text = "Error en la creación del socket.";
        }
    }

    public void quitGame()
    {
        Application.Quit();
    }
}