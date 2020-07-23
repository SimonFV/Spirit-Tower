
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

    private bool tcpIsConnected = false;

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

    // Conecta el cliente
    public void ConnectTCP()
    {
        if (!tcpIsConnected)
        {
            try
            {
                receive_msg_tcp = "";
                tcpClient = new TcpClient();
                tcpClient.Connect(ip, port);

                receive_msg_udp = "";
                udpClientSend = new UdpClient();
                udpClientSend.Connect(ip, port);
                Thread receiveThread = new Thread(new ThreadStart(ReceivedUDP));
                receiveThread.Start();
                tcpIsConnected = true;
            }
            catch (SocketException)
            {
                Debug.Log("Error durante la conexión del socket.");
            }
        }

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
        try
        {
            if (!tcpClient.Connected || string.IsNullOrEmpty(send_msg)) { return; }

            //Set up async read
            var stream = tcpClient.GetStream();

            //send message
            byte[] msg = Encoding.ASCII.GetBytes(send_msg);
            stream.Write(msg, 0, msg.Length);
        }
        catch (Exception)
        {
            tcpIsConnected = false;
            Pause.gameIsPaused = true;
        }
    }

    //Envía un mensaje por UDP
    public void sendMsgUDP(string send_msg)
    {
        try
        {
            Byte[] senddata = Encoding.ASCII.GetBytes(send_msg);
            udpClientSend.Send(senddata, senddata.Length);
        }
        catch (Exception)
        {
            tcpIsConnected = false;
            Pause.gameIsPaused = true;
        }
    }

    void FixedUpdate()
    {
        if (tcpIsConnected)
        {
            //Set up async read
            tcpStream = tcpClient.GetStream();
            tcpStream.BeginRead(tcpBuffer, 0, tcpBuffer.Length, ReceivedTCP, null);
        }
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
                Debug.Log(receive_msg_tcp);
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
                Debug.Log(receive_msg_udp);
            }

        }
    }

    public TcpClient getClient()
    {
        return tcpClient;
    }

}
