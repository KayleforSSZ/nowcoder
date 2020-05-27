/*
小v是公司的运维工程师，现有一个有关应用程序部署的任务如下：
1、一台服务器的磁盘空间、内存是固定的，现在有N个应用程序要部署；
2、每个应用程序所需要的磁盘、内存不同，每个应用程序允许访问的用户数也不同，且同一个应用程序不能在一台服务器上部署多个。
对于一台服务器而言，如何组合部署应用程序能够使得单台服务器允许访问的用户数最多？
*/

/*

背包问题，传统背包问题只有容量这一个限制条件，而本题限制条件为2个，一是磁盘空间不超，2是内存空间不超

dp[i][d][m]表示前i个程序恰好磁盘空间不超过d，内存空间不超过m，所获得的最大用户数

那么 两种情况：

	1. 不放第 i 个程序，dp[i][d][m] = dp[i-1][d][m]
	2. 放第 i 个程序，dp[i][d][m] = dp[i-1][d-disks[i]][m-mems[i]] + users[i];

所以 dp[i][d][m] = max( dp[i-1][d][m], dp[i-1][d-disks[i]][m-mems[i]] + users[i] );

这里可以省略第一维 i ，从而节省空间，前提是从大到小遍历

*/
#include <bits/stdc++.h>
using namespace std;
int getCountOfApp(const char* input){
    if(NULL == input){
        return 0;
    }
    int cnt = 0;
    for(int i=0;input[i]!=0;++i){
        if(input[i] == ','){
            ++cnt;
        }
    }
    return cnt/2;
}
 
//id start from 0
int getPositionOfApp(const char* input, const int id){
    int cntOfComma = id*2 + 1;
    int i=0;
    for(;input[i]!=0&&cntOfComma!=0;++i){
        if(input[i] == ','){
            --cntOfComma;
        }
    }
    while(input[--i]!=' '&&input[i]!='#');
    return i+1;
}
 
#define APP_MAX 1000
#define DP_MAX 2048
int disks[APP_MAX];
int mems[APP_MAX];
int users[APP_MAX];
int dp[DP_MAX][DP_MAX];
 
int solution(const char* input){
    const int countOfApp = getCountOfApp(input);
    if(0 == countOfApp){
        return 0;
    }
    int res = 0;
 
    int disk = 0;
    int mem = 0;
 
    sscanf(input, "%d %d", &disk, &mem);
 
    for(int i=0; i< countOfApp;++i){
        const int pos = getPositionOfApp(input, i);
        sscanf(input+pos, "%d,%d,%d", &disks[i], &mems[i], &users[i]);
    }
    // TODO Write your code here!
    fill(dp[0], dp[0] + DP_MAX*DP_MAX, 0);
    for(int i = 0; i < countOfApp; i++) {
        for(int d = disk; d >= disks[i]; d--) {
            for(int m = mem; m >= mems[i]; m--)
                dp[d][m] = max(dp[d][m], dp[d - disks[i]][m - mems[i]] + users[i]);
        }
    }
    res = dp[disk][mem];
    return res;
}
 
int main(int argc, char* args[])
{
    char input[10000];
    cin.getline(input,10000);
    cout<<solution(input)<<endl;
}