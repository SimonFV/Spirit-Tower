
using UnityEngine;
using UnityEngine.UI;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System;
using System.Threading;


public class Client : MonoBehaviour
{
    private readonly object objLockUDP = new object();
    private readonly object objLockTCP = new object();
    private UdpClient udpClientSend;
    private TcpClient tcpClient;
    private byte[] tcpBuffer = new byte[4096];

    private string receive_msg_tcp;
    private string receive_msg_udp;
    private NetworkStream tcpStream;
    public string ip = "127.0.0.1";
    public int port = 54000;
    public int listen_port = 52000;



    public static Client Instance { get; private set; }
    void Awake()
    {
        if (Instance != null)
        {
            Destroy(gameObject);
        }
        else
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);
        }

    }


    // Start is called before the first frame update
    void Start()
    {
        receive_msg_tcp = "";
        tcpClient = new TcpClient();
        tcpClient.Connect(ip, port);

        receive_msg_udp = "";
        udpClientSend = new UdpClient();
        udpClientSend.Connect(ip, port);
        Thread receiveThread = new Thread(new ThreadStart(ReceivedUDP));
        receiveThread.Start();
    }

    void OnDestroy()
    {
        if (tcpClient.Connected)
        {
            tcpClient.Close();
        }
    }



    //Envía un mensaje por TCP
    public void sendMsgTCP(string send_msg)
    {

        if (!tcpClient.Connected || string.IsNullOrEmpty(send_msg)) { return; }

        //Set up async read
        var stream = tcpClient.GetStream();

        //send message
        byte[] msg = Encoding.ASCII.GetBytes(send_msg);
        stream.Write(msg, 0, msg.Length);

    }

    //Envía un mensaje por UDP
    public void sendMsgUDP(string send_msg)
    {

        Byte[] senddata = Encoding.ASCII.GetBytes(send_msg);
        udpClientSend.Send(senddata, senddata.Length);

    }


    // Update is called once per frame
    void Update()
    {

        lock (objLockTCP)
        {
            if (!string.IsNullOrEmpty(receive_msg_tcp))
            {
                Debug.Log(receive_msg_tcp);
                receive_msg_tcp = "";
            }
        }
        lock (objLockUDP)
        {
            if (!string.IsNullOrEmpty(receive_msg_udp))
            {
                Debug.Log(receive_msg_udp);
                receive_msg_udp = "";
            }
        }
    }


    void FixedUpdate()
    {
        //Set up async read
        tcpStream = tcpClient.GetStream();
        tcpStream.BeginRead(tcpBuffer, 0, tcpBuffer.Length, ReceivedTCP, null);
    }

    void ReceivedTCP(IAsyncResult _result)
    {
        if (_result.IsCompleted && tcpClient.Connected)
        {
            var stream = tcpClient.GetStream();
            int bytesIn = stream.EndRead(_result);

            lock (objLockTCP)
            {
                receive_msg_tcp = Encoding.ASCII.GetString(tcpBuffer, 0, bytesIn);
            }
        }
    }

    void ReceivedUDP()
    {
        UdpClient udpClientReceive = new UdpClient(listen_port);
        IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Any, 0);
        while (true)
        {
            //UDP listen
            Byte[] receiveBytes = udpClientReceive.Receive(ref RemoteIpEndPoint);
            lock (objLockUDP)
            {
                receive_msg_udp = Encoding.ASCII.GetString(receiveBytes);
            }

        }
    }

}
