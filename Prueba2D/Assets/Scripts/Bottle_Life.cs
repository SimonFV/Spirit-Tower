using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bottle_Life : MonoBehaviour
{

    [SerializeField]
    BoxCollider2D boxCollider;

    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        
    }

    void OnCollisionEnter2D(Collision2D collision)
    {

        if (collision.gameObject.tag == "Player")
        {

            boxCollider.isTrigger = true;
            this.GetComponent<SpriteRenderer>().enabled = false;
            

        }

    }

}
