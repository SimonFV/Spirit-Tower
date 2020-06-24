
using UnityEngine;
using UnityEngine.UI;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System;
using System.Threading;

public class Client : MonoBehaviour{
    private readonly object objLock = new object();
    UdpClient udpClientSend;
    TcpClient tcpClient;
    byte[] tcpBuffer = new byte[4096];

    string receive_msg_tcp;
    string receive_msg_udp;
    NetworkStream tcpStream;
    public string ip ="127.0.0.1";
    public int port = 54000;
    public int listen_port = 52000;

    public Text tcpText;
    public Text udpText;



    public void sendMsgTCP(string send_msg){
        if(!tcpClient.Connected || string.IsNullOrEmpty(send_msg)){return;}

        //Set up async read
        var stream = tcpClient.GetStream();
        //stream.BeginRead(tcpBuffer, 0, tcpBuffer.Length, MessageReceived, null);

        //send message
        byte[] msg = Encoding.ASCII.GetBytes(send_msg);
        stream.Write(msg, 0, msg.Length);
    }

    public void sendMsgUDP(string send_msg){
        Byte[] senddata = Encoding.ASCII.GetBytes(send_msg);
        udpClientSend.Send(senddata, senddata.Length);
    }

    // Start is called before the first frame update
    void Start(){
        receive_msg_tcp = "";
        tcpClient = new TcpClient();
        tcpClient.Connect(ip, port);

        receive_msg_udp = "";
        udpClientSend = new UdpClient();
        udpClientSend.Connect(ip, port);
        Thread receiveThread = new Thread(new ThreadStart(ReceiveUDP));
        receiveThread.Start();
    }

    void OnDestroy(){
        if(tcpClient.Connected){
            tcpClient.Close();
        }
    }

    // Update is called once per frame
    void Update(){
        if(!string.IsNullOrEmpty(receive_msg_tcp)){
            tcpText.text = receive_msg_tcp;
            receive_msg_tcp = "";
        }
        lock(objLock){
            if(!string.IsNullOrEmpty(receive_msg_udp)){
                udpText.text = receive_msg_udp;
                receive_msg_udp = "";
            }
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

            receive_msg_tcp = Encoding.ASCII.GetString(tcpBuffer, 0, bytesIn);
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
