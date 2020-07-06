using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayerMov : MonoBehaviour
{
    public float player_speed = 5f;
    public Rigidbody2D player_rb;
    Vector2 movement;

    Vector3Int playerPos;
    Vector3Int localPlace;
    public Grid grid;
    public Tilemap tilemap;
    int[,] bitmap;
    string string_bitmap;

    public Client client;

    void Start()
    {
        bitmap = new int[tilemap.size.x, tilemap.size.y];
        for (int i = tilemap.origin.x; i < tilemap.origin.x + tilemap.size.x; i++)
        {
            for (int j = tilemap.origin.y; j < tilemap.origin.y + tilemap.size.y; j++)
            {
                localPlace = (new Vector3Int(i, j, (int)tilemap.transform.position.y));
                if (tilemap.HasTile(localPlace))
                {
                    if (tilemap.GetTile(localPlace).name == "tileset-sliced_25")
                    {
                        bitmap[localPlace.x - tilemap.origin.x, localPlace.y - tilemap.origin.y] = 1;
                    }
                    else
                    {
                        bitmap[localPlace.x - tilemap.origin.x, localPlace.y - tilemap.origin.y] = 0;
                    }
                }
                else
                {
                    bitmap[localPlace.x - tilemap.origin.x, localPlace.y - tilemap.origin.y] = 0;
                }
            }
        }

        string_bitmap = "";
        for (int j = tilemap.size.y - 1; j >= 0; j--)
        {
            for (int i = 0; i < tilemap.size.x; i++)
            {
                string_bitmap += bitmap[i, j].ToString("0") + " ";
            }
            string_bitmap += "\n";
        }
    }

    // Update is called once per frame
    void Update()
    {
        movement.x = Input.GetAxisRaw("Horizontal");
        movement.y = Input.GetAxisRaw("Vertical");
    }

    void FixedUpdate()
    {
        if (Input.GetAxisRaw("Horizontal") != 0 || Input.GetAxisRaw("Vertical") != 0)
        {
            player_rb.MovePosition(player_rb.position + movement * player_speed * Time.fixedDeltaTime);
            playerPos = grid.WorldToCell(player_rb.transform.position);

            client.sendMsgUDP(playerPos.ToString("0"));

            //client.sendMsgUDP(string_bitmap);
        }
    }
}
