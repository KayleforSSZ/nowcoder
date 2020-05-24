/*
现给定任意正整数 n，请寻找并输出最小的正整数 m（m>9），使得 m 的各位（个位、十位、百位 … …）之乘积等于n，若不存在则输出 -1。
*/


/*
显然这个数只能由若干个2到9的积组成才有解。如果不是则返回-1。

有解时，要保证最小，则先要保证数位最少。

所以分解因子的时候应当从大到小分解。

那么假设 n = 2^q1 * 3^q2 *...* 9^q8

显然为 m 为q1个2，q2个3等等以此类推连接起来即可
*/
class Solution {
public:
    /**
     * 输入一个整形数值，返回一个整形值
     * @param n int整型 n>9
     * @return int整型
     */
    int solution(int n) {
        vector<int> vi(10, 0);
        for(int i = 9; i >= 2; i--) {
            while(n % i == 0) {
                vi[i]++;
                n /= i;
            }
        }
        if(n > 1) return -1;
        int ret = 0;
        for(int i = 2; i <= 9; i++) {
            while(vi[i]--) ret = ret * 10 + i;
        }
        return ret;
    }
};