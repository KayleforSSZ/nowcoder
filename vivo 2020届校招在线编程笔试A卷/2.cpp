/*
小v在vivo手机的应用商店中下载了一款名为“一维消消乐”的游戏，介绍如下：
1、给出一些不同颜色的豆子，豆子的颜色用数字（0-9）表示，即不同的数字表示不同的颜色；
2、通过不断地按行消除相同颜色且连续的豆子来积分，直到所有的豆子都消掉为止；
3、假如每一轮可以消除相同颜色的连续 k 个豆子（k >= 1），这样一轮之后小v将得到 k*k 个积分；
4、由于仅可按行消除，不可跨行或按列消除，因此谓之“一维消消乐”。
请你帮助小v计算出最终能获得的最大积分。
*/

/*
	Leetcode原题546：https://leetcode.com/problems/remove-boxes/
	
	dp[i][j][k]表示第i位到第j位，后面有k个盒子与第j位的盒子颜色相同
	
	处理策略有两种：
	
	1. 将第 j 位与后面的 k 个一起消除，获得的分数是 dp[i][j-1][0] + (k+1)*(k+1)
	2. 假如在 i 到 j 之间有与 j 颜色相同的盒子 m ，我们可以先消除 m+1 到 j-1 的杂余盒子，分数为dp[m+1][j-1][0]
		然后剩余的盒子得分为dp[i][m][k+1]
		
	具体策略 可以先执行策略 1 ，让 dp[i][j][k] = dp[i][j-1][0] + (k+1)*(k+1)
			然后执行策略 2 ，如果比策略 1 的得分高，就更新
	
*/


#include <bits/stdc++.h>
using namespace std;

#define MAX_NUM 100

int dp[100][100][100] = {0};

int calculatePoints(int boxs[], int l, int r, int k) {
    if(l > r) return 0;     // 不满足条件
    if(dp[l][r][k] != 0) return dp[l][r][k];    // 如果计算过了，直接返回
    while(r > l && boxs[r] == boxs[r-1]) {      // 保证第r位与第r-1位颜色不同
        r--;k++;
    }
    dp[l][r][k] = calculatePoints(boxs, l, r-1, 0) + (k+1) * (k+1);
    for(int i = l; i < r-1; i++) {
        if(boxs[i] == boxs[r]) {
            dp[l][r][k] = max(dp[l][r][k], calculatePoints(boxs, l, i, k+1) + calculatePoints(boxs, i+1, r-1, 0));
        }
    }
    return dp[l][r][k];
}

int solution(int boxs[], int n)
{
	return calculatePoints(boxs, 0, n-1, 0);
}

int main()
{
	string str("");
	getline(cin, str);
	int boxs[MAX_NUM];
	int i = 0;
	char *p;
	int count = 0;
	
	const char* strs = str.c_str();
	p = strtok((char *)strs, " ");
	while(p)
	{
		boxs[i] = atoi(p);
		count++;
		p = strtok(NULL, " ");
		i++;
		if(i >= MAX_NUM)
			break;
	}

	int num = solution(boxs, count);
	cout << num << endl;
	return 0;
}