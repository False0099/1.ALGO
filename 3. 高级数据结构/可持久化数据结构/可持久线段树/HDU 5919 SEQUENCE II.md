Mr. Frog has an integer sequence of length n, which can be denoted as $a_1,a_2,\cdots ,a_n$ There are m queries.  
  
In the i-th query, you are given two integers $l_i$ and $r_i$. Consider the subsequence $a_{l_i},a_{l_{i+1}},a_{l_{i+2}},\cdots ,a_{r_i}$.  
  
We can denote the positions(the positions according to the original sequence) where an integer appears first in this subsequence as $p_{1}^{(i)},p_{2}^{(i)},\cdots, p_{k_i}^{(i)}$ (in ascending order, i.e.,$p_{1}^{(i)}<p_{2}^{(i)}<\cdots <p_{k_i}^{(i)}$).  
  
Note that $k_i$ is the number of different integers in this subsequence. You should output $p_{\left \lceil \frac{k_i}{2} \right \rceil}^{(i)}$for the i-th query.

Input

In the first line of input, there is an integer T ($T\leq 2$) denoting the number of test cases.  
  
Each test case starts with two integers n ($n \leq 2 \times 10^5$) and m ($m\leq 2\times 10^5$). There are n integers in the next line, which indicate the integers in the sequence(i.e., $a_1,a_2,\cdots ,a_n, 0\leq a_i \leq 2 \times 10^5$).  
  
There are two integers $l_i$ and $r_i$ in the following m lines.  
  
However, Mr. Frog thought that this problem was too young too simple so he became angry. He modified each query to $l_i^`,r_i^`(1\leq l_i^` \leq n,1\leq r_i^` \leq n )$. As a result, the problem became more exciting.  
  
We can denote the answers as $ans_1, ans_2,\cdots ,ans_m$. Note that for each test case $ans_0 = 0$.  
  
You can get the correct input $l_i,r_i$ from what you read (we denote them as $l_i^`,r_i^`$)by the following formula:  
$$ l_i = min\{ (l_i^`+ans_{i-1})\ mod \ n+1, (r_i^`+ans_{i-1})\ mod \ n+1 \} $$  
$$ r_i = max\{ (l_i^`+ans_{i-1})\ mod \ n+1, (r_i^`+ans_{i-1})\ mod \ n+1 \} $$

Output

You should output one single line for each test case.  
  
For each test case, output one line “Case x: $p_1,p_2,\cdots ,p_m$”, where x is the case number (starting from 1) and $p_1,p_2,\cdots ,p_m$ is the answer.

Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>5 2<br>3 3 1 5 4<br>2 2<br>4 4<br>5 2<br>2 5 2 1 2<br>2 3<br>2 4|Case #1: 3 3<br>Case #2: 3 1|

Hint

  
![](https://vj.csgrandeur.cn/bd7ab72dd09678ab6c1361f00cfd4d2c?v=1695338427)

## 题解
动态处理一个序列的区间问题，对于一个给定序列，每次输入区间的左端点和右端点，输出这个区间中：每个数字第一次出现的位子留下，输出这些位子中最中间的那个，就是（len+1）/2那个。

这里的思路是**从 n 到1开始建树。其他就是主席树查询区间第 K 小，计算区间不同值个数。**


```cpp
#include <algorithm>
#include  <iterator>
#include  <iostream>
#include   <cstring>
#include   <cstdlib>
#include   <iomanip>
#include    <bitset>
#include    <cctype>
#include    <cstdio>
#include    <string>
#include    <vector>
#include     <stack>
#include     <cmath>
#include     <queue>
#include      <list>
#include       <map>
#include       <set>
#include   <cassert>
#include <unordered_map>
using namespace std;
//#pragma GCC optimize(3)
//#pragma comment(linker, "/STACK:102400000,102400000")  //c++
// #pragma GCC diagnostic error "-std=c++11"
// #pragma comment(linker, "/stack:200000000")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define lson (l , mid , rt << 1)
#define rson (mid + 1 , r , rt << 1 | 1)
#define debug(x) cerr << #x << " = " << x << "\n";
#define pb push_back
#define pq priority_queue
#define max3(a,b,c) max(max(a,b),c)



typedef long long ll;
typedef unsigned long long ull;

typedef pair<ll ,ll > pll;
typedef pair<int ,int > pii;
typedef pair<int,pii> p3;

//priority_queue<int> q;//这是一个大根堆q
//priority_queue<int,vector<int>,greater<int> >q;//这是一个小根堆q
#define fi first
#define se second
//#define endl '\n'

#define OKC ios::sync_with_stdio(false);cin.tie(0)
#define FT(A,B,C) for(int A=B;A <= C;++A)  //用来压行
#define REP(i , j , k)  for(int i = j ; i <  k ; ++i)
//priority_queue<int ,vector<int>, greater<int> >que;

const ll mos = 0x7FFFFFFF;  //2147483647
const ll nmos = 0x80000000;  //-2147483648
const int inf = 0x3f3f3f3f;       
const ll inff = 0x3f3f3f3f3f3f3f3f; //18
const int mod = 256;
const double esp = 1e-8;
const double PI=acos(-1.0);

template<typename T>
inline T read(T&x){
    x=0;int f=0;char ch=getchar();
    while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x=f?-x:x;
}


/*-----------------------showtime----------------------*/   
            const int maxn = 2e5+9;
            struct node {
                int l,r;
                int sum;
            } t[maxn*40];
            int tot;
            int vis[maxn],rt[maxn],a[maxn];

            void update(int l,int r,int &x, int y,int pos,int val){
                tot++; x = tot;
                t[x] = t[y];
                t[x].sum += val;
                if(l == r)return;
                int mid = (l + r) >> 1;
                if(pos <= mid) update(l,mid,t[x].l,t[y].l,pos,val);
                else update(mid+1,r,t[x].r,t[y].r,pos,val);
            }

            int query(int l,int r,int x,int L, int R){
                if(l >= L && r<=R){
                    return t[x].sum;
                }
                int mid = (l + r) >> 1;
                int res = 0;
                if(mid >= L) res += query(l,mid,t[x].l,L,R);
                if(mid <  R) res += query(mid+1,r,t[x].r,L,R);
                return res;
            }

            int getk(int l,int r,int x,int k){
                if(l == r)return l;
                int cnt = t[t[x].l].sum;
                int mid = (l+r)>>1;
                if(cnt >= k) return getk(l,mid,t[x].l,k);
                else return getk(mid+1, r,t[x].r,k-cnt);
            }
int main(){
            int T,n,m;  scanf("%d", &T);
            for(int tt=1; tt<=T; tt++){
                tot = 0;
                scanf("%d%d", &n, &m);
                for(int i=1; i<=n; i++)scanf("%d", &a[i]);
                memset(vis, -1, sizeof(vis));
                memset(rt, 0, sizeof(rt));
                for(int i=n; i>=1; i--){
                    if(vis[a[i]] == -1){
                        update(1,n,rt[i],rt[i+1],i,1);
                    }
                    else{
                        int tmp;
                        update(1,n,tmp,rt[i+1], vis[a[i]], -1);
                        update(1,n,rt[i],tmp,i,1);
                    }
                    vis[a[i]] = i;
                }
                printf("Case #%d:", tt);
                int la = 0;
                for(int i=1; i<=m; i++){
                    int l,r,L,R;    scanf("%d%d", &L, &R);
                    l = min((L+la)%n + 1, (R+la)%n + 1);
                    r = max((L+la)%n + 1, (R+la)%n + 1);
                    int k = query(1,n,rt[l],l,r);
                    k = (k + 1) / 2;
                    la = getk(1,n,rt[l],k);
                    printf(" %d", la);
                }
                puts("");
            }
            return 0;
}

HDU - 5919
```