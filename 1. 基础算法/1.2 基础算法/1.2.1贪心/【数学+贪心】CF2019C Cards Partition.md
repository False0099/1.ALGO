[DJ Genki vs Gram - Einherjar Joker](https://soundcloud.com/leon-hwang-368077289/einherjar-joker-dj-genki-vs-gram)

You have some cards. An integer between $1$ and $n$ is written on each card: specifically, for each $i$ from $1$ to $n$, you have $a_i$ cards which have the number $i$ written on them.

There is also a shop which contains unlimited cards of each type. You have $k$ coins, so you can buy **at most** $k$ new cards in total, and the cards you buy can contain any integer **between $\mathbf{1}$ and $\mathbf{n}$**, inclusive.

After buying the new cards, you must partition **all** your cards into decks, according to the following rules:

-   all the decks must have the same size;
-   there are no pairs of cards with the same value in the same deck.

Find the maximum possible size of a deck after buying cards and partitioning them optimally.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains two integers $n$, $k$ ($1 \leq n \leq 2 \cdot 10^5$, $0 \leq k \leq 10^{16}$) — the number of distinct types of cards and the number of coins.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($0 \leq a_i \leq 10^{10}$, $\sum a_i \geq 1$) — the number of cards of type $i$ you have at the beginning, for each $1 \leq i \leq n$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.


**Output**

For each test case, output a single integer: the maximum possible size of a deck if you operate optimally.

## 题解
本题我们考虑通过**枚举的方法**来进行我们的对应的处理，我们发现，我们的答案是可以进行枚举的，我们可以通过枚举我们的答案，并且从大到小的枚举我们的答案。

我们考虑怎么去进行我们的**check**，考虑我们如果想要最大堆的总数为 $x$,并且我们满足我们的所有的总数在我们的 $[s,s+k]$ 之间，并且能够**整除我们的 x**，那么我们一定是**分的堆数越多越好**。这个时候，我们考虑我们最大能分成多少堆，这个显然可以通过我们的下面的公式计算得到：
$$
x-x\text{ mod }mid
$$

之后，我们就可以知道我们分成了多少堆，然后我们再去检查我们的最多的那个元素有没有满足正好为 $k$ 堆，如果有，就成立，反之不成立。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
void solve(){
    int n,k;
    cin>>n>>k;
    vector<int> a(n+1);
    int sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    int l=*(max_element(begin(a),end(a))),r=sum;
    //枚举答案，从大到小处理
    int ll=1,rr=n;
    auto check=[&](int mid){
        int s=(sum+k)/mid;
        if(s<=l-1){
            return false;
        }
        if(s*mid<=r-1){
            return false;
        }
        return true;
    };
//     while(ll<rr){
//         int mid=ll+rr>>1;
//         if(check(mid)){
//             ll=mid+1;
//         }else{
//             rr=mid;
//         }
//     }
// //    cerr<<rr<<endl;
//     int ans=1;
//     for(int dx=0;dx<=1;dx++){
//         if(ll+dx>0&&check(ll+dx)){
//             ans=max(ans,ll+dx);
//         }
//         if(ll-dx>0&&check(ll-dx)){
//             ans=max(ans,ll-dx);
//         }
//     }
//     cout<<ans<<endl;
    for(int i=n;i>=1;i--){
        //检查我们能分成多少堆
        int s=(sum+k)/i;
        if(s*i<=sum-1){
            continue;
        }
        if(s<=l-1){
            continue;
        }
        cout<<i<<endl;
        return;
    }
   
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```