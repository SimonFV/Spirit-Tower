using UnityEngine;
using UnityEngine.UI;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System;
using System.Threading;

public class ClientUDP : MonoBehaviour
{   
    private readonly object objLock = new object();
    UdpClient udpClientSend;

    string receive_msg_udp;
    public string ip ="127.0.0.1";
    public int port = 54000;
    public int listen_port = 52000;

    public Text udpText;
    public Button SendUDP;
    public InputField input;


    public void sendMsgUDP(){
        if(string.IsNullOrEmpty(input.text)){return;}

        SendUDP.interactable = false;

        udpClientSend.Connect(ip, port);
        Byte[] senddata = Encoding.ASCII.GetBytes(input.text);
        udpClientSend.Send(senddata, senddata.Length);
    }

    // Start is called before the first frame update
    void Start()
    {
        receive_msg_udp = "";
        udpClientSend = new UdpClient();
        Thread receiveThread = new Thread(new ThreadStart(ReceiveUDP));
        receiveThread.Start();
    }

    // Update is called once per frame
    void Update()
    {   
        lock(objLock){
            if(!string.IsNullOrEmpty(receive_msg_udp)){
                udpText.text = receive_msg_udp;
                receive_msg_udp = "";
                SendUDP.interactable = true;
            }
        }
    }

    void ReceiveUDP(){
        UdpClient udpClientReceive = new UdpClient(listen_port);
        IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Any, 0);
        while(true){
            //UDP listen
            Byte[] receiveBytes = udpClientReceive.Receive(ref RemoteIpEndPoint);
            lock(objLock){
                receive_msg_udp = Encoding.ASCII.GetString(receiveBytes);
            }

        }
    }
}
