题目描述

农夫约翰想修理牧场周围的一小段篱笆。他测量栅栏，发现他需要 N(1≤N≤20,000)块木板，每块木板都有一个整数长度 Li(1≤Li≤50,000)个单位。然后他买了一块长木板，长度刚好够锯进 N 块木板(也就是说，它的长度是长度 Li 的总和)。 FJ 遗憾地意识到他没有锯木头的锯子，所以他带着这个长板来到农民唐的农场，礼貌地问他是否可以借一把锯子。农民唐是一个秘密的资本家，他没有借给 FJ 一把锯子，而是向农民约翰收取每锯 N-1次的费用。切割一块木头所消耗的能量正好等于它的长度。切一块长度为21的木板需要21美分。然后农夫唐让农夫约翰决定切割木板的顺序和位置。帮助农夫约翰确定他可以花多少钱来制造 N 块木板。FJ 知道他可以按照不同的顺序切割木板，因为切割出来的中间木板长度不同，所以会产生不同的费用。

输入

第一行:一个整数N，表示木板的数量 行2 . .N+1:每行包含一个描述所需木板长度的整数

输出

一个整数：他必须花费N-1次切割的最小金额

样例

|输入样例copy|输出样例copy|
|---|---|
|3<br>8<br>5<br>8|34|

提示

他想把一块长度为21的木板切成长度为8、5和8的小块。原板尺寸为8+5+8=21。第一次切割将花费21，并且应该用来将木板切成尺寸为13和8的碎片。第二次切割将花费13，并且应该用来将13切成8和5。这将花费21+13=34。如果21被切成16和5，第二次切割将花费16，总共37(超过34)。

## 题解
我们这一题我们的整个操作过程可以视为合并果子得过程，我们每一次将两块小的合并成一块大的，反过来的过程就相当于我们把一个完整的块锯成两块。

```CPP
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <cstring>
#include <vector>
#include <iomanip>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;
 
/*
需要注意，调用优先队列用到两个头文件，
一个是<queue>，
一个是<functional>（因为要用到greater<int>这个结构体）
*/
priority_queue<int, vector<int>, greater<int> > q;
//这是一个按照升序排列的优先队列（即最小堆），要特别注意，最小堆是greater<int>。
//这里注意格式，greater<int>的小于号和后面那个小于号之间要有空格，否则会CE
 
int main(){
    int n; 
    cin >> n; //开始时木板数量
    int cur; //当前输入的木板长度
    long long ans = 0; //返回值，总开销数（数据很大，注意要用long long）
    for(int i=0; i<n; i++){
        //输入数据
        cin >> cur;
        q.push(cur);
    }
    while(n-- > 1){
        int t1 = q.top(); q.pop();
        int t2 = q.top(); q.pop();
        int sum = t1 + t2;
        ans += sum;
        q.push(sum);
    }
    cout << ans << endl;
}
```