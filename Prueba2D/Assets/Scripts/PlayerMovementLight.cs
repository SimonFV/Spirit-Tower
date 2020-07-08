using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Experimental.Rendering.Universal;

public class PlayerMovementLight : MonoBehaviour
{

	[SerializeField]
	private bool clave;

	[SerializeField]
	private Light2D light;

	[SerializeField]
	private Image heart;

	[SerializeField]
	private Image heart2;

	[SerializeField]
	private Image heart3;

	[SerializeField]
	private int life;

	[SerializeField]
	private float speed = 5;

	[SerializeField]
	private Animator animator;

	private Rigidbody2D rb;

	[SerializeField]
	private Camera camara;


	private void setLife()
	{

		if (life == 3)
		{

			heart.GetComponent<Animator>().SetBool("hit", false);
			heart2.GetComponent<Animator>().SetBool("hit", false);
			heart3.GetComponent<Animator>().SetBool("hit", false);

		}

		else if (life == 2)
		{

			heart.GetComponent<Animator>().SetBool("hit", true);
			heart2.GetComponent<Animator>().SetBool("hit", false);
			heart3.GetComponent<Animator>().SetBool("hit", false);

		}

		else if (life == 1)
		{

			heart.GetComponent<Animator>().SetBool("hit", true);
			heart2.GetComponent<Animator>().SetBool("hit", true);
			heart3.GetComponent<Animator>().SetBool("hit", false);

		}

		else if (life == 0)
		{

			heart.GetComponent<Animator>().SetBool("hit", true);
			heart2.GetComponent<Animator>().SetBool("hit", true);
			heart3.GetComponent<Animator>().SetBool("hit", true);

		}

	}


	// Use this for initialization
	void Start()
	{

	}

	private void Awake()
	{

		rb = GetComponent<Rigidbody2D>();
		life = 3;

	}

	// Update is called once per frame
	void FixedUpdate()
	{

		if (rb.velocity.x > 0)
		{
			transform.localScale = new Vector2(1, transform.localScale.y);

		}
		else if (rb.velocity.x < 0)
		{
			transform.localScale = new Vector2(-1, transform.localScale.y);
		}

		camara.transform.position = new Vector3(this.transform.position.x, this.transform.position.y, camara.transform.position.z);
		light.transform.position = new Vector3(this.transform.position.x, this.transform.position.y, 0);


		float horizontal = Input.GetAxis("Horizontal");
		float vertical = Input.GetAxis("Vertical");

		rb.velocity = new Vector2(horizontal * speed, vertical * speed);

		animator.SetFloat("Velocidad", Mathf.Abs(horizontal) + Mathf.Abs(vertical));

		this.setLife();
	}


	public int getLife()
	{
		return this.life;
	}

	public bool getKey()
	{
		return this.clave;
	}

	public void setKey(bool key)
	{
		this.clave = key;
	}
}

