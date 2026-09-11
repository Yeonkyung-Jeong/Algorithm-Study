#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<char>> field(8, vector<char>(8));
vector<vector<bool>> visited(8, vector<bool>(8, false));
vector<vector<vector<char>>> save(100, vector<vector<char>>(8, vector<char>(8)));

int dr[9] = { 0, -1, 1, 0, 0, -1, 1, -1, 1 };
int dc[9] = { 0, 0, 0, -1, 1, -1, 1, 1, -1 };
// 제자리이동용 (0,0) 


bool wallmove(int r, int c, int depth) {
	save[depth] = field;

	vector<vector<char>> temp = field;
	for (int i = 7; i >= 1; i--) {
		for (int j = 0; j < 8; j++) {
			if (i == r && j == c && temp[i - 1][j] == '#') return false;

			temp[i][j] = temp[i - 1][j];

		}
	}
	for (int j = 0; j < 8; j++) temp[0][j] = '.';

	field = temp;

	return true;
}

void wallbacktrack(int depth) {
	field = save[depth];
}

bool dfs(int r, int c, int depth) {
	// 종료조건
	if (r == 0 && c == 7) return true;

	for (int d = 0; d < 9; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];

		if (nr < 0 || nc < 0 || nr >= 8 || nc >= 8) continue;
		if (visited[nr][nc]) continue;
		if (field[nr][nc] == '#') continue;

		visited[nr][nc] = true;

		if (!wallmove(nr, nc, depth)) {
			visited[nr][nc] = false;
			continue;
		}
		if (dfs(nr, nc, depth + 1)) return true;

		wallbacktrack(depth);
		visited[nr][nc] = false;
	}

	return false;
}

int main() {
	// 입력
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> field[i][j]; // .이면 빈칸, #이면 벽
		}
	}

	// 욱제의 시작 지점 (7,0) 목적지는 (0,7)
	// while문, 한 turn 마다 욱제 이동, 그 다음 벽 이동, 벽이 욱제있는데로 가면 break, 벽이 사라지는거 잘 갱신 
	if (dfs(7, 0, 0)) cout << 1;
	else cout << 0;

	return 0;
}