using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMov : MonoBehaviour{
    public float player_speed = 5f;
    public Rigidbody2D player_rb;
    Vector2 movement;

    public Client client;

    // Update is called once per frame
    void Update(){
        movement.x = Input.GetAxisRaw("Horizontal");
        movement.y = Input.GetAxisRaw("Vertical");
    }

    void FixedUpdate(){
        if(Input.GetAxisRaw("Horizontal") != 0 || Input.GetAxisRaw("Vertical") != 0){
            player_rb.MovePosition(player_rb.position + movement * player_speed * Time.fixedDeltaTime);
            client.sendMsgUDP("p"+player_rb.position.ToString("0.0"));
        }
    }
}
