using System.Collections;
using System.Collections.Generic;
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
    public List<string> lista_msjs = new List<string>();

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

    // Update is called once per frame
    void Update()
    {

        if (lista_msjs.Count != 0)
        {
            procesarDatos(lista_msjs[0]);
            lista_msjs.RemoveAt(0);
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
                lista_msjs.Add(receive_msg_tcp);
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
                lista_msjs.Add(receive_msg_udp);
            }

        }
    }

    public void procesarDatos(string data)
    {

        Debug.Log("Inicio");
        Debug.Log(data);

        string key = "";
        int i = 0;
        for (i = 0; i < data.Length && data[i] != ','; i++)
        {
            key += data[i];
        }
        //ERROR
        i++;
        data = data.Remove(0, i);

        //Debug.Log(key);

        // Guardando ruta en matriz
        List<List<float>> list2 = new List<List<float>>();
        i = 0;
        string valor_x;
        string valor_y;
        //ERROR
        while (data.Length != 1) // El msj tiene un caracter extra¿?
        {

            // Saca el valor de x
            i = 0;
            valor_x = "";
            while (data[i] != '_')
            {
                valor_x += data[i];
                i++;
            }
            i++;
            data = data.Remove(0, i);

            // Saca el valor de y
            i = 0;
            valor_y = "";
            while (data[i] != '/')
            {
                valor_y += data[i];
                i++;
            }
            i++;
            data = data.Remove(0, i);

            // Push, valor_x, valor_y
            List<float> list1 = new List<float>();
            list1.Add(PlayerMovement.escaleToClientX(Int16.Parse(valor_x)) + 0.5f);
            list1.Add(PlayerMovement.escaleToClientY(Int16.Parse(valor_y)) + 0.5f);
            list2.Add(list1);

        }

        Patrulla valor = Patrulla.gameObjects[Int16.Parse(key)].GetComponent<Patrulla>();
        valor.lista_matriz = list2;
        valor.follow = false;
        valor.enviar_mensaje = false;
        valor.currentTarget = 0;

        Debug.Log("Fin");

    }

    public bool isConnected()
    {
        return tcpIsConnected;
    }

}
