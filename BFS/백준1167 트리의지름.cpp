#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int v;
vector<vector<pair<int, int>>> tree;


pair<int, int> bfs(int stidx) {
	queue<int> q;
	q.push(stidx);

	vector<int> dist(v + 1, -1);
	dist[stidx] = 0;

	int maxweight = -1;
	int retidx = 0;
	while (!q.empty()) {
		int curidx = q.front();
		q.pop();

		if (dist[curidx] > maxweight) {
			maxweight = dist[curidx];
			retidx = curidx;
		}

		for (pair<int, int>& p : tree[curidx]) {
			int nextidx = p.first;
			int weight = p.second;

			if (dist[nextidx] != -1) continue;

			q.push(nextidx);
			dist[nextidx] = dist[curidx] + weight;
		}
	}

	return { retidx, maxweight };
}


int main() {
	// 입력 
	cin >> v;

	tree.resize(v + 1);

	for (int i = 1; i <= v; i++) {
		int a;
		cin >> a;
		while (true) {
			int b, c;
			cin >> b;
			if (b == -1) break;

			cin >> c;

			tree[a].push_back({ b,c }); // 짝수 idx는 노드, 홀수 idx는 거리
		}
	}

	// 아무 노드에서나 시작해서 가장 먼 정점 구하기
	int firstfaridx = bfs(1).first;

	// 그 정점에서 또 가장 먼 정점 구하면서 거리 계산
	int answer = bfs(firstfaridx).second;

	cout << answer << "\n";

	return 0;
}