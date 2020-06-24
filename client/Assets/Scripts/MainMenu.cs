using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System;

public class MainMenu : MonoBehaviour{   
    public Text status;
    TcpClient tcpClient;
    public string ip ="127.0.0.1";
    public int port = 54000;

    public void playGame(){
        status.text = "Conectandose al servidor...";
        tcpClient = new TcpClient();
        try{
            tcpClient.Connect(ip, port);
        }
        catch(SocketException){
            status.text = "Servidor no encontrado.";
        }
        if(tcpClient.Connected){
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
        }
        
    }

    void OnDestroy(){
        if(tcpClient.Connected){
            tcpClient.Close();
        }
    }

    public void quitGame(){
        Application.Quit();
    }
}
