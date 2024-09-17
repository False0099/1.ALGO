# [HAOI 2007] 覆盖问题

## 题目描述

某人在山上种了 $N$ 棵小树苗。冬天来了，温度急速下降，小树苗脆弱得不堪一击，于是树主人想用一些塑料薄膜把这些小树遮盖起来，经过一番长久的思考，他决定用 $3$ 个 $L \times L$ 的正方形塑料薄膜将小树遮起来。我们不妨将山建立一个平面直角坐标系，设第 $i$ 棵小树的坐标为 $(X_i,Y_i)$ ，$3$ 个 $L \times L$ 的正方形的边要求平行于坐标轴，一个点如果在正方形的边界上，也算作被覆盖。当然，我们希望塑料薄膜面积越小越好，即求 $L$ 最小值。

## 输入格式

接下来有 $N$ 行，第 $i+1$ 行有 $2$ 个整数 $X_i,Y_i$，表示第 $i$ 棵树的坐标，保证不会有 $2$ 个树的坐标相同。

## 输出格式

一行，输出最小的 $L$ 值。

## 样例 #1

### 样例输入 #1

```
4
0 1
0 -1
1 0
-1 0
```

### 样例输出 #1

```
1
```

## 提示

对于 $100\%$ 的数据，$-1,000,000,000 \le X_i,Y_i \le 1,000,000,000。$

对于 $30\%$ 的数据，$N \le 100。$

对于 $50\%$ 的数据，$N \le 2000。$

对于 $100\%$ 的数据，$N \le 20000。$

## 题解
本题我们的思路是，通过我们的二分来找到我们的最小的 L，这一点是显然的，我们的 L 一定是越大越能满足要求的。于是，我们就可以考虑我们的下面的方法：我们枚举我们的 L，我们再去看怎么去检查我们的 L

我们有下面的结论：**我们每一次防止我们的布，一定是放在当前的所有四个角落之一的，也就是我们每一次只可能放在我们的下面四种情况之一**。
```
update(minx,minx+l,miny,miny,depth);
update(minx,minx+l,maxy-l,maxy,depth);
update(maxx-l,maxx,miny,miny+l,depth);
update(maxx-l,maxx,maxy-l,maxy,depth);
```

最后，我们只有三块布，我们就可以简单的 dfs 求得答案了。
```cpp
#include <bits/stdc++.h>
#define int long long
int INF=0x3f3f3f3f3f;
const int N=1e5+10;
using namespace std;
struct node{
    int x;
    int y;
    int depth;
}a[N];
int n;
bool check(){
    for(int i=0;i<n;i++){
        if(a[i].depth==-1){
            return false;
        }
    }
    return true;
}
void update(intminx,int maxx,int miny,int maxy,int depth){
    for(int i=0;i<n;i++){
        if(a[i].depth==-1){
           if(a[i]x>=minx&&a[i].x<=maxx&&a[i].y<=maxy&&a[i].y>=miny){
                a[i].depth=depth;
            }
        }
    }
}
void deupdate(it minx,int maxx,int miny,int maxy,int depth){
    for(int i=0;i<n;i++){
        if(a[i].depth==depth){
            a[i].depth=-1;
        }
    }
}
bool dfs(int cnt,int l){
    if(cnt==3){
        return check();
    }
    int minx=INF,miny=INF,maxx=-INF,maxy=-INF;
    for( int i=0;i<n;++i)
    {
        if(a[i].depth==-1)
        {
            if(a[i].x>maxx) maxx=a[i].x;
            if(a[i].x<minx) minx=a[i].x;
            if(a[i].y>maxy) maxy=a[i].y;
            if(a[i].y<miny) miny=a[i].y;
        }
    }
    bool u=0;
    int depth=cnt;
    update(minx,minx+l,miny,miny,depth);
    u|=dfs(cnt+1,l);
    deupdate(minx,minx+l,miny,miny,depth);
    update(minx,minx+l,maxy-l,maxy,depth);
    u|=dfs(cnt+1,l);
    deupdate(minx,minx+l,maxy-l,maxy,depth);
    update(maxx-l,maxx,miny,miny+l,depth);
    u|=dfs(cnt+1,l);
    deupdate(maxx-l,maxx,miny,miny+l,depth);
  
    update(maxx-l,maxx,maxy-l,maxy,depth);
    u|=dfs(cnt+1,l);
    deupdate(maxx-l,maxx,maxy-l,maxy,depth);
    return u;
}
void solve(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].depth=-1;
    }
    int l=0;
    int r=INF;
    while(l<r){
        int mid=l+r>>1;
        if(dfs(0,mid)){
            r=mid;
        }else{
            l=mid+1;
        }
    }
   // cerr<<dfs(0,0)<<endl;
    cout<<l<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    while(t--){
        solve();
    }
}
```