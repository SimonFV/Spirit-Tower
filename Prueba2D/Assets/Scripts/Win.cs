﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor.SceneManagement;
using UnityEngine.SceneManagement;

public class Win : MonoBehaviour
{
    [SerializeField]
    static int scene = 1;

    [SerializeField]
    BoxCollider2D boxCollider;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter2D(Collision2D collision)
    {

        if (collision.gameObject.tag == "Player")
        {

            SceneManager.LoadScene(scene);
            scene++;

        }

    }
    
}
