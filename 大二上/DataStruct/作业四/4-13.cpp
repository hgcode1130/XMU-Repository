#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 边的定义
struct Edge {
  int u, v, weight;
  bool operator<(const Edge &other) const {
    return weight < other.weight; // 按权重排序
  }
};

// 并查集实现
class UnionFind {
private:
  vector<int> parent, rank;

public:
  UnionFind(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]); // 路径压缩
    }
    return parent[x];
  }
  void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
      } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
      } else {
        parent[rootY] = rootX;
        rank[rootX]++;
      }
    }
  }
};

// 克鲁斯卡尔算法
vector<Edge> kruskal(int n, vector<Edge> &edges) {
  // 初始化并查集
  UnionFind uf(n);
  // 按权重排序边
  sort(edges.begin(), edges.end());
  vector<Edge> mst; // 存储最小生成树的边
  // 遍历边
  for (const Edge &edge : edges) {
    if (uf.find(edge.u) != uf.find(edge.v)) { // 不在同一连通分量
      mst.push_back(edge);                    // 加入最小生成树
      uf.unionSets(edge.u, edge.v);           // 合并连通分量
    }
    if (mst.size() == n - 1)
      break; // 最小生成树边数达到 n-1
  }
  return mst;
}

int main() {
  int n, m;
  cout << "输入顶点数和边数: ";
  cin >> n >> m;

  vector<Edge> edges(m);
  cout << "输入每条边的起点、终点和权重:" << endl;
  for (int i = 0; i < m; i++) {
    cin >> edges[i].u >> edges[i].v >> edges[i].weight;
  }

  vector<Edge> mst = kruskal(n, edges);
  cout << "最小生成树的边:" << endl;
  for (const Edge &edge : mst) {
    cout << edge.u << " - " << edge.v << " (权重: " << edge.weight << ")"
         << endl;
  }

  return 0;
}
