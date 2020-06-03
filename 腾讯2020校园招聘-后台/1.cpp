/*
小Q想要给他的朋友发送一个神秘字符串，但是他发现字符串的过于长了，于是小Q发明了一种压缩算法对字符串中重复的部分进行了压缩，
对于字符串中连续的m个相同字符串S将会压缩为[m|S](m为一个整数且1<=m<=100)，例如字符串ABCABCABC将会被压缩为[3|ABC]，
现在小Q的同学收到了小Q发送过来的字符串，你能帮助他进行解压缩么

输入描述:
输入第一行包含一个字符串s，代表压缩后的字符串。
S的长度<=1000;
S仅包含大写字母、[、]、|;
解压后的字符串长度不超过100000;
压缩递归层数不超过10层;

输出描述:
输出一个字符串，代表解压后的字符串。

输入例子1:
HG[3|B[2|CA]]F

输出例子1:
HGBCACABCACABCACAF
*/

#include <bits/stdc++.h>
using namespace std;

string solution(string s) {
    string res;
    string tmp;
    stack<char> st;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '[') st.push(s[i]);
        else if(s[i] == '|') continue;
        else if(isdigit(s[i])) st.push(s[i]);
        else if(isupper(s[i])) {
            if(st.empty()) {
                res += s[i];
            }
            else st.push(s[i]);
        }
        else if(s[i] == ']') {  // 开始出栈
            int num[3] = {0};
            int m = 2;
            while(!st.empty()) {
                char c = st.top();
                st.pop();
                if(c == '[') {
                    string s1 = tmp;
                    int n = num[0]*100+num[1]*10+num[2];
                    while(--n) tmp += s1;
                    break;
                }
                else if(isupper(c)) {    // 如果为大写字母
                    tmp.insert(0, 1, c);
                } else {                 // 如果为数字
                    num[m--] = c - '0';
                }
            }
            if(st.empty()) {
                res += tmp;
                tmp.clear();
            } else {
                for(int j = 0; j <tmp.size(); j++) st.push(tmp[j]);
                tmp.clear();
            }
        }
    }
    return res;
}

int main()
{
    string s;
    cin >> s;
    cout << solution(s) << endl;
    return 0;
}

/*
题目提示用递归来做，但是实在想不到怎么用递归来做，所以只能用笨方法了
遍历字符串，用栈来维护
	如果遇到 '[' 就入栈；
	如果遇到 '|' 就continue；
	如果遇到数字，因为数字一定是出现在 '[' 后面的，所以也要入栈；
	如果遇到的是大写字母，分两种情况
		1. 这个字母是在 "[]" 外面的，直接加在结果字符串后面
		2. 这个字母是在 "[]" 里面的，入栈，怎么判断是不是在 "[]" 里面，只需要判断栈是不是为空就行
	如果遇到的是 "]" 那么就要处理栈里的字符了
		因为这里的 "]" 一定与距离栈顶最近的 "["相匹配，所以需要把他俩之间的字符串计算出来，就是将字符拼接，
		然后遇到数字后统计数字，最后复制若干次字符串，这时需要【注意】了：
			如果栈为空，表明这个最大的"[]"走完了，将字符串加到结果字符串后面即可；
			如果栈不为空，因为有可能这个"[]"前后都有可能是字母或者是括号，所以为了避免复杂处理，直接将计算出来的字符串再
			推进栈中，就是相当于我们把栈里的"[]"这种字符串全部换成它应该的样子
*/