using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerMov : MonoBehaviour{
    
    public float movSpeed = 5f;
    public Rigidbody2D player_rb;

    Vector2 movement;

    // Start is called before the first frame update
    void Start(){
        
    }

    // Update is called once per frame
    void Update()
    {
        movement.x = Input.GetAxis("Horizontal");
        movement.y = Input.GetAxis("Vertical");
    }

    void FixedUpdate() {
        player_rb.MovePosition(player_rb.position + movement*movSpeed*Time.fixedDeltaTime);
    }
}
