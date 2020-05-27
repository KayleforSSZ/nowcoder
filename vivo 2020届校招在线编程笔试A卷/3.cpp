/*

小v所在的公司即将举行年会，年会方案设计过程中必不可少的一项就是抽奖活动。小v在本次活动中被委以重任，负责抽奖活动的策划；为了让中奖的礼物更加精美且富有神秘感，打算采用礼品盒来包装奖品，此时小v发挥了自己的创意想捉弄一下获奖的同事，便采取了多重包装来包装奖品。

现给出一个字符串，并假定用一对圆括号( )表示一个礼品盒，0表示奖品，你能据此帮获奖者算出最少要拆多少个礼品盒才能拿到奖品吗？

输入描述:
一行字符串，仅有'('、')'、'0' 组成，其中一对'(' ')'表示一个礼品盒，‘0’表示奖品；输入的字符串一定是有效的，即'(' ')'一定是成对出现的。

*/


/*
	括号成对出现，那么我们可以使用一个栈，遍历字符串，为左括号时就进栈，为右括号时就出栈，
	为0时就结束循环，此时栈里的元素个数就是最终结果


*/

#include <bits/stdc++.h>
using namespace std;
 
int solution(string str)
{
    int sum = 0;
    stack<char> st;
    for(int i = 0; i < str.length(); ++i) {
        if(str[i] == '0') return st.size();
        else if(str[i] == '(') st.push('(');
        else st.pop();
    }
 
    return sum;
}
 
int main()
{
    string str("");
    getline(cin, str);
 
    int sum = solution(str);
    cout << sum << endl;
    return 0;
}

