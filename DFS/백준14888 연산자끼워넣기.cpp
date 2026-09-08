#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int N;
vector<int> numbers;
vector<char> buhos;
vector<vector<char>> ret;
vector<char> temp;
vector<bool> visited;

int maxval = INT_MIN;
int minval = INT_MAX;

void dfs(int depth) {
	// 종료조건
	if (depth == N - 1) {
		ret.push_back(temp);
		return;
	}

	for (int i = 0; i < N - 1; i++) {
		if (visited[i]) continue;
		temp.push_back(buhos[i]);
		visited[i] = true;

		dfs(depth + 1);

		temp.pop_back();
		visited[i] = false;
	}
}

void cal(vector<char>& r, int idx, int result) {
	// 종료조건
	if (idx == N - 1) {
		if (result > maxval) maxval = result;
		if (result < minval) minval = result;
		return;
	}


	if (r[idx] == '+') {
		int nextresult = result + numbers[idx + 1];
		cal(r, idx + 1, nextresult);
	}
	if (r[idx] == '-') {
		int nextresult = result - numbers[idx + 1];
		cal(r, idx + 1, nextresult);
	}
	if (r[idx] == '*') {
		int nextresult = result * numbers[idx + 1];
		cal(r, idx + 1, nextresult);
	}
	if (r[idx] == '/') {
		int nextresult = result / numbers[idx + 1];
		cal(r, idx + 1, nextresult);
	}


}

int main() {

	// 입력
	cin >> N;

	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		numbers.push_back(a);
	}


	for (int i = 0; i < 4; i++) {
		int a;
		cin >> a;

		for (int j = 0; j < a; j++) {
			if (i == 0) buhos.push_back('+');
			if (i == 1) buhos.push_back('-');
			if (i == 2) buhos.push_back('*');
			if (i == 3) buhos.push_back('/');
		}
	}

	// buhos 순열 
	visited.assign(N, false);
	dfs(0);


	// buhos 순열 돌려서 반복문, 해당 부호 순서대로 numbers 계산, 최솟값, 최댓값 갱신갱신

	for (vector<char>& r : ret) {
		cal(r, 0, numbers[0]);

	}

	cout << maxval << "\n";
	cout << minval << "\n";

	return 0;
}