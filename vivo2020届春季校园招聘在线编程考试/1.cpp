/*
现有一个 3x3 规格的 Android 智能手机锁屏程序和两个正整数 m 和 n ，请计算出使用最少m 个键和最多 n个键可以解锁该屏幕的所有有效模式总数。
其中有效模式是指：
1、每个模式必须连接至少m个键和最多n个键；
2、所有的键都必须是不同的；
3、如果在模式中连接两个连续键的行通过任何其他键，则其他键必须在模式中选择，不允许跳过非选择键（如图）；
4、顺序相关，单键有效（这里可能跟部分手机不同）。

输入：m,n
代表允许解锁的最少m个键和最多n个键
输出：
满足m和n个键数的所有有效模式的总数
*/

/*
DFS：找出m到n个点的情况，当遇到n时就continue，值得注意的地方就是第3点，
需要在对两个点进行判断，如果两个点在一条线上，且中间有一个点，且中间点没有遍历过，那么这时时非法的，需要continue
使用两个map来记录同一行和同一列的标识，然后再判断1 5 9 和 3 5 7这两种情况
*/
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

