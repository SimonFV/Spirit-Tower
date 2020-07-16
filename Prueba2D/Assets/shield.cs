using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using UnityEngine;

public class shield : MonoBehaviour
{
    public static bool playerUsingShield;
    private static Vector3 playerShieldPosLeft;
    private static Vector3 playerShieldPosRight;
    private static Vector2 playerShieldSide;

    [SerializeField]
    BoxCollider2D boxCollider;

    [SerializeField]
    private Animator animator;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void FixedUpdate()
    {
        playerUsingShield = PlayerMovement.usingShield;
        playerShieldPosLeft = PlayerMovement.shieldPosLeft;
        playerShieldPosRight = PlayerMovement.shieldPosRight;
        playerShieldSide = PlayerMovement.shieldLeftOrRight;

        if (playerUsingShield)
        {
            boxCollider.isTrigger = false;
            if (transform.localScale.x == 1)
            {
                this.GetComponent<SpriteRenderer>().enabled = true;
                this.GetComponent<Transform>().position = playerShieldPosRight;
                transform.localScale = playerShieldSide;
            }
            if (transform.localScale.x == -1)
            {
                this.GetComponent<SpriteRenderer>().enabled = true;
                this.GetComponent<Transform>().position = playerShieldPosLeft;
                transform.localScale = playerShieldSide;
            }
        }
        else if (!playerUsingShield)
        {
            this.GetComponent<SpriteRenderer>().enabled = false;
            boxCollider.isTrigger = true;
        }
    }
}
