using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Eye : MonoBehaviour
{

    [SerializeField]
    Transform player;
    [SerializeField]
    Transform head;

    bool detected;

    [SerializeField]
    GameObject enemy;

    [Range(0f, 360f)]
    public float visionAngle = 30f;
    public float visionDistance = 10f;



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

    Vector2 PointForAngle(float angle, float distance)
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
        
    }

    // Update is called once per frame
    void Update()
    {

        detected = false;

        Vector2 playerVector = player.position - head.position;
        if (Vector3.Angle(playerVector.normalized, head.right) < visionAngle * 0.5f)
        {

            if (playerVector.magnitude < visionDistance)
            {
                detected = true;

                enemy.GetComponent<Patrulla>().setFollow(false);
                enemy.transform.position = this.transform.position;
            }

        }

    }
}
