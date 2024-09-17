有一个长度为 L 个单位长度的木板，现在要给木板染色（每个单位长度只能同时有一种颜色）。执行两种操作：  
  
1. "C A B C" 将 A 到 B 段染成颜色 C .  
2. "P A B" 输出 A 到 B 段（含 A 和 B ）不同颜色的数量。  
  
假设不同颜色的总数 T 非常小，并将颜色命名为 11，22，33，...，T.  
初始时，整个木板都被染成了颜色 11 .

Input

第一行为 L (1 <= L <= 100000), T (1 <= T <= 30) 和 O (1 <= O <= 100000). O 表示操作数。  
  
接下来 O 行，每行包含 "C A B C" 或者 "P A B"，如前面所定义的操作。A, B ,C 是整数, 且 A 可能比 B 大。

Output

每行包含一个数字，为每次查询的结果。

Sample

|Inputcopy|Outputcopy|
|---|---|
|2 2 4<br>C 1 1 2<br>P 1 2<br>C 2 2 2<br>P 1 2|2<br>1|

## 题解
题目要求我们维护区间上出现的数字的种类，这一点理论上我们应该用我们的离线分块算法去计算，但因为我们有修改，所以分块也许并不是那么的好用，如果没有修改，我们就可以直接离线莫队，cnt++--操作即可。

但因为我们这一题颜色的种类不多，所以我们其实可以用我们的状态压缩来表示我们每一个区间内的颜色，到时候我们合并的时候暴力合并即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
#include<cstring>
#include<set>
#include<map>
#include<queue>
#include<string>
#include<cmath>
#include<climits>
 
using namespace std;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
const int MAXN=100001;
int color[MAXN<<2];
int change[MAXN<<2];
int kind,ans;
 
void push_up(int rt){
    color[rt]=color[rt<<1]|color[rt<<1|1];
}
 
void push_down(int rt){
    if (change[rt]){
        change[rt<<1]=change[rt];
        change[rt<<1|1]=change[rt];
        color[rt<<1]=change[rt];
        color[rt<<1|1]=change[rt];
        change[rt]=0;
    }
}
 
void build(int l,int r,int rt){
    change[rt]=0;
    if (l==r){
        color[rt]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
    push_up(rt);
}
 
void update(int a,int b,int c,int l,int r,int rt){
    if (a<=l && b>=r){
        change[rt]=c;
        color[rt]=c;
        return;
    }
    push_down(rt);
    int mid=(l+r)>>1;
    if (a<=mid){
        update(a,b,c,lson);
    }
    if (b>mid){
        update(a,b,c,rson);
    }
    push_up(rt);
}
 
void query(int a,int b,int l,int r,int rt){
    if (a<=l && b>=r){
        kind|=color[rt];
        return;
    }
    push_down(rt);
    int mid=(l+r)>>1;
    if (a<=mid){
        query(a,b,lson);
    }
    if (b>mid){
        query(a,b,rson);
    }
    // update的时候该push_up的节点都push_up过了 这里只需要update节点的颜色
//    push_up(rt);
}
 
int main(){
    int L,T,O;
    int a,b,c;
    char op[2];
    while (~scanf("%d %d %d",&L,&T,&O)){
        build(1,L,1);
        while (O--){
            scanf("%s",op);
            if (op[0]=='C'){
                scanf("%d %d %d",&a,&b,&c);
                if (a>b) swap(a,b);
//                cout<<op<<","<<a<<","<<b<<","<<c<<endl;
                c=1<<(c-1);
                update(a,b,c,1,L,1);
            } else{
                scanf("%d %d",&a,&b);
                if (a>b) swap(a,b);
//                cout<<op<<","<<a<<","<<b<<endl;
                kind=0;
                ans=0;
                query(a,b,1,L,1);
                for (int i = 0; i < T; ++i) {
                    if (kind & (1<<i)){
                        ans++;
                    }
                }
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
```