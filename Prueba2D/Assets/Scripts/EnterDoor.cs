using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EnterDoor : MonoBehaviour {

	[SerializeField]
	Animator animator;
	[SerializeField]
	BoxCollider2D boxCollider;

	void OnCollisionEnter2D(Collision2D collision) {
		if (collision.gameObject.tag == "Player") {

			if (collision.gameObject.GetComponent<PlayerMovement>().getKey() == true)
			{
				animator.SetBool("Collition", true);
				boxCollider.isTrigger = true;
			}

		}
	}
}
