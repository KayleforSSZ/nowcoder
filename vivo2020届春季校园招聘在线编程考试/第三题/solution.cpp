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