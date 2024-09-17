还记得汉诺塔 III 吗？他的规则是这样的：不允许直接从最左(右)边移到最右(左)边(每次移动一定是移到中间杆或从中间移出)，也不允许大盘放到小盘的上面。xhd 在想如果我们允许最大的盘子放到最上面会怎么样呢？（只允许最大的放在最上面）当然最后需要的结果是盘子从小到大排在最右边。

### Input

输入数据的第一行是一个数据T，表示有T组数据。  
每组数据有一个正整数n(1 <= n <= 20)，表示有n个盘子。  

### Output

对于每组输入数据，最少需要的摆放次数。

### Sample

| Inputcopy    | Outputcopy |
| ------------ | ---------- |
| 2<br>1<br>10 | 2<br>19684 |
## 题解
我们对于递推类问题，我们的最好的解决方法，就是 **找到一个合法的步骤**。我们对于本体，我们可以找到下面的步骤：
1. 将我们的 n-1 层都放到我们的 C 号
2. 将我们的第 N 层直接移动到 C（n-1）

于是我们就有我们的下面的代码：
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

const int N=65;

int f[N];

int g[N];

using namespace std;

void init(){

    f[1]=2;

    g[1]=2;

    for(int i=2;i<=64;i++){

        f[i]=3*f[i-1]+2;

    }

    for(int i=2;i<=64;i++){

        g[i]=f[i-1]+2;

    }

}

void solve(){

    int n;

    cin>>n;

    cout<<g[n]<<endl;

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    cin>>t;

    init();

    while(t--){

        solve();

    }

}
```