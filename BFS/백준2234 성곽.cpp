#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M; // 열, 행
vector<vector<int>> field;
vector<int> groupsz;
vector<vector<int>> groupnum;

int dr[4] = { 0, -1, 0, 1 };
int dc[4] = { -1, 0, 1, 0 }; // 좌, 상, 우, 하
int wallbit[4] = { 1, 2, 4, 8 }; // 서, 북, 동, 남

bool rangecheck(int r, int c) {
	if (r < 0 || c < 0 || r >= M || c >= N) return false;
	return true;
}

// 비트마스킹
int calwall(int num, int d) {
	if (num & wallbit[d]) return false; // 겹침
	return true; // 안 겹침
}

pair<int, int> countgroup(int turn, vector<vector<int>>& groupnum, int r, int c) {
	queue<pair<int, int>> q;
	q.push({ r,c });

	groupnum[r][c] = turn;
	int sz = 1;
	while (!q.empty()) {
		int curr = q.front().first, curc = q.front().second;
		q.pop();

		for (int d = 0; d < 4; d++) {
			int nr = curr + dr[d];
			int nc = curc + dc[d];

			if (!rangecheck(nr, nc)) continue;
			if (groupnum[nr][nc] != -1) continue;
			if (!calwall(field[curr][curc], d)) continue;

			groupnum[nr][nc] = turn;
			q.push({ nr, nc });
			sz++;

		}
	}

	return { 1, sz };
}


int main() {

	// 입력
	cin >> N >> M;

	groupsz.assign(N * M + 1, 0);

	field.assign(M, vector<int>(N));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> field[i][j];
		}
	}

	// 이 성에 있는 방의 개수, 가장 넓은 방의 넓이 = bfs로 한번에
	groupnum.assign(M, vector<int>(N, -1));
	int groupcnt = 0;
	int maxsz = -1;
	int turn = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (groupnum[i][j] != -1) continue;
			turn++;
			pair<int, int> ret = countgroup(turn, groupnum, i, j);
			groupcnt += ret.first;
			groupsz[turn] = ret.second;
			if (ret.second > maxsz) maxsz = ret.second;
		}
	}

	// 벽 제거 후 넓은 방 갱신갱신
	int maxroom = -1;
	vector<vector<bool>> visited(M, vector<bool>(N, false));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j]) continue;

			for (int d = 0; d < 4; d++) {
				int nr = i + dr[d];
				int nc = j + dc[d];

				if (!rangecheck(nr, nc)) continue;
				if (visited[nr][nc]) continue;
				if (groupnum[nr][nc] == groupnum[i][j]) continue;

				int cursz = groupsz[groupnum[i][j]] + groupsz[groupnum[nr][nc]];
				if (cursz > maxroom) maxroom = cursz;
			}
		}
	}



	// 출력
	cout << groupcnt << '\n';
	cout << maxsz << "\n";
	cout << maxroom << "\n";



	return 0;
}