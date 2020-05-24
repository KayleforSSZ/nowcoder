/*
在一块长为n，宽为m的场地上，有n✖️m个1✖️1的单元格。每个单元格上的数字就是按照从1到n和1到m中的数的乘积。具体如下

n = 3, m = 3
1   2   3
2   4   6
3   6   9

给出一个查询的值k，求出按照这个方式列举的的数中第k大的值v。
例如上面的例子里，
从大到小为(9, 6, 6, 4, 3, 3, 2, 2, 1)
k = 1, v = 9
k = 2, v = 6
k = 3, v = 6
...
k = 8, v = 2
k = 9, v = 1
*/

/*
用二分法来求第K大的元素，把求第K大的元素转换成求第m*n+1-K个的元素
这里二分法可以这么做，左边界left初始为1， 右边界right初始为m*n，每次取两者的平均值mid，然后遍历数组，
找出有多少个元素比mid小，然后跟m*n+1-K作比较来决定是更新left还是right，

【注意】：遍历数组时，如果时双层循环判断i*j<=mid的话，线上会超时，所以可以通过比较mid/i与m来决定个数，这是一个很不错的优化的地方
*/


#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, m, k;
    cin >> n >> m >> k;
    long long left = 1, right = m * n;
    k = m * n - k + 1;  // 从小到大排第k
    long long mid;
    while(left < right) {
        mid = left + (right - left) / 2; 
        long long cnt = 0;	// cnt统计<= mid的元素个数
        for(int i = 1; i <= n; i++) {
            cnt += min(m, mid / i);		
        }
        if(cnt >= k) right = mid;
        else left = mid + 1;
    }
    cout << right << endl;
    return 0;
}