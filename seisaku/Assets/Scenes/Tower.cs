using UnityEngine;

public class Tower : MonoBehaviour
{
    public GameObject bulletPrefab;
    public float fireRate = 1f;
    public float range = 3f;

    float timer = 0f;

    void Update()
    {
        timer += Time.deltaTime;

        if (timer >= fireRate)
        {
            GameObject enemy = FindClosestEnemy();
            if (enemy != null)
            {
                Shoot(enemy.transform);
                timer = 0f;
            }
        }
    }

    GameObject FindClosestEnemy()
    {
        GameObject[] enemies = GameObject.FindGameObjectsWithTag("Enemy");
        GameObject closest = null;
        float minDist = Mathf.Infinity;

        foreach (GameObject e in enemies)
        {
            float dist = Vector2.Distance(transform.position, e.transform.position);
            if (dist < minDist && dist <= range)
            {
                closest = e;
                minDist = dist;
            }
        }
        return closest;
    }

    void Shoot(Transform target)
    {
        GameObject b = Instantiate(bulletPrefab, transform.position, Quaternion.identity);
        b.GetComponent<Bullet>().target = target;
    }
}
