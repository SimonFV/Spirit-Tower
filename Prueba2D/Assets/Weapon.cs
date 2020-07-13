using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using UnityEngine;

public class Weapon : MonoBehaviour
{
    private static bool playerUsingBlade;
    private static Vector3 playerBladePosLeft;
    private static Vector3 playerBladePosRight;
    private static Vector2 playerBladeSide;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        playerUsingBlade = PlayerMovement.usingBlade;
        playerBladePosLeft = PlayerMovement.bladePosLeft;
        playerBladePosRight = PlayerMovement.bladePosRight;
        playerBladeSide = PlayerMovement.bladeLeftOrRight;
        
        if (playerUsingBlade)
        {
            if (transform.localScale.x == 1)
            {
                this.GetComponent<SpriteRenderer>().enabled = true;
                this.GetComponent<Transform>().position = playerBladePosRight;
                transform.localScale = playerBladeSide;
            }
            if (transform.localScale.x == -1)
            {
                this.GetComponent<SpriteRenderer>().enabled = true;
                this.GetComponent<Transform>().position = playerBladePosLeft;
                transform.localScale = playerBladeSide;
            }
        }
        else if (!playerUsingBlade) {
            this.GetComponent<SpriteRenderer>().enabled = false;
        }
    }
}
