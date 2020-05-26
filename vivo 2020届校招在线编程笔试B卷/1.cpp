/*
小v最近在玩一款挖矿的游戏，该游戏介绍如下：
1、每次可以挖到多个矿石，每个矿石的重量都不一样，挖矿结束后需要通过一款平衡矿车运送下山；
2、平衡矿车有左右2个车厢，中间只有1个车轮沿着导轨滑到山下，且矿车只有在2个车厢重量完全相等且矿石数量相差不超过1个的情况下才能成功运送矿石，否则在转弯时可能出现侧翻。
假设小v挖到了n（n<100）个矿石，每个矿石重量不超过100，为了确保一次性将n个矿石都运送出去，一旦矿车的车厢重量不一样就需要购买配重砝码。请问小v每次最少需要购买多少重量的砝码呢? （假设车厢足够放下这些矿石和砝码，砝码重量任选）

*/

/*
动态规划，限制条件为2个，1是重量最接近，2是矿石个数之差不超过1
int f[i][j]表示用了 i 块石头，能否达到重量为 j ，如果能的话就看 i 是否是总石头数量的一半，如果是，看此时的差是否需要更新
*/
#include <bits/stdc++.h>
using namespace std;

#define MAX_NUM 101
int solution(int n, int weight[]) {
    int sum=0;
    for(int i = 0; i < n; i++) sum += weight[i];
    vector<vector<int> > f(110, vector<int>(10010, 0));
    int ans = 0;		// ans记录最小配重砝码所对应的一半车厢的重量
    int halfN = n / 2;	// 石头的一半
    int Min = 100000;	// 记录最小配重砝码
    f[0][0]=1;
    for(int i = 0; i < n; i++){ 
        for(int j = sum; j >= weight[i]; j--){
            for(int h = n - 1; h >= 0; h--){
                if(f[h][j - weight[i]]){	// 如果h个石头能达到重量j - weight[i],那么h+1个石头（加上第i个石头）能达到重量j
                    f[h + 1][j]=1;
                    if(h + 1 == halfN){		// 判断是否满足一半石头
                        if(abs(sum - 2 * j) < Min){	// 判断是否需要更新Min
                            Min = abs(sum - 2 * j);
                            ans = j;
                        }
                    }
                }
            }
        }
    }
    return abs(sum - ans - ans);	// 这里不能返回Min，因为有可能在循环里不改变Min，此时Min为100000，而结果应该为sum
}
  
int main()
{   
    string str("");
    getline(cin, str);
    int a[MAX_NUM];
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
        if(i >= MAX_NUM)
            break;
    }
      
    int result = solution(count, a);
    cout << result << endl;
    return 0;
}