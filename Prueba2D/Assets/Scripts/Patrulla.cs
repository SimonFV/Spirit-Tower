using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Patrulla : MonoBehaviour
{

    [SerializeField]
    Transform player;
    [SerializeField]
    Transform head;

    [Range(0f, 360f)]
    public float visionAngle = 30f;
    public float visionDistance = 10f;

    bool detected = false;

    //patrulla

    [SerializeField]
    BoxCollider2D boxCollider;

    public bool follow = true;

    private Rigidbody2D rb;

    [SerializeField]
    Transform[] waypoints;

    [SerializeField]
    float moveSpeed = 1f;

    int waypointIndex = 0;


    public void setFollow(bool value)
    {
        this.follow = value;
    }

    private void OnDrawGizmos()
    {
        if (visionAngle <= 0f) return;

        float halfVisionAngle = visionAngle * 0.5f;

        Vector2 p1, p2;
        p1 = PointForAngle(halfVisionAngle, visionDistance);
        p2 = PointForAngle(-halfVisionAngle, visionDistance);

        Gizmos.color = detected ? Color.green : Color.red;
        Gizmos.DrawLine(head.position, (Vector2)head.position + p1);
        Gizmos.DrawLine(head.position, (Vector2)head.position + p2);

        Gizmos.DrawRay(head.position, head.right * 4f);
    }

    private Vector2 PointForAngle(float angle, float distance)
    {
        return head.TransformDirection(
            new Vector2(
                Mathf.Cos(angle * Mathf.Deg2Rad),
                 Mathf.Sin(angle * Mathf.Deg2Rad))
            )
            * distance;
    }

    // Start is called before the first frame update
    void Start()
    {

        rb = GetComponent<Rigidbody2D>();
        transform.position = waypoints[waypointIndex].transform.position;

    }

    void checkSide()
    {

        if (rb.velocity.x > 0)
        {
            transform.localScale = new Vector2(1, transform.localScale.y);

        }
        else if (rb.velocity.x < 0)
        {
            transform.localScale = new Vector2(-1, transform.localScale.y);
        }

    }

    void Move()
    {

        transform.position = Vector2.MoveTowards(transform.position,
                                                    waypoints[waypointIndex].transform.position,
                                                    moveSpeed * Time.deltaTime);

        if (transform.position == waypoints[waypointIndex].transform.position)
        {
            waypointIndex += 1;
        }
        if (waypointIndex == waypoints.Length)
        {
            waypointIndex = 0;
        }

    }

    private void Update()
    {

        if (follow)
        {
            Move();
        }

        detected = false;

        Vector2 playerVector = player.position - head.position;
        if (Vector3.Angle(playerVector.normalized, head.right) < visionAngle * 0.5f)
        {

            if (playerVector.magnitude < visionDistance)
            {
                detected = true;
                if (!this.GetComponent<SpriteRenderer>().enabled)
                {
                    boxCollider.isTrigger = true;
                }
            }

        }


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
                this.follow = false;
                visionAngle = 0f;
                visionDistance = 0f;
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
