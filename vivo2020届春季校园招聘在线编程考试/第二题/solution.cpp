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