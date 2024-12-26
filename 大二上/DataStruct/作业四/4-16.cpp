#include <iostream>
#include <vector>
using namespace std;

// 判断是否存在长度为 k 的简单路径
bool DFS(vector<vector<int>> &graph, vector<bool> &visited, int cur, int target,
         int depth, int k) {
  if (depth == k) {
    return cur == target; // 如果路径长度达到 k，判断是否为目标顶点
  }

  visited[cur] = true;              // 标记当前顶点已访问
  for (int neighbor : graph[cur]) { // 遍历邻接点
    if (!visited[neighbor]) {       // 仅对未访问的邻接点继续递归
      if (DFS(graph, visited, neighbor, target, depth + 1, k)) {
        return true;
      }
    }
  }
  visited[cur] = false; // 回溯，恢复当前顶点的访问状态
  return false;
}

// 主函数
bool existsSimplePath(vector<vector<int>> &graph, int u, int v, int k) {
  int n = graph.size();
  vector<bool> visited(n, false); // 标记顶点是否访问
  return DFS(graph, visited, u, v, 0, k);
}

int main() {
  int n, m;
  cout << "输入顶点数和边数: ";
  cin >> n >> m;

  vector<vector<int>> graph(n);
  cout << "输入边信息 (无向图，每条边两个顶点):" << endl;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int u, v, k;
  cout << "输入起点、终点和路径长度 k: ";
  cin >> u >> v >> k;

  if (existsSimplePath(graph, u, v, k)) {
    cout << "存在长度为 " << k << " 的简单路径。" << endl;
  } else {
    cout << "不存在长度为 " << k << " 的简单路径。" << endl;
  }

  return 0;
}
