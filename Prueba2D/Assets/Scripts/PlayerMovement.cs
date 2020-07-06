using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour {

	public bool clave;

	[SerializeField]
	private float speed = 5;
	
	[SerializeField]
	private Animator animator;

	private Rigidbody2D rb;

	[SerializeField]
	private Camera camara;
 
	// Use this for initialization
	void Start () {


		
	}

    private void Awake()
    {

		rb = GetComponent<Rigidbody2D>();

    }

    // Update is called once per frame
    void FixedUpdate () {

		if (rb.velocity.x > 0)
		{
			transform.localScale = new Vector2(1, transform.localScale.y);

		}else if (rb.velocity.x < 0)
		{
			transform.localScale = new Vector2(-1, transform.localScale.y);
		}

		camara.transform.position = new Vector3(transform.position.x, transform.position.y, camara.transform.position.z); ;


		float horizontal = Input.GetAxis ("Horizontal");
		float vertical = Input.GetAxis ("Vertical");

		rb.velocity = new Vector2 (horizontal * speed, vertical * speed);

		animator.SetFloat("Velocidad", Mathf.Abs(horizontal) + Mathf.Abs(vertical));

	}
}
