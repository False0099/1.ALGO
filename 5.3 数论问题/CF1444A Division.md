# Division

## 题面翻译

给定 $t$ 组询问，每组给两个数 $p_i$ 和 $q_i$，找出最大的整数 $x_i$，要求 $p_i$ 可被 $x_i$ 整除，且 $x_i$ 不可被 $q_i$ 整除。

## 题目描述

Oleg's favorite subjects are History and Math, and his favorite branch of mathematics is division.

To improve his division skills, Oleg came up with $ t $ pairs of integers $ p_i $ and $ q_i $ and for each pair decided to find the greatest integer $ x_i $ , such that:

- $ p_i $ is divisible by $ x_i $ ;
- $ x_i $ is not divisible by $ q_i $ .

 Oleg is really good at division and managed to find all the answers quickly, how about you?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 50 $ ) — the number of pairs.

Each of the following $ t $ lines contains two integers $ p_i $ and $ q_i $ ( $ 1 \le p_i \le 10^{18} $ ; $ 2 \le q_i \le 10^{9} $ ) — the $ i $ -th pair of integers.

## 输出格式

Print $ t $ integers: the $ i $ -th integer is the largest $ x_i $ such that $ p_i $ is divisible by $ x_i $ , but $ x_i $ is not divisible by $ q_i $ .

One can show that there is always at least one value of $ x_i $ satisfying the divisibility conditions for the given constraints.

## 样例 #1

### 样例输入 #1

```
3
10 4
12 6
179 822
```

### 样例输出 #1

```
10
4
179
```

## 提示

For the first pair, where $ p_1 = 10 $ and $ q_1 = 4 $ , the answer is $ x_1 = 10 $ , since it is the greatest divisor of $ 10 $ and $ 10 $ is not divisible by $ 4 $ .

For the second pair, where $ p_2 = 12 $ and $ q_2 = 6 $ , note that

- $ 12 $ is not a valid $ x_2 $ , since $ 12 $ is divisible by $ q_2 = 6 $ ;
- $ 6 $ is not valid $ x_2 $ as well: $ 6 $ is also divisible by $ q_2 = 6 $ .

 The next available divisor of $ p_2 = 12 $ is $ 4 $ , which is the answer, since $ 4 $ is not divisible by $ 6 $ .
## 题解
本题通过观察样例，显然有如果我们的 $a\text{ mod  b}\neq 0$,那么我们一定可以构造我们的最后答案为 $a$。

否则，我们一定有 $a=k*b$,我们假设我们的 $b$ 的分解为 $P_{1}^{t_{1}}\dots P_{n}^{t_{n}}$。于是，我们就可以通过让我们的 a 中的某一个因子变成我们的 $P_{1}^{t_{1}-1}$，然后其他的不变，从而来最大的我们的答案，我们最后的结果就是其中的最大值。
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
    int p,q;
    cin>>p>>q;
    if(p%q!=0){
        cout<<p<<endl;
    }else{
        int ans=0;
        for(int i=2;i*i<=q;i++){
            int fg=1;
            int times=0;
            if(q%i){
                continue;
            }
            while(q%i==0){
                q/=i;
                fg*=i;
                times++;
            }
            fg/=i;
            if(times>=1){
                int ttmp=p;
                while(ttmp%i==0){
                    ttmp/=i;
                }
                ans=max(ans,ttmp*fg);
            }
        }
        if(q>1){
            while(p%q==0){
                p/=q;
            }
            ans=max(ans,p);
        }
        cout<<ans<<endl;
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