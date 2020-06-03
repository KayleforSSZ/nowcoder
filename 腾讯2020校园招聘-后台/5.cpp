/*
小Q在进行一场竞技游戏,这场游戏的胜负关键就在于能否能争夺一条长度为L的河道,即可以看作是[0,L]的一条数轴。
这款竞技游戏当中有n个可以提供视野的道具−真视守卫,第i个真视守卫能够覆盖区间[xi,yi]。现在小Q想知道至少用几个真视守卫就可以覆盖整段河道。

输入描述:
输入包括n+1行。

第一行包括两个正整数n和L(1<=n<=105,1<=L<=109)

接下来的n行,每行两个正整数xi,yi(0<=xi<=yi<=109),表示第i个真视守卫覆盖的区间。 


输出描述:
一个整数，表示最少需要的真视守卫数量, 如果无解, 输出-1
*/

/*
贪心：
	先对结构体数组排个序，然后每次都取能前进的最大值，并让计数器加1

*/


#include <bits/stdc++.h>
using namespace std;
 
struct section {
    int l;
    int r;
};
 
bool cmp(section a, section b) {
    if(a.l == b.l) return a.r > b.r;
    else return a.l < b.l;
}
 
int solution(vector<section> &vec, int &L, int &n) {
    int res = 0;	// 每次前进的最终位置，当res >= L时，即表明走到了终点
    int num = 0;	// 记录已经使用的真视守卫
    int index = 0;	// 每次查找的起点，起到一个剪枝的作用
    while(res < L) {
        int temp = res;		// 查找满足这样条件的结构体 l <= res < r，我们要做的就是找到最大的这个 r，从而保证守卫数量最少
        for(int i = index; i < n; i++) {
            if(vec[i].l > res) {	// 因为数组是排序过的，一旦 l > res，那么后面的都是大于
                index = i;			// 此时可将这里作为下一次遍历的起点
                break;
            }
            if(vec[i].r > res) {	// 更新最大的终点
                temp = max(temp, vec[i].r);
            }
        }
        num++;
        res = temp;
    }
    return num;
}
 
int main()
{
    int n, L;
    cin >> n >> L;
    vector<section> vec(n);
    int Max = INT_MIN, Min = INT_MAX;
    for(int i = 0; i < n; i++) {	// 如果左边界最小值 min > 0 或者 有边界最大值 max < L，表明没法覆盖
        cin >> vec[i].l >> vec[i].r;
        if(Min > vec[i].l) Min = vec[i].l;
        if(Max < vec[i].r) Max = vec[i].r;
    }
    sort(vec.begin(), vec.end(), cmp);
    if(Min > 0 || Max < L) cout << -1 << endl;
    else cout << solution(vec, L, n) << endl;
    return 0;
}