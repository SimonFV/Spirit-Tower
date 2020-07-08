using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TrampaFuego : MonoBehaviour
{
    [SerializeField]
    BoxCollider2D boxCollider;

    [SerializeField]
    private Animator animator;

    int cont = -20;

    // Start is called before the first frame update
    void Start()
    {
    
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (cont == -20)
        {
            boxCollider.isTrigger = false;
            animator.SetBool("Activar", true);
        }
        if (cont == 0)
        {
            boxCollider.isTrigger = true;
            animator.SetBool("Activar", false);
        }
        if (cont == 50) {
            cont = -21;
        }
        cont++;
    }

    /*
    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            boxCollider.isTrigger = false;
        }
    }
    */
}
