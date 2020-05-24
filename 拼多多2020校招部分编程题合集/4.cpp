/*
扔n个骰子，第i个骰子有可能投掷出Xi种等概率的不同的结果，数字从1到Xi。所有骰子的结果的最大值将作为最终结果。求最终结果的期望。
*/

/*
期望 = 每个数值 ✖ 数值出现的次数 / 总次数 求和
对于 n 个骰子，分别为x1, x2, ... xn，那么总的出现的次数就是 x1*x2*...*xn
我们将其排序，假设x1, x2, ... xn按从小到大排序，从最大的开始，那么如果要让最大值为xn，那么则让第n个骰子的取值为xn，其他骰子任取
因为不管前面n-1个骰子是否能出现xn，我们都只让第n个骰子取值xn，这样情况有x1*x2*...*xn-1种。然后我们第n个骰子的取值不能为xn了，则让xn--，
这时我们接着将其排序，仍然取最后一个骰子的最大值，这个最大值无论是不是与上一次的最大值相等都不影响
依次进行以上步骤，直到所有序列均为1
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> xi(n, 0);
    double f1 = 1, f2 = 1;
    for(int i = 0; i < n; i++) {
        cin >> xi[i];
        f1 *= xi[i];
    }
    sort(xi.begin(), xi.end());
    do
    {
        double t = 1;
        for(int i = 0; i < n-1; i++) {
            t *= xi[i];
        }
        f2 += t * xi.back();
        xi.back()--;
        sort(xi.begin(), xi.end());
    } while (xi.back() != 1);
    cout << fixed << setprecision(2) << f2 * 1.0 / f1 << endl;
    
    return 0;
}