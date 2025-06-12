using UnityEngine;

public class EnemyMove : MonoBehaviour
{
    public Transform[] waypoints;
    public float speed = 2f;
    private int index = 0;

    void Update()
    {
        if (index < waypoints.Length)
        {
            transform.position = Vector2.MoveTowards(transform.position, waypoints[index].position, speed * Time.deltaTime);

            if (Vector2.Distance(transform.position, waypoints[index].position) < 0.1f)
            {
                index++;
            }
        }
        else
        {
            Destroy(gameObject);
        }
    }
    void OnTriggerEnter2D(Collider2D other)
    {
        Debug.Log("‚Ô‚Â‚©‚Á‚½‘ŠŽè: " + other.name);
        if (other.CompareTag("King"))
        {
            GameManager.Instance.GameOver();
            Destroy(gameObject);
        }
    }
}
