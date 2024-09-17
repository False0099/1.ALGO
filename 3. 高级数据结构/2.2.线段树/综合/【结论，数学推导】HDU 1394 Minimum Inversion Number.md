## [[数学结论]] 

The inversion number of a given number sequence a1, a2, ..., an is the number of pairs (ai, aj) that satisfy i < j and ai > aj.  
  
For a given sequence of numbers a1, a2, ..., an, if we move the first m >= 0 numbers to the end of the seqence, we will obtain another sequence. There are totally n such sequences as the following:  
  
a1, a2, ..., an-1, an (where m = 0 - the initial seqence)  
a2, a3, ..., an, a1 (where m = 1)  
a3, a4, ..., an, a1, a2 (where m = 2)  
...  
an, a1, a2, ..., an-1 (where m = n-1)  
  
You are asked to write a program to find the minimum inversion number out of the above sequences.  

Input

The input consists of a number of test cases. Each case consists of two lines: the first line contains a positive integer n (n <= 5000); the next line contains a permutation of the n integers from 0 to n-1.  

Output

For each case, output the minimum inversion number on a single line.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|10<br>1 3 6 9 0 8 5 7 4 2|16|

Translation
我们给定一个序列，问这个序列和他的循环序列中，哪一个的逆序对结果最小。



## 题解
假设我们 $a_{1},a_{2},\dots a_{n}$ 的逆序数为 $sum$, $a_{n}$ 的逆序数为 $invn$,则 $a_{n},a_{1},\dots a_{n-1}$ 的逆序数就是 $sum-invn+比a_{n}小的数$ 。而由于我们输入的数是 0,1,2,..., n-1, 所以比 $a_{n}$ 小的数个数就为 $a_{n}$，并且 $invn=n-1-an$,所以我们的逆序数就是 $sum+2*a_n+1-n$。反过来，我们把一个数字移动到最后面，我们的 cnt 就会变更 n-1- $2*a[i]$ 个逆序对。这一步更新我们是可以暴力的 $o(1)$ 求出来的。

总结：
1. 我们首先取出我们最原始情况下的逆序对（树状数组、线段树）
2. 我们在原来的逆序对条件下，每次计算我们把第一位移到最后得到的逆序对的结果

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
using namespace std;

const int maxn=5010;
int n;
/******************线段树模板**********************/
int SegTree[maxn << 2], a[maxn];
int Query(int L, int R, int l, int r, int rt) {//区间查询,LR是查询区间,lr是总区间,rt是根结点一般为1
    if (l >= L && r <= R)
        return SegTree[rt];
    int m = (l + r) >> 1;
    int ans = 0;
    if (L <= m)
        ans += Query(L, R, l, m, rt << 1);
    if (R > m)
        ans += Query(L, R, m + 1, r, rt << 1 | 1);
    return ans;
}
void Update(int point, int value, int l, int r, int rt) {//单点更新，把point点的值改为value,lr是总区间,rt是根结点一般为1
    If (l == r) {
        SegTree[rt] = value;
        return;
    }
    int m = (l + r) >> 1;
    if (point <= m)
        Update(point, value, l, m, rt << 1);
    else
        Update(point, value, m + 1, r, rt << 1 | 1);
    SegTree[rt] = SegTree[rt << 1] + SegTree[rt << 1 | 1];
}
void init(){
    memset(a,0,sizeof a);
    memset(SegTree,0,sizeof SegTree);
}
/******************线段树模板**********************/
int main(void) {
    while (cin >> n) {
        int cnt = 0, ans;
        init();
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            cnt += Query(a[i] + 1, n - 1, 0, n, 1);//我们先查询数字前面有多少个大于它的数，就是逆序对的个数
            Update(a[i], 1, 0, n, 1);
        }
        ans = cnt;
        for (int i = 0; i < n - 1; i++)
            cnt = cnt + n - 1 - 2 * a[i], ans = min(ans, cnt);
        cout << ans << endl;
    }
    return 0;
}
```

