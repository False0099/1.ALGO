Monocarp is playing a computer game (yet again). Guess what is he doing? That's right, killing monsters.

There are $n$ monsters in a row, numbered from $1$ to $n$. The $i$ \-th monster has two parameters: attack value equal to $a_i$ and defense value equal to $d_i$. In order to kill these monsters, Monocarp put a berserk spell on them, so they're attacking each other instead of Monocarp's character.

The fight consists of $n$ rounds. Every round, the following happens:

-   first, every alive monster $i$ deals $a_i$ damage to the **closest** alive monster to the left (if it exists) and the **closest** alive monster to the right (if it exists);
-   then, every alive monster $j$ which received more than $d_j$ damage **during this round** dies. I. e. the $j$ \-th monster dies if and only if its defense value $d_j$ is **strictly less** than the total damage it received **this round**.         

For each round, calculate the number of monsters that will die during that round.        
## 输入
**Input**

The first line contains one integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

Each test case consists of three lines:

-   the first line contains one integer $n$ ($1 \le n \le 3 \cdot 10^5$);
-   the second line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 10^9$);
-   the third line contains $n$ integers $d_1, d_2, \dots, d_n$ ($1 \le d_i \le 10^9$).

Additional constraint on the input: the sum of $n$ over all test cases does not exceed $3 \cdot 10^5$.

## 输出
**Output**

For each test case, print $n$ integers. The $i$ \-th integer should be equal to the number of monsters that die during the $i$ \-th round.

## 题解
这一题，我们只需要模拟这一整个过程，就可以满足我们的需求，因为我们如果一次过程，我们的消耗是 0，那么我们之后的消耗也一定是 0，只有当我们的消耗不为 0 的时候，我们的更新才会进行，于是我们的最坏情况，也只会进行我们的 $o (n)$ 次操作。
而我们在模拟的过程中，遇到的最大的问题，就是要快速的求出在多次操作后，我们一个位置的前驱和后继是什么。这个我们显然可以通过我们的双向链表来解决。于是我们就可借助我们的双向链表来模拟我们的过程。
```cpp
ll n,a[300005],d[300005],l[300005],r[300005],w[300005];
set<pair<ll,ll>> s;
inline void upd(ll i){
    w[i]=d[i];
    if(l[i]!=0)w[i]-=a[l[i]];
    if(r[i]!=n+1)w[i]-=a[r[i]];
    s.insert({w[i],i});
}
inline void qfl_zzz(){
    cin>>n;
    for(ll i=1;i<=n;++i)cin>>a[i];
    for(ll i=1;i<=n;++i)cin>>d[i];
    for(ll i=1;i<=n;++i){
        l[i]=i-1;
        r[i]=i+1;
        upd(i);//初始化我们的双向链表
    }
    ll m=n,cnt=1e9;
    while(m--){
        if(cnt==0){
            writet(0);
            continue;
        }
        set<ll> id;//存放我们当前轮被杀掉的id
        while(s.size()&&(*s.begin()).first<0){
            ll x=(*s.begin()).second;
            s.erase({w[x],x});
            id.insert(x);
        }
        for(ll i:id){
            if(l[i]!=0){//链表的删除
                ll j=l[i];
                s.erase({w[j],j});
                r[j]=r[i];
                if(!id.count(j))upd(j);
            }
            if(r[i]!=n+1){
                ll j=r[i];
                s.erase({w[j],j});
                l[j]=l[i];
                if(!id.count(j))upd(j);
            }
        }
        writet(cnt=(ll)id.size());
    }
    printf("\n");
    for(ll i=0;i<=n+1;++i)a[i]=d[i]=l[i]=r[i]=w[i]=0;
    s.clear();
} 作者：qfl_zzz 
```