给定一个长度为 $n$ 的数组 $a=[a_1,a_2,\cdots ,a_n]$。  
  
对数组进行多次查询，每次查询数组的一个连续区间 $[l,r]$，需要计算集合 $S=\bigcup_{i=l}^{r}{\left\{\text{gcd}_{j=i}^r{a_j}\right\}}$ 的大小。  
  
注意：$\text{gcd}_{i=p}^{q}{a_i}$ 表示数组 $a$ 中 $a_p,a_{p+1},\cdots ,a_{q}$ 的最大公因数，$\bigcup_{i=p}^{q}{s_i}$ 表示集合 $s_p,s_{p+1},\cdots s_{q}$ 的并集。

## 输入
第一行两个整数 $n,m\ (1\leq n,m\leq 6\times 10^5)$ 表示序列大小和询问次数。  
  
第二行 $n$ 个整数表示 $a_i\ (1\leq a_i\leq 2^{31})$。  
  
接下来 $m$ 行，每行两个正整数 $l,r\ (1\leq l\leq r\leq n)$ 表示询问。

## 输出
共 $m$ 行，每行一个正整数表示答案。

## 题解
我们这一题需要利用到 gcd 的这么一个性质：对于两个数，如果我们有 $gcd(a,b)<a$,那么我们一定有 $gcd(a,b)\leq \dfrac{a}{2}$,这一点其实我们不难理解。

那么我们就可以知道，一段区间内的后缀 gcd 种类数量应该是很少的，小于我们的 $\log(n)$ 的，所以我们就可以通过我们的暴力维护每一个前缀的 gcd 种类。

那么我们就可以**枚举我们以某个数为右端点时，我们前端点改变的位置**是哪些？这里我们用一个数组来存储（）
```cpp
vector<int> pos(n);
```

然后，我们需要做的，就是怎么快速的求出我们的 $pos$ 数组，我们发现，我们从 $pos(n)\to pos(n+1)$ 这一个过程中，我们是具有传承性质的，也就是说，我们的 $pos(n+1)$ 中只可能包含两种元素：第一种是这个位置本身，第二种就是前面 $pos(n)$ 中出现过的元素。

于是，我们就可以暴力的进行我们的 $gcd$ 计算，然后来预处理我们的 $pos(n)$,这里，我们需要一个辅助数组 $gcd(n)$ 来存储我们对应位置所能获得的 gcd 具体是多少。或者，我们可以直接用一个 PII 来存储，而不新开一个数组

```cpp
vector<PII> g[N];
 
void solve()
{
    cin>>n>>m;
    vector<int> a(n+5);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
     
    unordered_map<int,int> mp;
     
    for(int i=1;i<=n;i++){
        g[i].push_back({a[i],i});
        mp[a[i]]=i;
        for(auto&[x,id]:g[i-1]){
            int v=__gcd(x,a[i]);
            if(!mp.count(v) || mp[v]!=i){// 在前面或者是没有出现过是新的
                mp[v]=i;// 向后走
                g[i].push_back({v,id});
            }
        }
    }
     
    while(m--){
        int l,r; cin>>l>>r;
        int cnt=0;
        for(auto&[x,id]:g[r]){
            if(id>=l) cnt++;
        }
        cout<<cnt<<endl;
    }
    return ;
}
```