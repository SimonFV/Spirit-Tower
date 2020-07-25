using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using UnityEngine;

public class TrampaPicos : MonoBehaviour
{
    [SerializeField]
    BoxCollider2D boxCollider;

    [SerializeField]
    private Animator animator;

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

    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        PlayerMovement player = collision.gameObject.GetComponent<PlayerMovement>();
        if (collision.gameObject.tag == "Player" && player.getLife() > 0)
        {
            Client.Instance.sendMsgTCP("mele,picos");
            StartCoroutine(waiter(collision, player));
        }
    }
}
