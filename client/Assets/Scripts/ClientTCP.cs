
using UnityEngine;
using UnityEngine.UI;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System;

public class ClientTCP : MonoBehaviour{   
    TcpClient tcpClient;
    byte[] tcpBuffer = new byte[4096];

    string receive_msg;
    NetworkStream tcpStream;
    public string ip ="127.0.0.1";
    public int port = 54000;

    public Text tcpText;
    public Button SendTCP;
    public InputField input;



    public void sendMsgTCP(){
        if(!tcpClient.Connected || string.IsNullOrEmpty(input.text)){return;}

        SendTCP.interactable = false;

        //Set up async read
        var stream = tcpClient.GetStream();
        //stream.BeginRead(tcpBuffer, 0, tcpBuffer.Length, MessageReceived, null);

        //send message
        byte[] msg = Encoding.ASCII.GetBytes(input.text);
        stream.Write(msg, 0, msg.Length);
    }

    // Start is called before the first frame update
    void Start(){
        receive_msg = "";
        tcpClient = new TcpClient();
        tcpClient.Connect(ip, port);
    }

    void OnDestroy(){
        if(tcpClient.Connected){
            tcpClient.Close();
        }
    }

    // Update is called once per frame
    void Update(){
        if(!string.IsNullOrEmpty(receive_msg)){
            tcpText.text = receive_msg;
            receive_msg = "";
            SendTCP.interactable = true;
        }
    }

    void FixedUpdate(){
        //Set up async read
        tcpStream = tcpClient.GetStream();
        tcpStream.BeginRead(tcpBuffer, 0, tcpBuffer.Length, MessageReceived, null);
    }


    void MessageReceived(IAsyncResult _result){
        if(_result.IsCompleted && tcpClient.Connected){
            var stream = tcpClient.GetStream();
            int bytesIn = stream.EndRead(_result);

            receive_msg = Encoding.ASCII.GetString(tcpBuffer, 0, bytesIn);
        }
    }
}
