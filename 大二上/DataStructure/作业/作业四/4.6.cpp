#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 创建邻接表
void createAdjacencyList() {
  // 初始化邻接表
  unordered_map<string, vector<string>> adjacencyList;

  // 输入顶点数目和弧数目
  int n, m;
  cout << "输入顶点数目: ";
  cin >> n;
  cout << "输入弧数目: ";
  cin >> m;

  // 输入顶点信息
  vector<string> vertices(n);
  cout << "输入所有顶点信息 (用空格分隔): ";
  for (int i = 0; i < n; i++) {
    cin >> vertices[i];
    // 初始化邻接表中每个顶点的邻接列表为空
    adjacencyList[vertices[i]] = {};
  }

  // 输入弧信息并构建邻接表
  cout << "输入每条弧的信息（起点和终点用空格分隔）:" << endl;
  for (int i = 0; i < m; i++) {
    string start, end;
    cin >> start >> end;
    adjacencyList[start].push_back(end);
  }

  // 输出邻接表
  cout << "邻接表表示的有向图:" << endl;
  for (const auto &vertex : adjacencyList) {
    cout << vertex.first << ": ";
    for (const auto &neighbor : vertex.second) {
      cout << neighbor << " ";
    }
    cout << endl;
  }
}

int main() {
  // 调用创建邻接表的函数
  createAdjacencyList();
  return 0;
}
