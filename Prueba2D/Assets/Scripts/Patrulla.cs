using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Patrulla : MonoBehaviour
{
    [SerializeField]
    private Grid grid;

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

    // Variables nuevas
    public float changeTargetDistance = 0.1f;
    public int currentTarget = 0;
    public List<List<float>> lista_matriz = new List<List<float>>();
    public List<float> lista_interna = new List<float>();
    public static GameObject[] gameObjects;
    public bool enviar_mensaje = true;

    public int pos_x_anterior;
    public int pos_y_anterior;

    public bool detecto = false;

    // Fin

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

        // Se inicializa una ruta (Si no lanza error :) )
        lista_interna.Add(0);
        lista_interna.Add(0);
        lista_matriz.Add(lista_interna);

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

    private bool MoveRuta()
    {

        Vector3 target = new Vector3(lista_matriz[currentTarget][0], lista_matriz[currentTarget][1], 0);
        Vector3 distanciaVector = target - transform.position;
        if (distanciaVector.magnitude <= changeTargetDistance)
        {
            return true;
        }

        transform.position = Vector2.MoveTowards(transform.position,
                                                    target,
                                                    moveSpeed * Time.deltaTime);
        return false;
    }

    private int GetNextTarget()
    {

        currentTarget++;
        if (currentTarget >= lista_matriz.Count)
        {
            // Ya llego al objetivo 
            currentTarget = -1;
        }

        return currentTarget;
    }

    private void Update()
    {

        if (follow)
        {
            Move();
        }
        else
        {

            if (enviar_mensaje)
            {

                // Enviar posiciones de los espectros y asignar nueva posicion del jugador
                Patrulla valor1;
                for (int i = 0; i < Patrulla.gameObjects.Length; i++)
                {
                    Client.Instance.sendMsgUDP("espectros,pos," + i + "," +
                        PlayerMovement.escaleToServerX((int)gameObjects[i].GetComponent<Patrulla>().transform.position.x) +
                        "," +
                        PlayerMovement.escaleToServerY((int)gameObjects[i].GetComponent<Patrulla>().transform.position.y) +
                        "\n"
                        );

                    valor1 = gameObjects[i].GetComponent<Patrulla>();
                    valor1.pos_x_anterior = (int)player.position.x;
                    valor1.pos_y_anterior = (int)player.position.y;
                }

                // Solicitar breadcrumbing y aStar
                Debug.Log("Enviando mensaje");
                Patrulla valor;
                for (int i = 0; i < Patrulla.gameObjects.Length; i++)
                {
                    valor = gameObjects[i].GetComponent<Patrulla>();
                    if (valor.follow == false && valor.enviar_mensaje == true)
                    {
                        Client.Instance.sendMsgUDP("dentroVision," + i + ",");
                    }
                }

                enviar_mensaje = false;
            }

            if (pos_x_anterior != (int)player.position.x || pos_y_anterior != (int)player.position.y)
            {

                // Asignar nueva posicion del jugador
                Patrulla valor1;
                for (int i = 0; i < Patrulla.gameObjects.Length; i++)
                {
                    valor1 = gameObjects[i].GetComponent<Patrulla>();
                    valor1.pos_x_anterior = (int)player.position.x;
                    valor1.pos_y_anterior = (int)player.position.y;
                    valor1.lista_matriz.Clear();
                    valor1.currentTarget = -1;
                }

                // Volver a solicitur algoritmos
                Patrulla valor2;
                for (int i = 0; i < Patrulla.gameObjects.Length; i++)
                {
                    valor2 = gameObjects[i].GetComponent<Patrulla>();
                    if (valor2.detecto == true)
                    {
                        valor2.enviar_mensaje = true;
                    }
                }
            }

            if (currentTarget != -1)
            {
                if (MoveRuta())
                {
                    currentTarget = GetNextTarget();
                }
            }

        }

        detected = false;

        Vector2 playerVector = player.position - head.position;
        if (Vector3.Angle(playerVector.normalized, head.right) < visionAngle * 0.5f)
        {

            if (playerVector.magnitude < visionDistance)
            {
                detected = true;
                follow = false;
                detecto = true;
                if (!this.GetComponent<SpriteRenderer>().enabled)
                {
                    boxCollider.isTrigger = true;
                }
            }
            else
            {
                //follow=true;
            }

        }


    }

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
                if (this.transform.Find("Point Light 2D (4)") != null)
                {
                    Destroy(this.transform.Find("Point Light 2D (4)").gameObject);
                }
                this.follow = false;
                visionAngle = 0f;
                visionDistance = 0f;
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