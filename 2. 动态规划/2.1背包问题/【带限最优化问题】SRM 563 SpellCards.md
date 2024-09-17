有 n 张符卡排成一个队列，每张符卡有两个属性，等级 li 和伤害 di。你可以做任意次操作，每次操作为以下二者之一：
1. 把队首的符卡移动到队尾。使用队首的符卡
2. 对敌人造成 $d_{i}$ 点伤害，并丢弃队首的 $l_{i}$ 张符卡 (包括你所使用的符卡) 。如果队列不足 li 张符卡那么你不能使用。

求出造成的伤害的总和的最大值。
$1< = n< = 50, 1< = |$ i$< = 50, 1< = $di$ < = 10000$


## 题解
这一题我们是一个结论题，首先我们需要推导出我们的结论：只要我们选出的卡牌满足 $\sum L_{i}\leq N$,那么我们总有一种方案能够打出这种牌。

具体的证明，我们可以考虑先把我们的链看成一个环，然后再把我们的环上进行考虑就会相对直观一些。

```cpp
 
#include<bits/stdc++.h>
using namespace std;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int f[100];
 
class SpellCards{
public:
    int maxDamage(vector<int> l, vector<int> d) {
        int N = l.size();
        for(int i = 0; i < N; i++) 
            for(int j = N; j >= l[i]; j--)
                f[j] = max(f[j], f[j - l[i]] + d[i]);
        return *max_element(f + 1, f + N + 1);
    }
};
 
int main() {
    int N = read();
    vector<int> l, d;
    for(int i = 1; i <= N; i++) l.push_back(read());
    for(int i = 1; i <= N; i++) d.push_back(read());
    cout << SpellCards().maxDamage(l, d);
}
/*
7
1 2 2 3 1 4 2
113 253 523 941 250 534 454
*/
```