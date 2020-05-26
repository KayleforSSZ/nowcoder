/*
小v在公司负责游戏运营，今天收到一款申请新上架的游戏“跳一跳”，为了确保提供给广大玩家朋友们的游戏都是高品质的，按照运营流程小v必须对新游戏进行全方位了解体验和评估。这款游戏的规则如下：
    有n个盒子排成了一行，每个盒子上面有一个数字a[i]，表示在该盒子上的人最多能向右移动a[i]个盒子（比如当前所在盒子上的数字是3，则表示可以一次向右前进1个盒子，2个盒子或者3个盒子）。
现在小v从左边第一个盒子上开始体验游戏，请问最少需要移动几次能到最后一个盒子上？
*/


/*
跳盒子问题，与leetcode 55题类似，不同的是leetcode判断能否到达终点，该题要输出最少移动次数
方法依然是动态规划
从后往前构造dp[i]，dp[i]表示第 i 个盒子能到达最后一个盒子所需要的最少次数
在构造dp[i]的时候，如果
*/
#include <bits/stdc++.h>
 
using namespace std;
 
/**
 * Welcome to vivo !
 */
  
int solution(int a[], int n)
{
    if(n == 1) return 0;
    if(a[0] <= 0) return -1;
    vector<int> dp(n, 0);
    // 边界条件
    dp[n-2] = a[n-2] >= 1 ? 1: 0;
    // 状态转移方程
    for(int i = n - 3; i >= 0; i--) {
        if(a[i] >= n-i-1) dp[i] = 1;	// 如果i能直接到达最后一个，就是1
        else {	// 如果不能
            int len = i + a[i] < n - 2 ? i + a[i] : n - 2;	// 遍历i所能到达的后续盒子j，因为i到j需要一步，所以只要dp[j]最小，那dp[i] = dp[j]+1
            dp[i] = INT_MAX;
            for(int j = len; j > i; j--) {
                if(!dp[j]) continue;	// 如果dp[j]无法到达最后一个，continue
                dp[i] = min(dp[i], dp[j]);
            }
            if(dp[i] != INT_MAX) dp[i]++;
        }
    }
    if(dp[0] == INT_MAX) return -1;
    return dp[0];
}
 
int main()
{
    string str("");
    getline(cin, str);
    int a[2000];
    int i = 0;
    char *p;
    int count = 0;
     
    const char* strs = str.c_str();
    p = strtok((char *)strs, " ");
    while(p)
    {
        a[i] = atoi(p);
        count++;
        p = strtok(NULL, " ");
        i++;
        if(i >= 2000)
            break;
    }
    int num = solution(a, count);
    cout << num << endl;
    return 0;
}

