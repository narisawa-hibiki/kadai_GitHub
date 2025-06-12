using UnityEngine;

public class Bullet : MonoBehaviour
{
    public Transform target;
    public float speed = 5f;

    void Update()
    {
        if (target == null)
        {
            Destroy(gameObject);
            return;
        }

        transform.position = Vector2.MoveTowards(transform.position, target.position, speed * Time.deltaTime);

        if (Vector2.Distance(transform.position, target.position) < 0.1f)
        {
            Destroy(target.gameObject);
            Destroy(gameObject); 
        }
    }
}
