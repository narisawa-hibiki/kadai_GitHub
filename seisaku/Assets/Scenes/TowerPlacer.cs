using UnityEngine;

public class TowerPlacer : MonoBehaviour
{
    public GameObject towerPrefab; 
    public LayerMask placeableLayer; 

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
            Debug.Log("アプリケーションを終了します。");
        }
        if (Input.GetMouseButtonDown(0)) // 左クリック
        {
            Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            Vector2Int gridPosInt = Vector2Int.RoundToInt(mousePos);
            Vector3 gridPos = new Vector3(gridPosInt.x, gridPosInt.y, 0f); 

            if (CanPlaceTowerAt(gridPosInt))
            {
                Instantiate(towerPrefab, gridPos, Quaternion.identity);
            }

        }
    }

    bool CanPlaceTowerAt(Vector2Int pos)
    {
        Collider2D hit = Physics2D.OverlapPoint(pos, placeableLayer);
        return hit != null; 
    }
}
