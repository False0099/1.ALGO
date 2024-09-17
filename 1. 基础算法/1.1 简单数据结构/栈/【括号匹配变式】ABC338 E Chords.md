### Problem Statement

There are $2N$ points placed at equal intervals on a circle, numbered $1$ to $2N$ in a clockwise direction starting from a certain point.

There are also $N$ chords on the circle, with the $i$ \-th chord connecting points $A_i$ and $B_i$. It is guaranteed that all the values $A_1,\dots,A_N,B_1,\dots,B_N$ are distinct.

Determine whether there is an intersection between the chords.

### Constraints

-   $2\leq N \leq 2\times 10^5$
-   $1\leq A_i,B_i \leq 2N$
-   $A_1,\dots,A_N,B_1,\dots,B_N$ are all distinct
-   All input values are integers

### Input

The input is given from Standard Input in the following format:

```
$N$
$A_1$ $B_1$
$A_2$ $B_2$
$\vdots$
$A_N$ $B_N$
```

### Output

If there is an intersection between the chords, print `Yes`; otherwise, print `No`.

### Sample Input 1

```
3
1 3
4 2
5 6
```

### Sample Output 1

```
Yes
```

![](https://img.atcoder.jp/abc338/de1d9dd6cf38caec1c69fe035bdba545.png)

As shown in the figure, chord $1$ (the line segment connecting points $1$ and $3$) and chord $2$ (the line segment connecting points $4$ and $2$) intersect, so print `Yes`.

## 题解
这一题是我们的一个非常经典的题目，我们可以通过我们的一个栈来进行一个类似于括号匹配的处理。

我们首先破坏为链，然后我们就有：
![[Pasted image 20240128213148.png]]
![[Pasted image 20240401170841.png]]

之后，我们如果圆上有线段相交，那么就可以转换为我们的区间上有两个线段香蕉（且不存在覆盖关系）

接下来我们考虑怎么处理我们的上面的问题：
方法一：括号序列法：
我们如果按照每一个顶点的顺序把我们的每一个线段添加到我们的栈中，如果我们退栈的时候，我们匹配的端点不是我们的栈顶的端点，直接就有交点，退出即可。
```
#include<bits/stdc++.h>
using namespace std;

int n,a,b;
stack<int> st;
map<int,pair<int,int> > mp;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a>>b;
    	if(b<a) swap(a,b);
    	mp[a]={i,0},mp[b]={i,1};
	}
	for(int i=1;i<=2*n;i++){
		if(mp[i].second==0){
			st.push(mp[i].first);
		}
		else{
			if(st.top()!=mp[i].first){
				puts("Yes");
				return 0;
			}
			else{
				st.pop();
			}
		}
	}
	puts("No");
    return 0;
}
```

这里，我们可以通过一种较为简单的思路来处理，我们如果有相交，那么我们一定满足，在某一对线段中，有：$l_{a}\leq l_{b}\leq r_{a}$, $r_b>r_a$。

于是，我们就可以通过枚举我们的每一个点，然后判断：
1. 这个点是右端点吗？是的话，我们就拿这个所在的左端点，和我们当前左端点的最大值进行比较，
	1. 如果我们所在的这个就是我们的最大值，那么我们消去对应的左端点即可。
	2. 否则，我们认为有相交，我们直接输出答案即可。
```cpp
//#pragma GCC optimize(2)
//#pragma GCC optimize(3,"Ofast","inline")
//#include <bits\stdc++.h>
#include <iostream>
#include <bitset>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <cstdio>
#include <ctime>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <random>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define bs bitset
#define lg log10
#define re register
#define db double
#define ld long double
#define ll long long
#define lll __int128
#define ull unsigned long long
#define nth nth_element
#define lb lower_bound
#define ub upper_bound
#define _div stable_partition
#define _merge inplace_merge
#define point(x) setiosflags(ios::fixed)<<setprecision(x)
#define writen(x) write(x),printf("\n")
#define writet(x) write(x),printf(" ")
//const ull MOD = 212370440130137957ll;
const ll MOD = 1e9 + 7;
int test = 1;
//读入输出优化
namespace Fio {
    inline string sread() {
        string s=" ";char e=getchar();
        while(e==' '||e=='\n')e=getchar();
        while(e!=' '&&e!='\n')s+=e,e=getchar();
        return s;
    }
    inline void swrite(string s){
        for(char e:s)putchar(e);
        printf("\n");
    }
    inline ll read() {
        ll x=0,y=1;char c=getchar();
        while(!isdigit(c)){if(c=='-')y=-1;c=getchar();}
        while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
        return x*=y;
    }
    inline void write(ll x) {
        if(x<0)x=-x,putchar('-');ll sta[35],top=0;
        do sta[top++]=x%10,x/=10;while(x);
        while(top)putchar(sta[--top]+'0');
    }
}using namespace Fio;
const ll modd=1e9+7;
const ll inv2=499122177;
const ll inv6=166374059;
const db eps=0.0001;
//mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll> rd(1,1e18);
//inline ll rnd(){return rd(gen);}

inline ll qpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%modd;
        a=a*a%modd,b>>=1;
    }
    return res;
}
inline ll gcd(ll a,ll b){
    if(b==0)return a;
    return gcd(b,a%b);
}
inline ll lcm(ll a,ll b){
    return a/gcd(a,b)*b;
}
inline ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}


ll n,id[400005];
inline void qfl_zzz(){  
    n=read();
    for(ll i=1;i<=n;++i){
        ll u=read(),v=read();
        id[u]=v,id[v]=u;
    }
    set<ll> s;
    for(ll i=1;i<=2*n;++i){
        if(!s.count(id[i]))s.insert(i);
        else{
            s.erase(id[i]);
            auto p=s.ub(id[i]);
            if(p!=s.end()){
                printf("Yes\n");
                return;
            }
        }
    }
    printf("No\n");
} 
inline void pre_work(){

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    srand(time(NULL));
    //freopen("uuiu.txt","r",stdin);
    //test=read(); 
    //cin>>test;
    pre_work();
    for(ll i=1;i<=test;++i){
        //printf("Case #%lld: ",i);
        qfl_zzz();
    }
    //system("pause");
    return 0;
}   
```

