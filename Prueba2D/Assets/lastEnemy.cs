using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lastEnemy : MonoBehaviour
{
    [SerializeField]
    BoxCollider2D boxCollider;

    // Start is called before the first frame update
    void Start()
    {
    }

    private void Update()
    {
    }

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

            yield return new WaitForSeconds(3);
            boxCollider.isTrigger = false;
        }
    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            if (shield.playerUsingShield)
            {
            }
            if (Weapon.playerUsingBlade)
            {
                this.GetComponent<SpriteRenderer>().enabled = false;
                boxCollider.isTrigger = true;
            }
            if (!shield.playerUsingShield && !Weapon.playerUsingBlade)
            {
                PlayerMovement player = collision.gameObject.GetComponent<PlayerMovement>();
                StartCoroutine(waiter(collision, player));
            }

        }
    }
}
