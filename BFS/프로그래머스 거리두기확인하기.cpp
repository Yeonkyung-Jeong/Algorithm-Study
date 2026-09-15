// 9:57
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> dist;

int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };

int bfs(vector<string>& room) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (room[i][j] != 'P') continue;

            dist.assign(5, vector<int>(5, -1));
            dist[i][j] = 0;

            queue<pair<int, int>> q;
            q.push({ i, j });

            while (!q.empty()) {
                int curr = q.front().first, curc = q.front().second;
                q.pop();

                if (dist[curr][curc] >= 2) break;

                for (int d = 0; d < 4; d++) {
                    int nr = curr + dr[d];
                    int nc = curc + dc[d];

                    if (nr < 0 || nc < 0 || nr >= 5 || nc >= 5) continue;
                    if (room[nr][nc] == 'X') continue;
                    if (dist[nr][nc] != -1) continue;

                    dist[nr][nc] = dist[curr][curc] + 1;
                    q.push({ nr,nc });

                    if (room[nr][nc] == 'P') return 0;

                }
            }

        }
    }

    return 1;
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;

    // places 순회를 해서 bfs 호출 
    for (vector<string>& v : places) answer.push_back(bfs(v));

    return answer;
}