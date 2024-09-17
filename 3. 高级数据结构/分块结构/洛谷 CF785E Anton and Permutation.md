# Anton and Permutation

## 题面翻译

有一个长度为 $n$ 的排列，初始为 $1,2,\dots,n$。

现在对其进行 $k$ 次操作，每次操作都是交换序列中的某两个数。对于每一个操作，回答当前序列中有多少个逆序对。

## 题目描述

Anton likes permutations, especially he likes to permute their elements. Note that a permutation of $ n $ elements is a sequence of numbers $ {a_{1}, a_{2},..., a_{n}} $ , in which every number from $ 1 $ to $ n $ appears exactly once.

One day Anton got a new permutation and started to play with it. He does the following operation $ q $ times: he takes two elements of the permutation and swaps these elements. After each operation he asks his friend Vanya, how many inversions there are in the new permutation. The number of inversions in a permutation is the number of distinct pairs $ (i, j) $ such that $ 1<=i<j<=n $ and $ a_{i}>a_{j} $ .

Vanya is tired of answering Anton's silly questions. So he asked you to write a program that would answer these questions instead of him.

Initially Anton's permutation was $ {1,2,..., n} $ , that is $ a_{i}=i $ for all $ i $ such that $ 1<=i<=n $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ $ (1<=n<=200000,1<=q<=50000) $ — the length of the permutation and the number of operations that Anton does.

Each of the following $ q $ lines of the input contains two integers $ l_{i} $ and $ r_{i} $ $ (1<=l_{i}, r_{i}<=n) $ — the indices of elements that Anton swaps during the $ i $ -th operation. Note that indices of elements that Anton swaps during the $ i $ -th operation can coincide. Elements in the permutation are numbered starting with one.

## 输出格式

Output $ q $ lines. The $ i $ -th line of the output is the number of inversions in the Anton's permutation after the $ i $ -th operation.

## 样例 #1

### 样例输入 #1

```
5 4
4 5
2 4
2 5
2 2
```

### 样例输出 #1

```
1
4
3
3
```

## 样例 #2

### 样例输入 #2

```
2 1
2 1
```

### 样例输出 #2

```
1
```

## 样例 #3

### 样例输入 #3

```
6 7
1 4
3 5
2 3
3 3
3 6
2 1
5 1
```

### 样例输出 #3

```
5
6
7
7
10
11
8
```

## 提示

Consider the first sample.

After the first Anton's operation the permutation will be $ {1,2,3,5,4} $ . There is only one inversion in it: $ (4,5) $ .

After the second Anton's operation the permutation will be $ {1,5,3,2,4} $ . There are four inversions: $ (2,3) $ , $ (2,4) $ , $ (2,5) $ and $ (3,4) $ .

After the third Anton's operation the permutation will be $ {1,4,3,2,5} $ . There are three inversions: $ (2,3) $ , $ (2,4) $ and $ (3,4) $ .

After the fourth Anton's operation the permutation doesn't change, so there are still three inversions.

## 题解
本题我们理上可以使用树套树的方法去解决我们的问题。但我们这里采用我们的分块算法。
对于每一次交换 $(l,r)$，位置对应的值为 $(x,y)$, 我们这一次交换对于 $(l+1 \to r-1)$ 范围内，值域在 $(x,y)$ 的所有数字，造成 1 点影响。等价于**询问一个范围区间内，某个值域区间内的所有数的个数**。

我们如果按照分块的思路，把区间划分为若干**整块和散块**。对于一个**整块**，我们先把他们排列成有序的，然后再用我们的库函数*upper_bound*,**lowerbound**, 来求出我们在这一段内，**在某个值域区间内的所有数的个数**。答案即为：$upper(x)-lower(y)$
对于我们的散块，我们就暴力的寻找即可。

```cpp
#include<bits/stdc++.h>
#define maxn 200010
#define lower(a,x) lower_bound(ve[a].begin(),ve[a].end(),x)
#define upper(a,x) upper_bound(ve[a].begin(),ve[a].end(),x)
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,k,S;
int bel[maxn],a[maxn];
ll ans;
vector<int> ve[maxn];
void change(int l,int r)
{
    if(bel[l]!=bel[r])
    {
        ve[bel[l]].erase(lower(bel[l],a[l])),ve[bel[l]].insert(upper(bel[l],a[r]),a[r]);
        ve[bel[r]].erase(lower(bel[r],a[r])),ve[bel[r]].insert(upper(bel[r],a[l]),a[l]);
    }
    swap(a[l],a[r]);
}
int query(int l,int r,int v)
{
    if(l>r) return 0;
    int cnt=0;
    for(int i=l;i<=min(S*bel[l],r);++i) cnt+=(a[i]<v);
    if(bel[l]==bel[r]) return cnt;
    for(int i=S*(bel[r]-1)+1;i<=r;++i) cnt+=(a[i]<v);
    for(int i=bel[l]+1;i<=bel[r]-1;++i) cnt+=lower(i,v)-ve[i].begin();
    return cnt;
}
int main()
{
    read(n),read(k),S=sqrt(n);
    for(int i=1;i<=n;++i) a[i]=i,bel[i]=(i-1)/S+1,ve[bel[i]].push_back(a[i]);
    while(k--)
    {
        int l,r;
        read(l),read(r);
        if(l>r) swap(l,r);
        if(l==r)
        {
            printf("%lld\n",ans);
            continue;
        }
        ans+=2*(query(l+1,r-1,a[r])-query(l+1,r-1,a[l]));
        if(a[l]<a[r]) ans++;
        else ans--;
        change(l,r),printf("%lld\n",ans);
    }
    return 0;
}
```