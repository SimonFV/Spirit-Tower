using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lastEnemy : MonoBehaviour
{
    [SerializeField]
    BoxCollider2D boxCollider;

    IEnumerator waiter(Collision2D collision, PlayerMovement player)
    {
        if (collision.gameObject.GetComponent<PlayerMovement>().getLife() == 1)
        {
            boxCollider.isTrigger = true;
            collision.gameObject.GetComponent<PlayerMovement>().setLife(player.getLife() - 1);
            Client.Instance.sendMsgTCP("player,life," + player.getLife().ToString() + "\n");
            yield return new WaitForSeconds(1);

            boxCollider.isTrigger = false;
            collision.gameObject.GetComponent<PlayerMovement>().restartPlayerPos();
            collision.gameObject.GetComponent<PlayerMovement>().setLife(3);
            Client.Instance.sendMsgTCP("player,life," + player.getLife().ToString() + "\n");
        }
        else
        {
            boxCollider.isTrigger = true;
            collision.gameObject.GetComponent<PlayerMovement>().setLife(player.getLife() - 1);
            Client.Instance.sendMsgTCP("player,life," + player.getLife().ToString() + "\n");
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
                Client.Instance.sendMsgTCP("mele,player");
            }
            if (!shield.playerUsingShield && !Weapon.playerUsingBlade)
            {
                Client.Instance.sendMsgTCP("mele,ghost");
                PlayerMovement player = collision.gameObject.GetComponent<PlayerMovement>();
                StartCoroutine(waiter(collision, player));
            }

        }
    }
}
