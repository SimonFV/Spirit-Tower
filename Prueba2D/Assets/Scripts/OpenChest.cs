using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class OpenChest : MonoBehaviour
{
	[SerializeField]
	Animator animator;
	[SerializeField]
	BoxCollider2D boxCollider;

	static int contador;

    [SerializeField]
    Text text;

    IEnumerator waiter()  
    {
        text.enabled = true;

        yield return new WaitForSeconds(3);

        text.enabled = false;
    }

    private void Awake()
    {

        contador = 1;
        text.enabled = false;

    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
		animator.SetBool("Collition", true);

        if (contador == 3)
        {
            if (!collision.gameObject.GetComponent<PlayerMovement>().getKey()) 
            { 
                collision.gameObject.GetComponent<PlayerMovement>().setKey(true);
                //contador = 0;
                StartCoroutine(waiter());
            }
        }
        else
        {

        contador++;

        }

    }

}
