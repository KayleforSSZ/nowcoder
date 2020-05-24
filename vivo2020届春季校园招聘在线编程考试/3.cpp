/*
在vivo产线上，每位职工随着对手机加工流程认识的熟悉和经验的增加，日产量也会不断攀升。
假设第一天量产1台，接下来2天(即第二、三天)每天量产2件，接下来3天(即第四、五、六天)每天量产3件 … …
以此类推，请编程计算出第n天总共可以量产的手机数量。
*/

/*
找出量产为x的最大的天数，这样构成一个数组，只需要查询这个数组满足vi[i] >= n且 vi[i-1] < n即可找到第n天的产量
进而确定前n天的总产量
*/
class Solution {
public:
    /**
     *
     * @param n int整型 第n天
     * @return int整型
     */
    int solution(int n) {
        vector<int> vi(n+1, 0);
        for(int i = 1; i < n+1; i++) {
            vi[i] = vi[i-1] + i;
        }
        int ret = 0;
        for(int i = 1; i < n+1; i++) {
            if(vi[i] >= n && vi[i-1] < n) {
                ret += i * (n - vi[i-1]);
                break;
            }
            ret += i * (vi[i] - vi[i-1]);
        }
        return ret;
    }
};