# [USACO 05 JAN] Moo Volume S

## 题目描述

Farmer John 的农场上有 $N$ 头奶牛（$1 \leq N \leq 10^5$），第 $i$ 头奶牛的位置为 $x_i$（$0 \leq x_i \leq 10^9$）。

奶牛很健谈，每头奶牛都和其他 $N-1$ 头奶牛聊天。第 $i$ 头奶牛和第 $j$ 头奶牛聊天时，音量为 $|x_i-x_j|$。

请您求出所有奶牛聊天音量的总和。

## 输入格式

第一行一个整数 $N$。

接下来 $N$ 行，每行一个整数 $x_i$。

## 输出格式

输出总音量。

**保证答案在 64 位带符号整数的表示范围内。**

## 样例 #1

### 样例输入 #1

```
5
1
5
3
2
4
```

### 样例输出 #1

```
40
```

## 提示

- 子任务 1（原测试数据，1 分）：$N \leq 10^4$；
- 子任务 2（99 分）：无特殊限制。

## 题解
首先，我们的曼哈顿距离和与我们的**顺序无关**，所以我们就可以通过我们的**排序来去掉绝对值**。这个时候，对于我们的一个元素，我们最后就相当于求 $(i-1)\times x[i-1]+\sum x[i]$，

最后，我们就可以得到我们的下面的方法，我们按照我们的距离的大小，将我们的元素进行排序，我们排序后我们再带入我们的上面的式子即可。

```
#include <bits/stdc++.h>
#define int long long
int INF=0x3f3f3f3f3f;
using namespace std;
void solve(){
    int n;
    cin>>n;
    vector<int> x(n);
    for(int i=0;i<n;i++){
       cin>>x[i];
    }
    vector<int> sum(n);
    sort(x.begin(),x.end());
    sum[0]=x[0];
    for(int i=1;i<n;i++){
        sum[i]=sum[i-1]+x[i];
    }
    int res=0;
    int ress=0;
    for(int i=1;i<n;i++){
        res+=i*(x[i]-x[i-1]);
        ress+=res;
    }
    cout<<ress*2<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    //cin>>t;
    t=1;
    while(t--){
        solve();
    }
}
```