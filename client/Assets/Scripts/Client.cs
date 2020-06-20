using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System;

public class Client : MonoBehaviour{
    public static Client client_instance;
    public static int data_buffer_size = 4096;

    public string server_ip = "127.0.0.1";
    public int server_port = 54000;
    public int my_id = 0;
    public TCP tcp;

    private void Awake(){
        if(client_instance == null){
            client_instance = this;
        }
        else if(client_instance != this){
            Destroy(this);
        }
    }

    private void Start(){
        tcp = new TCP();
    }

    public void conectToServer(){
        tcp.Conect();
    }

    public class TCP{
        TcpClient socket;
        private NetworkStream stream;
        private byte[] receiveBuffer;

        public void Conect(){
            socket = new TcpClient{
                ReceiveBufferSize = data_buffer_size,
                SendBufferSize = data_buffer_size
            };
            receiveBuffer = new byte[data_buffer_size];
            socket.BeginConnect(client_instance.server_ip, 
                                client_instance.server_port, 
                                ConnectCallback, socket);
        }

        private void ConnectCallback(IAsyncResult _result){
            socket.EndConnect(_result);
            if(socket.Connected){
                return;
            }

            stream = socket.GetStream();
            stream.BeginRead(receiveBuffer, 0, data_buffer_size, ReceiveCallback, null);
        }

        private void ReceiveCallback(IAsyncResult _result){
            try{
                int byte_length = stream.EndRead(_result);
                if(byte_length <= 0){
                    //TODO: disconnect
                    return;
                }

                //TODO: handle data
                byte[] _data = new byte[byte_length];
                stream.BeginRead(receiveBuffer, 0, data_buffer_size, ReceiveCallback, null);
            }
            catch{
                //TODO: disconnect
            }
        }

    }
}
