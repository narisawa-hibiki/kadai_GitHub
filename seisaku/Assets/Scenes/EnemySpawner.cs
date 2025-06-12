using UnityEngine;

public class EnemySpawner : MonoBehaviour
{
    public GameObject enemyPrefab;
    public Transform[] waypoints;
    public float spawnInterval = 2f;
    float timer;

    void Update()
    {
        timer += Time.deltaTime;
        if (timer >= spawnInterval)
        {
            GameObject e = Instantiate(enemyPrefab, waypoints[0].position, Quaternion.identity);
            e.GetComponent<EnemyMove>().waypoints = waypoints;
            timer = 0f;
        }
    }
}
