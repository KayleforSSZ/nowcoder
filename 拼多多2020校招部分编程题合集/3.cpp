/*
多多鸡打算造一本自己的电子字典，里面的所有单词都只由a和b组成。
每个单词的组成里a的数量不能超过N个且b的数量不能超过M个。
多多鸡的幸运数字是K，它打算把所有满足条件的单词里的字典序第K小的单词找出来，作为字典的封面。
*/

/*
是一个递归的题，可以用一个vector来存这些字符，用一个num来记录这是字典序为num的单词，
用一个数组来记录a和b的剩余个数，每次往vector里面push一个字符就让num++，这样当num==K时就可以终止了
需要注意的是每次都优先push a，只有当a的个数为0时才会push b，这样就能保证始终是字典序
但是这样程序会超时，因为缺少剪枝
*/
#include <bits/stdc++.h>
using namespace std;

void dfs(int &num, int K, vector<int> &mp, vector<char> &temp, bool &sig) {
    num++;
    if(num == K && !sig) {
        sig = true;
        return;
    }
    if(mp[0]) {
        temp.push_back('a');
        mp[0]--;
        dfs(num, K, mp, temp, sig);
        if(sig) return;
        temp.pop_back();
        mp[0]++;
    }
    if(mp[1]) {
        temp.push_back('b');
        mp[1]--;
        dfs(num, K, mp, temp, sig);
        if(sig) return;
        temp.pop_back();
        mp[1]++;
    }
}

int main()
{
    int N, M, K;
    bool sig = false;
    int num = -1;
    cin >> N >> M >> K;
    vector<char> temp;
    vector<int> mp = {N, M};
    dfs(num, K, mp, temp, sig);
    for(int i = 0; i < temp.size(); i++) cout << temp[i];
    cout << endl;
}

/*
这个方案就是用一个map来记录a的个数<= n，b的个数<= m的所有排列的个数，f(m,n)函数就是来构造这个map的，这样就能防止重复计算
然后依次固定一个字符，再判断所求的K是不是位于固定这个字符的区间内，比如固定第一个字符为a，然后求第一个字符为a的排列的个数，
如果K位于这个区间内，就表明第一个字符为a。如果不在这个区间内，就表明第一个字符是b，这时候需要更新k
*/

#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, unsigned long long> ma;
 

 /*计算a的个数小于m，b的个数小于n的所有排列的个数*/
 /*
 f(m, n) = f(m-1, n) + 1 + f(m, n-1) + 1;
 m个a，n个b，相当于有两种情况，
 1：在m-1个a，n个b的时候往里面添加一个a，那么相当于往每一个排列的末尾添加一个a，有f(m-1, n)种，还有单独一个a的情况，这样每一种排列末尾都是a
 2：在m个a，n-1个b的时候往里面添加一个b，那么相当于往每一个排列的末尾添加一个b，有f(m, n-1)种，还有单独一个b的情况，这样每一种排列末尾都是b
 因为末尾分别是a和b，所以也不会造成重复，总的就变成  f(m, n) = f(m-1, n) + 1 + f(m, n-1) + 1;

 */
unsigned long long f(int m,int n)
{
    if(ma.count({m, n})) return ma[{m, n}]; // 如果已经计算过了，直接返回
    if(!m) ma[{m, n}] = n;                  // 如果m为0，相当于只有n个b，那么只有n种情况
    else if(!n) ma[{m, n}] = m;             // 如果n为0，相当于只有m个a，那么只有m种情况
    else ma[{m, n}] = f(m-1, n) + f(m, n-1)+2;  // 否则，计算个数
    return ma[{m, n}];
}
 
int main()
{
    long long k;
    int n,m;
    cin >> n >> m >> k;
    string cur = "a";
    n--;
    k--;
    while(k > 0 && (m || n))    // m和n不全为0
    {
        unsigned long long step = f(n, m) + 1; // 这里相当于开头是a，那么剩下的a和b能构成f(n, m) + 1种情况
        if(step > k)    // 第k种在这f(n, m)+1种情况里，也就是开头是a
        {
            k--;        
            if(n)       // 假设第二个字符是a，然后接着执行while循环
            {
                cur += "a";
                n--;
            }else{      // 假设第二个字符是b，然后接着执行while循环
                cur += "b";
                m--;
            }
        }else{          // 第k种不在这f(n, m)+1种情况里，也就是开头是b
             k -= step; // 这里一定要减去step，因为k是将a排在前面时的计数，而f(m, n)只会记录个数
             n++;       // n复原
             m--;       
             cur.back()++;  //'a'++ = 'b'，相当于把最后一位变成b
        }
    }
    cout << cur << endl;
    return 0;
}