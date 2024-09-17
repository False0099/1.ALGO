This is a simple problem. The teacher gives Bob a list of problems about GCD (Greatest Common Divisor). After studying some of them, Bob thinks that GCD is so interesting. One day, he comes up with a new problem about GCD. Easy as it looks, Bob cannot figure it out himself. Now he turns to you for help, and here is the problem:  
    
Given an array a of N positive integers $a_1, a_2, \cdots a_{N-1}, a_N$; a subarray of a is defined as a continuous interval between $a_1$ and$a_N$. In other words, $a_i, a_{i+1}, \cdots, a_{j-1}$, $a_j$is a subarray of a, for $1\le i\le j\le N$. For a query in the form (L, R), tell the number of different GCDs contributed by all subarrays of the interval$[L, R]$.  
  

## Input

There are several tests, process till the end of input.  
    
For each test, the first line consists of two integers N and Q, denoting the length of the array and the number of queries, respectively. N positive integers are listed in the second line, followed by Q lines each containing two integers L,R for a query.  
  
You can assume that  
    
$1\le N,Q\le100000$  
      
$1\le a_i\le1000000$

## Output

For each query, output the answer in one line.

## Sample

|Inputcopy|Outputcopy|
|---|---|
|5 3<br>1 3 4 6 9<br>3 5<br>2 5<br>1 5|6<br>6<br>6|


## 题解
题意：给定一个数组，问所有字数组构成的不同 gcd 总种类是多少。

我们这一题采用离线算法，是因为如果**固定了我们的右端点，我们的查询会变得非常简单**，我们这么做能够确确实实的缩短我们的哈密顿距离。方便我们用“暴力”的算法进行。

固定右端点后，我们先用一个树状数组，来维护我们从 0-x 位置，我们**一共有的 gcd 数种类**。之后，我们对于怎么求出我们的 gcd 数种类，我们只需要用一个 map1 用来存储我们**包含 x 的后缀的所有可能的不重复的 gcd 值**，和每个值出现的**最左端**，并且把我们对应的数目给记录下来，我们用一个 map2 来存储我们 0-x 之间**所有可能的 gcd 值**，和每个 gcd 值出现的最左端。

然后对于每一个查询，只需要每一个右端点就进行一次查询，这样才能保证我们的正确性。**不然等到后面，有其他数据更新了我们的当前数，就不能了**。类似于我们的 dp 转移，如果**全部整完再去转移，我们就没得玩了。**

我们考虑把询问预存下来，按右边界排序，然后遍历右边界，过程中求出**每个左边界到当前右边界的 gcd 种数**，这样当前右边界的询问中每个左边界可以求出一个答案出来。gcd 种数可以用树状数组存。

那么存下每种 gcd 在当前右边界下，最近的左边界即可。这里就是我们用到 map 的地方，存储每种 gcd 的最大的左边界。


```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <ctime>
#include <cstring>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#define LL long long
#define Pr pair<int,int>
#define fread(ch) freopen(ch,"r",stdin)
#define fwrite(ch) freopen(ch,"w",stdout)

using namespace std;
const int INF = 0x3f3f3f3f;
const int msz = 112345;
const int mod = 1e9+7;
const double eps = 1e-8;

int a[msz],n;
int bit[msz];//树状数组，存储我们0到某个位置，一共有的gcd的数目
map <int,int> mp2;//表示我们某个gcd值对应的最左边是拿个
map <int,int> mp1;//表示我们某个gcd是否在我们的整个区间内出现过
map <int,int> tmp;//暂存

struct Query
{
    int l,r,id;
    bool operator <(const struct Query a)const
    {
        return r < a.r;
    }
};
//把我们的询问按照右端点排序

Query que[msz];
int ans[msz];

int Lowbit(int x)
{
    return x&(-x);
}

void Add(int x,int ad)
{
    while(x <= n)
    {
        bit[x] += ad;
        x += Lowbit(x);
    }
}

int Sum(int x)
{
    int ans = 0;
    while(x)
    {
        ans += bit[x];
        x -= Lowbit(x);
    }
    return ans;
}

int main()
{
    //fread("in.in");
    //fwrite("");
    int q;
    while(~scanf("%d%d",&n,&q))
    {
        memset(bit,0,sizeof(bit));
        for(int i = 1; i <= n; ++i) scanf("%d",&a[i]);
        for(int i = 0; i < q; ++i)
        {
            scanf("%d%d",&que[i].l,&que[i].r);
            que[i].id = i;
        }
        sort(que,que+q);
        int pos = 0;
        int g;
        mp1.clear();
        mp2.clear();
        for(int i = 1; i <= n; ++i)
        {
            tmp.clear();//存储我们到这个位置位置所有gcd的位置
            for(auto iter: mp2)
            {
                g = __gcd(iter.first,a[i]);//求gcd，要求必须以a[i]结尾
                if(!tmp.count(g) || tmp[g] < iter.second)
                    tmp[g] = iter.second;//更新我们这个数出现的最左边的位置
	        }
            tmp[a[i]] = i;//这个数自己作为一个添加上去
            mp2.clear();
            for(auto iter: tmp)
            {
                if(!mp1.count(iter.first))
                {
                    mp1[iter.first] = iter.second;
                    Add(iter.second,1);//我们的对应左边界位置+1
                }
                else if(mp1[iter.first] < iter.second)
                {
                    Add(mp1[iter.first],-1);//我们对应的有边界的位置
                    mp1[iter.first] = iter.second;
                    Add(iter.second,1);//我们的对应左边界位置+1
                }
                mp2[iter.first] = iter.second;
            }
            //按照我们的排序查询
            while(pos < q && que[pos].r == i)
            {
                ans[que[pos].id] = Sum(que[pos].r)-Sum(que[pos].l-1);
                pos++;
            }
        }
        for(int i = 0; i < q; ++i)
            printf("%d\n",ans[i]);
	    }

    return 0;
}
```