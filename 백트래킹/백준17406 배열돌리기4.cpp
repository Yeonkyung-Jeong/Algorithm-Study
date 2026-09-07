#include <iostream>
#include <vector>
#include <tuple>
#include <climits>

using namespace std;

// 1-based

int N, M, K;
vector<vector<int>> A;
vector<tuple<int, int, int>> temp;
vector<tuple<int, int, int>> t;

// 순열
void dfs(vector<bool> visited, vector<vector<tuple<int, int, int>>>& ret, int depth) {
    // 종료조건
    if (depth == K) {
        ret.push_back(t);
        return;
    }

    for (int i = 0; i < K; i++) {
        if (visited[i]) continue;
        t.push_back(temp[i]);
        visited[i] = true;

        dfs(visited, ret, depth + 1);

        visited[i] = false;
        t.pop_back();
    }
}

// 나선형 회전
void rotate(vector<vector<int>>& Acopy, int r, int c, int s) {
    for (int layer = 1; layer <= s; layer++) {
        int t = r - layer, b = r + layer;
        int l = c - layer, rr = c + layer;
        vector<int> ring;
        for (int j = l; j < rr; j++) ring.push_back(Acopy[t][j]);       // 위쪽
        for (int i = t; i < b; i++) ring.push_back(Acopy[i][rr]);       // 오른쪽
        for (int j = rr; j > l; j--) ring.push_back(Acopy[b][j]);       // 아래쪽
        for (int i = b; i > t; i--) ring.push_back(Acopy[i][l]);        // 왼쪽

        int len = ring.size();
        // 시계방향 1칸 회전: 마지막 원소를 맨 앞으로
        vector<int> rotated(len);
        rotated[0] = ring[len - 1];
        for (int i = 1; i < len; i++) rotated[i] = ring[i - 1];

        int idx = 0;
        for (int j = l; j < rr; j++) Acopy[t][j] = rotated[idx++];
        for (int i = t; i < b; i++) Acopy[i][rr] = rotated[idx++];
        for (int j = rr; j > l; j--) Acopy[b][j] = rotated[idx++];
        for (int i = b; i > t; i--) Acopy[i][l] = rotated[idx++];
    }
}

int main() {

    // 입력
    cin >> N >> M >> K;

    A.resize(N + 1, vector<int>(M + 1));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < K; i++) {
        int r, c, s;
        cin >> r >> c >> s;
        temp.push_back({ r,c,s });
    }

    // temp의 순열 (중복 X)
    vector<bool> visited(K + 1, false);
    vector<vector<tuple<int, int, int>>> ret;
    dfs(visited, ret, 0);


    // 순서가 다른 각 temp 모음 = ret 반복문n
    int finminval = INT_MAX;
    for (vector<tuple<int, int, int>>& v : ret) {
        // 하나의 version 반복문 
        vector<vector<int>> Acopy = A;
        for (tuple<int, int, int>& t : v) {
            // 각 r, c, s 회전     
            int r = get<0>(t), c = get<1>(t), s = get<2>(t);

            rotate(Acopy, r, c, s);
        }

        // A값 계산, 최솟값 갱신갱신
        int minval = INT_MAX;
        for (int i = 1; i <= N; i++) {
            int sumrow = 0;
            for (int j = 1; j <= M; j++) {
                sumrow += Acopy[i][j];
            }
            if (sumrow < minval) minval = sumrow;
        }
        if (minval < finminval) finminval = minval;
    }

    cout << finminval << "\n";

    return 0;
}