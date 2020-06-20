using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_manager : MonoBehaviour
{
    public static UI_manager ui_instance;
    public GameObject start_menu;
    public InputField user_field;

    private void Awake(){
        if(ui_instance == null){
            ui_instance = this;
        }
        else if(ui_instance != this){
            Destroy(this);
        }
    }

    public void ConnectToServer(){
        start_menu.SetActive(false);
        user_field.interactable = false;
        Client.client_instance.conectToServer();
    }

}
