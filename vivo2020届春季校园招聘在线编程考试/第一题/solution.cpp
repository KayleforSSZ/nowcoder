#include <bits/stdc++.h>
using namespace std;

map<int, int> rmp = {{1, 0}, {2, 0}, {3, 0},    // 同一行标识
                     {4, 1}, {5, 1}, {6, 1},
                     {7, 2}, {8, 2}, {9, 2}};

map<int, int> cmp = {{1, 0}, {2, 1}, {3, 2},    // 同一列标识
                     {4, 0}, {5, 1}, {6, 2},
                     {7, 0}, {8, 1}, {9, 2}};

bool judge(int a, int b, vector<bool> &visited) {
    if((cmp[a] == cmp[b]) && abs(a-b) == 6 && !visited[(a+b)/2]) return true;
    if((rmp[a] == rmp[b]) && abs(a-b) == 2 && !visited[(a+b)/2]) return true;
    if(!visited[5] && ((a==1 && b==9) || (a==9 && b == 1) || (a==3 && b==7) || (a==7 && b==3))) return true;
    return false;
}

void dfs(int m, int n, int len, int &cnt, int now, vector<bool> &visited) {
    if(len >= m) cnt++;
    if(len == n) return;
    for(int i = 1; i <= 9; i++) {
        if(visited[i]) continue;
        if(judge(now, i, visited)) continue;
        visited[i] = true;
        dfs(m, n, len+1, cnt, i, visited);
        visited[i] = false;
    }
}

int solution(int m, int n) {
    vector<bool> visited(10, false);
    int cnt = 0;
    int x = 4;
    for(int i = 1; i <= 9; i++) {
        visited[i] = true;
        dfs(m, n, 1, cnt, i, visited);
        visited[i] = false;
    }
    return cnt;
}

int main()
{
    cout << solution(1, 2) << endl;
    return 0;
}
