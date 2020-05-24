
/*
数列 {An} 为N的一种排列。
例如N=3，可能的排列共6种：

1 | 1, 2, 3
2 | 1, 3, 2
3 | 2, 1, 3
4 | 2, 3, 1
5 | 3, 1, 2
6 | 3, 2, 1
定义函数F:

F(x) = A1,  		  x = 1;
	  |F(x-1) - Ax|,  x > 1

其中|X|表示X的绝对值。

现在多多鸡想知道，在所有可能的数列 {An} 中，F(N)的最小值和最大值分别是多少。
*/

/*
这道题的意思就是一个数N，有很多种排列组合，我们在这么多排列组合中根据 F(x) 的定义，找到 F(N) 的最大和最小值，
F(N)最大和最小时的排列组合有可能不一样
对于N = 3：
	当排列为 3 2 1 时，可以得到F(3)的最小值 0
	当排列为 2 1 3 时，可以得到F(3)的最大值 2
*/

/*
一开始想着计算出 N 对应的所有的排列组合，然后用一个min和一个max来记录最大和最小值，遍历这些排列组合来更新min和max
结果在N很大的时候程序超时，显然这道题不能用这种方法
那就要找规律

我们发现，每相邻的四个数可以构成最小值0，比如这四个数 5, 6, 7, 8，那么当排列为8 6 7 5 时最小值为0，因为F(4) = |||8 - 6| - 7| - 5| = 0
这样我们就能发现，如果我们把排列组合这些数，每四个一组，就会产生一个0，相当于最小值的变化也是每4个一组。
我们就只需要求出前3个数的最小值就可以知道后面所有的数的最小值了
F(0)min = 0
F(1)min = 1
F(2)min = 1
F(3)min = ||3 - 2| - 1| = 0
F(N)min = F(N % 4)min

剩下求最大值，我们已经知道了最小值，因为 F(x) = |F(x-1) - Ax|，那么我们可以发现如果要求F(N)max，那么就要Ax最大且F(N-1)最小

即F(N)max = |F(N-1)min - N|，即F(N)max = N - F(N-1)min。

*/

// 全排列，时间超限
#include <bits/stdc++.h>
using namespace std;

vector<int> solution(int n) {
    vector<int> res(2, 0);
    int Max = 0, Min = INT_MAX;
    vector<int> temp(n, 0);
    for(int i = 0; i < n; i++) {
        temp[i] = i+1;
    }
    do
    {
        int f = temp[0];
        for(int i = 1; i < n; i++) {
            f = abs(f - temp[i]);
        }
        if(Max < f) Max = f;
        if(Min > f) Min = f;
    }while(next_permutation(temp.begin(), temp.end()));
    res[0] = Min, res[1] = Max;
    return res;
}

int main()
{
    int T, N;
    cin >> T;
    vector<int> group(T, 0);
    for(int i = 0; i < T; i++) {
        cin >> group[i];
    }

    for(int i = 0; i < T; i++) cout << solution(group[i])[0] << " " << solution(group[i])[1] << endl;
    return 0;
}

// 找规律
vector<int> solution(int n) {
    vector<int> res(2, 0);
    vector<int> dp(n+1, 0);
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 0;
    for(int i = 4; i <= n; i++) {
        dp[i] = dp[i%4];
    }
    res[0] = dp[n];
    res[1] = n - dp[n-1];
    return res;
}

int main()
{
    int T, N;
    cin >> T;
    vector<int> group(T, 0);
    for(int i = 0; i < T; i++) {
        cin >> group[i];
    }
    for(int i = 0; i < T; i++) cout << solution(group[i])[0] << " " << solution(group[i])[1] << endl;
    return 0;
}