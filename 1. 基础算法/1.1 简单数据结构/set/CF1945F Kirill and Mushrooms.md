As soon as everyone in the camp fell asleep, Kirill sneaked out of the tent and went to the Wise Oak to gather mushrooms.

It is known that there are $n$ mushrooms growing under the Oak, each of which has magic power $v_i$. Kirill really wants to make a magical elixir of maximum strength from the mushrooms.

The strength of the elixir is equal to the product of the **number** of mushrooms in it and the **minimum** magic power among these mushrooms. To prepare the elixir, Kirill will sequentially pick one mushroom growing under the Oak. Kirill can gather mushrooms in any order.

However, it's not that simple. The Wise Oak informed Kirill of a permutation of numbers $p$ from $1$ to $n$. If Kirill picks only $k$ mushrooms, then the magic power of all mushrooms with indices $p_1, p_2, \dots, p_{k - 1}$ will become $0$. Kirill will not use mushrooms with zero magic power to prepare the elixir.

Your task is to help Kirill gather mushrooms in such a way that he can brew the elixir of maximum possible strength. However, Kirill is a little scared to stay near the oak for too long, so out of all the suitable options for gathering mushrooms, he asks you to find the one with the minimum number of mushrooms.

A permutation of length $n$ is an array consisting of $n$ different integers from $1$ to $n$ in any order. For example, $[2,3,1,5,4]$ is a permutation, but $[1,2,2]$ is not a permutation ($2$ appears in the array twice) and $[1,3,4]$ is also not a permutation ($n=3$, but $4$ appears in the array).

**Input**

Each test consists of multiple test cases. The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $n$ ($1 \le n \le 200\,000$) — the number of mushrooms.

The second line contains an array $v$ of size $n$ ($1\le v_i \le 10^9$) — the magic powers of the mushrooms.

The third line contains a permutation $p$ of numbers from $1$ to $n$.

It is guaranteed that the sum of the values of $n$ over all test cases does not exceed $2\cdot 10^5$.

**Output**

For each test case, output two integers separated by a space — the maximum strength of the elixir that can be brewed and the minimum number of mushrooms that Kirill needs to use for this.

## 题解
我们本题的想法是：我们从小到达枚举我们要选择 $K$ 个元素，我们的最优想法一定是选择我们的前 K 大元素，但是我们有删除要求，我们就需要先删除掉我们的 $K-1$ 个元素，再去求我们的全局第 $K$ 大元素是多少。

于是，我们就可以通过我们的一个 set 来动态维护出我们的全局第 $K$ 大。具体来说，我们用一个 $set$ 来维护我们可能的取值，如果我们删除的元素比我们的第 $K$ 大要小，我们就忽略，否则，我们就继续
```cpp
//选k个蘑菇
void solve(){
    int n;cin>>n;
    vector<int>a(n),p(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++){
        cin>>p[i];p[i]--;
    }

    priority_queue<pii>pq;
    for(int i=0;i<n;i++){
        pq.push({a[i],i});
    }

    ll ans=0;
    int asz=0;
    int mn=inf,sz=0;
    //维护使用过的位置,不能使用的位置
    vector<int>v1(n),v2(n);
    for(int i=0;i<n&&!pq.empty();i++){
        if(i!=0){
            v2[p[i-1]]=1;
            if(v1[p[i-1]]) sz--;
        }
        while(sz!=i+1){
            if(pq.empty()) break;
            auto [x,pos]=pq.top();
            pq.pop();
            if(v2[pos]) continue;
            v1[pos]=1;

            mn=min(x,mn);
            sz++;
        }
        if(sz==i+1){
            ll y=1ll*sz*mn;
            if(y>ans){
                ans=y,asz=sz;
            }
        }
    }
    cout<<ans<<' '<<asz<<'\n';
}
```