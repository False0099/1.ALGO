# [USACO 08 FEB] Hotel G

## 题目描述

The cows are journeying north to Thunder Bay in Canada to gain cultural enrichment and enjoy a vacation on the sunny shores of Lake Superior. Bessie, ever the competent travel agent, has named the Bullmoose Hotel on famed Cumberland Street as their vacation residence. This immense hotel has N (1 ≤ N ≤ 50,000) rooms all located on the same side of an extremely long hallway (all the better to see the lake, of course).

The cows and other visitors arrive in groups of size Di (1 ≤ Di ≤ N) and approach the front desk to check in. Each group i requests a set of Di contiguous rooms from Canmuu, the moose staffing the counter. He assigns them some set of consecutive room numbers r..r+Di-1 if they are available or, if no contiguous set of rooms is available, politely suggests alternate lodging. Canmuu always chooses the value of r to be the smallest possible.

Visitors also depart the hotel from groups of contiguous rooms. Checkout i has the parameters Xi and Di which specify the vacating of rooms Xi .. Xi +Di-1 (1 ≤ Xi ≤ N-Di+1). Some (or all) of those rooms might be empty before the checkout.

Your job is to assist Canmuu by processing M (1 ≤ M < 50,000) checkin/checkout requests. The hotel is initially unoccupied.

第一行输入 $n,m$，$n$ 代表有 $n$ 个房间 $(1\leq n \leq 50,000)$，编号为 $1 \sim n$，开始都为空房，$m$ 表示以下有 $m$ 行操作 $(1\leq m < 50,000)$，以下每行先输入一个数 $i$ ，表示一种操作：

若 $i$ 为 $1$，表示查询房间，再输入一个数 $x$，表示在 $1,2,...,n$ 房间中找到长度为 $x$ 的连续空房，输出连续 $x$ 个房间中左端的房间号，尽量让这个房间号最小，若找不到长度为 $x$ 的连续空房，输出 $0$。若找得到，在这 $x$ 个空房间中住上人。

若 $i$ 为 $2$，表示退房，再输入两个数 $x,y$ 代表房间号 $x \sim x+y-1$ 退房，即让房间为空。

你需要对每个输入 $1$ 输出对应的答案。

## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2.. M+1: Line i+1 contains request expressed as one of two possible formats: (a) Two space separated integers representing a check-in request: 1 and Di (b) Three space-separated integers representing a check-out: 2, Xi, and Di

## 输出格式

\* Lines 1.....: For each check-in request, output a single line with a single integer r, the first room in the contiguous sequence of rooms to be occupied. If the request cannot be satisfied, output 0.

## 样例 #1

### 样例输入 #1

```
10 6
1 3
1 3
1 3
1 3
2 5 5
1 6
```

### 样例输出 #1

```
1
4
7
0
5
```

## 题解
这一题与我们的花瓶题不同点在于，如果我们的花瓶题是一定要尽可能的放，就算放不了连续的也要强制间隔着放。我们这一题**只能连续的放**，放不了就只能全部拒绝。所以我们这一题只需要维护最大间隔长度即可。而我们的花瓶题要维护的不仅仅是最大间隔长度了，**本题求的是连续空区间的长度，花瓶题求得是空区间的总长度**。

我们这一题维护三个数值：以区间左端点开始的空房长度；以区间右端点开始的空房长度；整个区间的最长的空房长度。
对于区间合并，为了维护大区间的最长空房长度，我们可以对其进行分类讨论：
1. 最长空房区间在左儿子
2. 最长空方区间在右儿子
3. 最长空房区间跨越左右

我们只需要以上三中情况取最大值即可。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#define Ll long long
using namespace std;
struct tree{
    int xx,yy,l,r,m,p;//xx，yy是这个区间的范围，l,r代表这段区间的左右最长连续空位，m就是整段区间的连续空位，p是lazy标记 
}T[500000*8+1];
int n,m,x,y,z,ans;
void clean(int num){//这个显然就是lazy的下传 
    if(T[num].xx==T[num].yy)return;
    if(!T[num].p)return;
    int k=num+num;
    if(T[num].p==1){
        T[k].l=T[k].m=T[k].r=T[k+1].l=T[k+1].m=T[k+1].r=0;
        T[k].p=T[k+1].p=1;
    }else{
        T[k].l=T[k].m=T[k].r=T[k].yy-T[k].xx+1;
        T[k+1].l=T[k+1].m=T[k+1].r=T[k+1].yy-T[k+1].xx+1;
        T[k].p=T[k+1].p=2;
    }
    T[num].p=0;
}
void maketree(int x,int y,int num){
    T[num].xx=x;T[num].yy=y;
    T[num].l=T[num].r=T[num].m=y-x+1;//一开始全空房 
    if(x==y)return;
    int mid=(x+y)>>1;num=num<<1;
    maketree(x,mid  ,num  );
    maketree(mid+1,y,num+1);
}
int find(int x,int num){//找一个长度位x的区间，现搜索到第num个区间 
    clean(num);clean(num*2);clean(num*2+1); 
    if(T[num].l>=x)return T[num].xx;//如果这个区间的左连续区间足够，那么直接住在最左边吧 
    if(T[num*2].m>=x)return find(x,num*2);//如果左半段区间的最大值满足x，说明可以住在左子儿子的区间 
    if(T[num*2].r+T[num*2+1].l>=x)return T[num*2].yy-T[num*2].r+1;//这时判断中间的一块区域 
    return find(x,num*2+1);    //因为一定可以找到区间，但前面都找不到，那只可能在右半段的区间里了 
}
void gaoji(int num){//ohly~ohlyohlyohly~~ wearethegay~~~wearethegay~~~~~~~~随便取的函数命 
    int k=num<<1;
    clean(k);clean(k+1);
    T[num].l=T[k  ].l;//显然大区间的l是左小区间的l，但是如果左小区间全空，显然大区间的l要加上右小区间的l 
    if(T[k  ].l==T[k  ].yy-T[k  ].xx+1)T[num].l+=T[k+1].l;
    T[num].r=T[k+1].r;//同理 
    if(T[k+1].r==T[k+1].yy-T[k+1].xx+1)T[num].r+=T[k  ].r;
    T[num].m=max(T[k].m,T[k+1].m);//这个很显然啊 
    T[num].m=max(T[num].m,T[k].r+T[k+1].l);
}
void dec(int x,int y,int num){//这些和基本线段树差不多 
    clean(num);
    if(x<=T[num].xx&&T[num].yy<=y){T[num].l=T[num].r=T[num].m=0;T[num].p=1;return;}
    num=num<<1;
    if(x<=T[num  ].yy)dec(x,y,num  );
    if(y>=T[num+1].xx)dec(x,y,num+1);
    gaoji(num/2);
}
void pluss(int x,int y,int num){
    clean(num);
    if(x<=T[num].xx&&T[num].yy<=y){T[num].l=T[num].r=T[num].m=T[num].yy-T[num].xx+1;T[num].p=2;return;}
    num=num<<1;
    if(x<=T[num  ].yy)pluss(x,y,num  );
    if(y>=T[num+1].xx)pluss(x,y,num+1);
    gaoji(num/2);
}
int main()
{
    scanf("%d%d",&n,&m);
    maketree(1,n,1);
    while(m--){
        scanf("%d",&x);
        if(x==1){
            scanf("%d",&x);
            if(T[1].m<x){printf("0\n");continue;}//T[1].m是整个区间中的最大连续空位，这个判断显然成立 
            ans=find(x,1);//通过了上面一个判断，一定可以找出答案 
            printf("%d\n",ans);
            dec(ans,ans+x-1,1);//把新住进来的房间重置 
        }else{
            scanf("%d%d",&x,&y);
            pluss(x,x+y-1,1);//把新走出去的房间重置 
        }
    }
}
```