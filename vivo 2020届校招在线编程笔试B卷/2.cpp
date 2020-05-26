/*
今年7月份vivo迎来了新入职的大学生，现在需要为每个新同事分配一个工号。人力资源部同事小v设计了一个方法为每个人进行排序并分配最终的工号，具体规则是：
将N（N<10000）个人排成一排，从第1个人开始报数；如果报数是M的倍数就出列，报到队尾后则回到队头继续报，直到所有人都出列；
最后按照出列顺序为每个人依次分配工号。请你使用自己擅长的编程语言帮助小v实现此方法。
*/

/*
这是个约瑟夫环问题
最简单的方法就是用一个环形链表来存储，每次找到一个之后就去掉该节点，接着找

对于数学方法，待更新
*/


#include <bits/stdc++.h>
 
using namespace std;
 
/**
 * Welcome to vivo !
 */
 
typedef struct _node
{
    int num;
    struct _node * next;
    _node(int x) : num(x), next(nullptr) {}
}node;
 
_node* creatList(int n, int m) {
    _node *head = new _node(1);
    _node *res = head;
    for(int i  = 2; i <= n; i++) {
        _node *temp = new _node(i);
        head->next = temp;
        head = head->next;
    }
    head->next = res;
    return res;
}
 
void solution(int n, int m)
{
    _node *head = creatList(n, m);
    _node *pre; _node *post;
    if(m == 1) {
        while(n--) {
            cout << head->num << " ";
            head = head->next;
        }
        return;
    }
    while(head->next != head) {
        // 走 m 步
        for(int i = 1; i < m-1; i++) {
            head = head->next;
        }
        pre = head;
        head = head->next;
        // 删掉第m个点
        cout << head->num << " ";
        post = head->next;
        pre->next = post;
        // 更新head
        head = post;
    }
    cout << head->num << endl;
}
 
int main()
{
    int N;
    int M;
     
    string str("");
    getline(cin, str);
     
    char *p;
    const char* strs = str.c_str();
     
    p = strtok((char *)strs, " ");
    N = atoi(p);
 
    p = strtok(NULL, " ");
    M = atoi(p);
     
    solution(N, M);
     
    return 0;
}