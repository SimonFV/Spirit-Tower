using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor.SceneManagement;
using UnityEngine.SceneManagement;

public class Win : MonoBehaviour
{
    public static int scene = 2;

    [SerializeField]
    BoxCollider2D boxCollider;

    void OnCollisionEnter2D(Collision2D collision)
    {

        if (collision.gameObject.tag == "Player")
        {

            SceneManager.LoadScene(scene);
            scene++;

        }

    }

}
