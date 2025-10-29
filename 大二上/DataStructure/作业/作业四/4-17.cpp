#include <climits> // 用于定义 INT_MAX
#include <iostream>
#include <vector>

using namespace std;

// Dijkstra 算法
void Dijkstra(int Graph[][100], int n, int V0) {
  // 定义常量
  const int INF = INT_MAX;        // 表示无穷大
  vector<int> dist(n, INF);       // 源点到各顶点的最短距离
  vector<bool> visited(n, false); // 标记顶点是否已访问

  // 初始化：源点距离为 0
  dist[V0] = 0;

  // 主循环：每次选取一个顶点加入最短路径集合
  for (int i = 0; i < n; i++) {
    // 找到未访问顶点中距离最小的顶点 u
    int u = -1, minDist = INF;
    for (int j = 0; j < n; j++) {
      if (!visited[j] && dist[j] < minDist) {
        u = j;
        minDist = dist[j];
      }
    }

    // 如果 u == -1，说明剩余顶点不可达
    if (u == -1)
      break;

    // 标记 u 为已访问
    visited[u] = true;

    // 更新 u 的邻接点的距离
    for (int v = 0; v < n; v++) {
      if (!visited[v] && Graph[u][v] != 0 && Graph[u][v] != INF) {
        if (dist[u] + Graph[u][v] < dist[v]) {
          dist[v] = dist[u] + Graph[u][v];
        }
      }
    }
  }

  // 输出结果
  cout << "源点 " << V0 << " 到其它顶点的最短路径距离为:" << endl;
  for (int i = 0; i < n; i++) {
    if (dist[i] == INF) {
      cout << "顶点 " << i << ": 不可达" << endl;
    } else {
      cout << "顶点 " << i << ": " << dist[i] << endl;
    }
  }
}

int main() {
  // 输入顶点数和邻接矩阵
  int n, V0;
  cout << "输入顶点数: ";
  cin >> n;

  int Graph[100][100];
  cout << "输入邻接矩阵(不可达的边权用 0 表示):" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> Graph[i][j];
      if (i != j && Graph[i][j] == 0) {
        Graph[i][j] = INT_MAX; // 转换为无穷大
      }
    }
  }

  cout << "输入源点编号(从 0 开始): ";
  cin >> V0;

  // 调用 Dijkstra 算法
  Dijkstra(Graph, n, V0);

  return 0;
}
