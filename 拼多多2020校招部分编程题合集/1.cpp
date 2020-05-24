/*
多多鸡有N个魔术盒子（编号1～N），其中编号为i的盒子里有i个球。
多多鸡让皮皮虾每次选择一个数字X（1 <= X <= N），多多鸡就会把球数量大于等于X个的盒子里的球减少X个。
通过观察，皮皮虾已经掌握了其中的奥秘，并且发现只要通过一定的操作顺序，可以用最少的次数将所有盒子里的球变没。
那么请问聪明的你，是否已经知道了应该如何操作呢？
*/

#include <bits/stdc++.h>
using namespace std;

int solution(int n) {
    if(n == 1) return 1;
    else return solution(n>>1) + 1;
}

int main()
{
    int T, N;
    cin >> T;
    vector<int> group(T, 0);
    for(int i = 0; i < T; i++) cin >> group[i];
    for(int i = 0; i < T; i++) cout << solution(group[i]) << endl;
    return 0;
}

/*
最先想到的就是分治，不停地从中值减少，最后就发现 第n个盒子的次数 等于 第n/2个盒子的次数+1，所以dp[n] = dp[n/2] + 1

最后观察发现，存在规律，第n个盒子的次数实际上是 log2(n)向下取整后+1
*/