using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OpenChest : MonoBehaviour
{
	[SerializeField]
	Animator animator;
	[SerializeField]
	BoxCollider2D boxCollider;
	/*
	void OnCollisionEnter2D(Collision2D collision)
	{
		if (collision.gameObject.tag == "Player")
		{

			animator.SetBool("Collition", true);

		}
	}
	*/

    private void OnCollisionStay2D(Collision2D collision)
    {
        if (Input.GetAxis("Jump") == 1)
        {
			animator.SetBool("Collition", true);
		}


    }

}
