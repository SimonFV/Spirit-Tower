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

    IEnumerator waiter(Collision2D collision, PlayerMovement player)
    {
        if (collision.gameObject.GetComponent<PlayerMovement>().getLife() == 1)
        {
            boxCollider.isTrigger = true;
            collision.gameObject.GetComponent<PlayerMovement>().setLife(player.getLife() - 1);

            yield return new WaitForSeconds(1);

            boxCollider.isTrigger = false;
            collision.gameObject.GetComponent<PlayerMovement>().restartPlayerPos();
            collision.gameObject.GetComponent<PlayerMovement>().setLife(3);
        }
        else
        {
            boxCollider.isTrigger = true;
            collision.gameObject.GetComponent<PlayerMovement>().setLife(player.getLife() - 1);

            yield return new WaitForSeconds(1);
            boxCollider.isTrigger = false;
        }
    }

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

    void OnCollisionEnter2D(Collision2D collision)
    {
        PlayerMovement player = collision.gameObject.GetComponent<PlayerMovement>();
        if (collision.gameObject.tag == "Player" && player.getLife() > 0)
        {
            StartCoroutine(waiter(collision, player));
        }
    }
}
