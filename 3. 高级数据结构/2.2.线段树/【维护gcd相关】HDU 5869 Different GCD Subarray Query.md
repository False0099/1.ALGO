# 
## 题目描述
给定n个数的序列，有q个询问，每次询问一个区间中所有子区间所形成不同的gcd的数量。

## 输入格式
There are several tests, process till the end of input.  
    
  For each test, the first line consists of two integers N and Q, denoting the length of the array and the number of queries, respectively. N positive integers are listed in the second line, followed by Q lines each containing two integers L,R for a query.  
  
You can assume that  
    
   1≤N,Q≤100000  
      
 1≤ai​≤1000000


## 输出格式
For each query, output the answer in one line.


## 样例 #1

### 样例输入 #1

```
5 3
1 3 4 6 9
3 5
2 5
1 5

```

### 样例输出 #1

```
6
6
6

```

## 提示




## 题解
由于固定一个数为右端点，所能形成的 gcd 共有 logn，所以可以预处理出每个数为右端点所能形成的 gcd，相同 gcd 取左端点靠右的。

然后将询问离线，按照r从小到

## 代码
```cpp
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#pragma comment(linker,"/STACK:102400000,102400000")
using namespace std;

#define N 100008
#define M 1000008
#define LL long long
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define clr(x,v) memset(x,v,sizeof(x));
#define bitcnt(x) __builtin_popcount(x)
#define rep(x,y,z) for (int x=y;x<=z;x++)
#define repd(x,y,z) for (int x=y;x>=z;x--)
const int mo  = 1000000007;
const int inf = 0x3f3f3f3f;
const int INF = 2000000000;
/**************************************************************************/
int n,m;
int a[N],pre[N],last[M],ans[N];
struct node{
    int x,id;
};
vector <node> q[N];
struct BIT{
    int a[N];
    void clear(){
        clr(a,0);
    }
    void add(int x,int val){
        for (int i=x;i<N;i+=i & (-i)) a[i]+=val;
    }
    int query(int x){
        int res=0;
        for (int i=x;i>0;i-=i & (-i)) res+=a[i];
        return res;
    }
    int sigma(int l,int r){
        return query(r)-query(l-1);
    }
}T;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main(){
    while (~scanf("%d%d",&n,&m)){
        rep(i,1,n) scanf("%d",&a[i]);
        rep(i,1,n) q[i].clear();
        rep(i,1,m){
            int l,r;
            scanf("%d%d",&l,&r);
            q[r].push_back((node){l,i});
        }
        repd(i,n,1)
            pre[i]= a[i]==a[i-1]? pre[i-1] : i-1;
        clr(last,0);
        T.clear();
        rep(i,1,n){
            for (int j=i,x=a[j];j>0;j=pre[j],x=gcd(x,a[j])){
                if (j>last[x]){
                    if (last[x]!=0) T.add(last[x],-1);
                    T.add(j,1);
                    last[x]=j;
                }
                If (x==1) break;
            }
            for (int j=0;j<q[i].size();j++){
                ans[q[i][j].id]=T.sigma(q[i][j].x,i);
            }
        }
        rep(i,1,m) printf("%d\n",ans[i]);
    }
}
```