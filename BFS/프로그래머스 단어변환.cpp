// 14m
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

int answer = 0;

bool compare(string begin, string next) {
    int cnt = 0;

    for (int i = 0; i < begin.size(); i++) {
        if (begin[i] != next[i]) cnt++;
    }

    return cnt == 1;
}

int solution(string begin, string target, vector<string> words) {
    auto it = find(words.begin(), words.end(), target);
    if (it == words.end()) return 0;
    if (begin.size() != target.size()) return 0;

    queue<string> q;
    q.push(begin);

    unordered_map<string, int> dist;
    for (string& w : words) dist[w] = -1;
    dist[begin] = 0;

    while (!q.empty()) {
        string cur = q.front();
        q.pop();

        // 종료조건
        if (cur == target) {
            answer = dist[cur];
            break;
        }
        
        for (int i = 0; i < words.size(); i++) {
            if (dist[words[i]] != -1) continue;
            if (!compare(cur, words[i])) continue;

            string next = words[i];
            dist[next] = dist[cur] + 1;
            q.push(next);
        }
    }

    return answer;

}