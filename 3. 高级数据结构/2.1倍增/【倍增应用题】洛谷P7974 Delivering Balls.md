# [KSN 2021] Delivering Balls

## 题目描述

给定一个长度为 $N$ 的序列 $H$ 和 $Q$ 次询问。

第 $i$ 次询问中，你初始在第 $S_i$ 列 $H_{S_i}$ 行，想要到第 $T_i$ 列第 $H_{T_i}$ 行。

你可以进行若干次移动。每次移动你可以选择以下两种参数：

* 列 $-1$，列不变，列 $+1$。
* 行 $-1$，行不变，行 $+1$。

如果你选择行 $-1$，消耗 $1$ 体力，如果你选择行不变，消耗 $2$ 体力，如果你选择行 $+1$，消耗 $4$ 体力。

你需要保证每次移动后，你的列数 $x$ 在 $[1,N]$ 之间，且你的行数 $y$ 不小于 $H_x$。

对于每个询问，你需要求出你消耗体力的最小值。

## 输入格式

第一行输入一个正整数 $N$。

第二行输入 $N$ 个正整数 $H_i$。

接下来 $Q$ 行，每行输入两个正整数 $S_i,T_i$。

## 输出格式

对于每个询问，输出一行，包含一个整数，代表消耗体力的最小值。

## 样例 #1

### 样例输入 #1

```
4
9 1 8 2
2
1 3
4 2
```

### 样例输出 #1

```
3
31
```

## 样例 #2

### 样例输入 #2

```
9
1 2 3 2 1 2 3 2 1
4
1 9
4 6
2 6
5 2
```

### 样例输出 #2

```
18
4
9
9
```

## 提示

**【样例解释】**

以下为第一个样例中两个询问的图示：

![](https://sandalphon.tlx.toki.id/api/v2/problems/JIDPROG92Su7ScrLh6DkhILekKA/render/roket-q-1.png) ![](https://sandalphon.tlx.toki.id/api/v2/problems/JIDPROG92Su7ScrLh6DkhILekKA/render/roket-q-2.png)

**【数据范围】**

- Subtask 1（7 points）：只存在一组数据，满足 $N=8$，$Q=4$，$H=[,9,3,3,5,4,8,2]$，$(S_i,T_i)$ 依次为 $(1,8)$，$(3,6)$，$(6,4)$ 和 $(7,2)$。
- Subtask 2（5 points）：$S_i+1=T_i$。
- Subtask 3（6 points）：$H_i=i$。
- Subtask 4（18 points）：$N,Q,H_i\leq 100$。
- Subtask 5（24 points）：$N,Q\leq 1000$。
- Subtask 6（13 points）：$S_i=1$。
- Subtask 7（27 points）：无特殊限制。

对于所有数据，$2\leq N\leq 2\times 10^5$，$H_i\leq 10^9$，$Q\leq 2\times 10^5$，$1\leq S_i,T_i\leq N$。

## 题解
考虑删除掉我们的行数约束，我们又有什么方法？我们这个时候，我们的最终的步数显然是**唯一的**，我们一定是尽可能的先让我们的高度调整到相同的，然后再去向左向右行动。

但是，我们这一题由我们的行数约束，我们要怎么考虑我们的现在的新问题呢？可以将**数列想象成二维地图**，$h_i$ 就是在 $i$ 位置上的山的高度。自然我们到不了山里 (你的行数 $y$ 不小于 $H_x)$。向左上、正上、右上花费 4；向左，右花费 2；左下、正下、右下花费 1。
![[Pasted image 20240822144750.png]]

对于一个询问，我们可以先认为 $s<t$。
这样，我们水平移动的次数就决定好了，因此我们应当尽量的利用水平移动的步数向上 (向下)走。对于 $s$ 来说，我们让他尽量向右上走，这样它的轨迹就是一条斜率为 1 的直线 (下图红色) 。

![[Pasted image 20240822145003.png]]


显然我们可以发现，等到撞上墙了再往上升，不如再起点处就向上。（绿+灰）那么我们这个时候要**预先向上的就是我们的 $max(h_{i}-(h_{s}+(i-s)))$**。

因此，我们只需要维护我们的一个 $h_{i}-i$ 即可。但是这个并不是正确的，我们可能在**过程中撞墙**。对于这一种撞墙的问题，我们首先找到**撞墙的位置最大可能是哪里**，然后预先向上走，然后再进行我们的处理。

之后，我们就可以写出我们的代码：
```
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f;
using namespace std;
const int N=2e5+10;
int h[N];
int max_h[N][32];//h
int max_hi[N][32];//h-i
int max_ih[N][32];//h+i
int lg[N];
void init(){
    
}
int query_h(int l,int r){
    int len=lg[r-l+1];
    return max(max_h[l][len],max_h[r-(1<<len)+1][len]);
}
int query_hi(int l,int r){
    int len=lg[r-l+1];
    return max(max_hi[l][len],max_hi[r-(1<<len)+1][len]);
}
int query_ih(int l,int r){
    int len=lg[r-l+1];
    return max(max_ih[l][len],max_ih[r-(1<<len)+1][len]);
}
void solve(){
    int n;
    cin>>n;
    lg[1]=0;
    for(int i=2;i<=n;i++){
        lg[i]=lg[i>>1]+1;
    }
    for(int i=1;i<=n;i++){
        cin>>h[i];
        max_h[i][0]=h[i];
        max_hi[i][0]=h[i]-i;
        max_ih[i][0]=h[i]+i;
    }
    for(int k=1;k<=lg[n];k++){
        for(int i=1;i+(1ll<<k)-1<=n;i++){
            max_h[i][k]=max(max_h[i][k-1],max_h[i+(1ll<<k-1)][k-1]);
            max_hi[i][k]=max(max_hi[i][k-1],max_hi[i+(1ll<<k-1)][k-1]);
            max_ih[i][k]=max(max_ih[i][k-1],max_ih[i+(1ll<<k-1)][k-1]);
        }
    }
    int m;
    cin>>m;
    for(int i=1;i<=m;i++){
        int s,t;
        cin>>s>>t;
        int l = min(s, t), r = max(s, t);
        int a=query_h(l,r);
        int b=query_hi(l,r);
        int c=query_ih(l,r);
        cout<<a-4*h[s]-h[t]+2*(b+c)<<endl;
    }
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    //cin>>t;
    init();
    while(t--){
        solve();
    }
}
```
```