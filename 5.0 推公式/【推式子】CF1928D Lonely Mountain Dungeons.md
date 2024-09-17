# Lonely Mountain Dungeons

## 题目描述

Once, the people, elves, dwarves, and other inhabitants of Middle-earth gathered to reclaim the treasures stolen from them by Smaug. In the name of this great goal, they rallied around the powerful elf Timothy and began to plan the overthrow of the ruler of the Lonely Mountain.

The army of Middle-earth inhabitants will consist of several squads. It is known that each pair of creatures of the same race, which are in different squads, adds $ b $ units to the total strength of the army. But since it will be difficult for Timothy to lead an army consisting of a large number of squads, the total strength of an army consisting of $ k $ squads is reduced by $ (k - 1) \cdot x $ units. Note that the army always consists of at least one squad.

It is known that there are $ n $ races in Middle-earth, and the number of creatures of the $ i $ -th race is equal to $ c_i $ . Help the inhabitants of Middle-earth determine the maximum strength of the army they can assemble.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ b $ , and $ x $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le b \le 10^6, 0 \le x \le 10^9 $ ) — the number of races and the constants $ b $ and $ x $ described above.

The second line of each test case contains $ n $ integers $ c_1, c_2, \ldots, c_n $ ( $ 1 \le c_i \le 2 \cdot 10^5 $ ) — the number of creatures of each of the $ n $ races.

It is guaranteed that the sum of the values $ c_1 + c_2 + \ldots + c_n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum strength of the army that the inhabitants of Middle-earth can assemble.

## 样例 #1

### 样例输入 #1

```
5
3 1 0
1 2 3
3 5 10
2 5 3
4 3 3
3 2 1 2
4 1 0
4 1 4 2
4 1 10
4 1 4 2
```

### 样例输出 #1

```
4
40
9
13
0
```

## 提示

In the first test case, the inhabitants of Middle-earth can form $ 3 $ squads. Since $ x = 0 $ , the army's strength will not decrease due to the number of squads. The inhabitants can be distributed among the squads as follows:

- The single representative of the first species can be sent to the first squad.
- The first representative of the second species can be sent to the first squad, the second representative of the second species can be sent to the second squad. Then the total strength of the army will increase by $ b = 1 $ .
- The first representative of the third species can be sent to the first squad, the second representative of the third species can be sent to the second squad, the third representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 3 \cdot b = 3 $ , as they form three pairs in different squads.

Thus, the total strength of the army is $ 4 $ .

In the second test case, the inhabitants of Middle-earth can form $ 3 $ squads. Since $ x = 10 $ , the army's strength will decrease by $ 20 $ . The inhabitants can be distributed among the squads as follows:

- The first representative of the first species can be sent to the first squad, the second representative of the first species can be sent to the second squad. Then the total strength of the army will increase by $ b = 5 $ .
- The first and second representatives of the second species can be sent to the first squad, the third and fourth representatives of the second species can be sent to the second squad, the fifth representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 8 \cdot b = 40 $ .
- The first representative of the third species can be sent to the first squad, the second representative of the third species can be sent to the second squad, the third representative of the third species can be sent to the third squad. Then the total strength of the army will increase by $ 3 \cdot b = 15 $ , as they form three pairs in different squads.

Thus, the total strength of the army is $ 5 + 40 + 15 - 20 = 40 $ .

## 题解
我们本题最为暴力的方法，就是枚举我们分成多少个组，然后再去计算我们每种生物对于我们的答案的贡献。

我们不难发现，如果我们坚持这样做的话，我们一定会超时，于是我们考虑优化。注意到：$$\text{lt is guaranteed that the sum of the values }c_1+c_2+\ldots+c_n\text{over all test cases does not exceed }2\cdot10^5.$$

又因为我们数量相同的物种对于我们的答案的贡献是相同的，于是我们就可以通过我们的去重来快速计算我们的答案是多少。

然后我们的关键就变成了，我们对于 m 个人，分成 k 组的贡献是多少。

这里我们考虑进行推式子：

我们假设我们把我们的 m 个人正好分成 $k$ 组，我们平均每一组分到了 $j$ 个人，然后我们剩余下 $j_{2}$ 个人没有分到。

对于已经分成整数组的，我们的答案就是我们的：$(1+2+\dots+(k-1))*j*b*j$
我们可以通过我们的画图或者我们的其他方式来进行证明。

然后我们对于我们的剩余组，他们对于我们的答案的共线，我们可以通过反向计算来得到：

$(c*(y-1))j_{2}*b+\frac{d(d-1)}{2}*b$

之后，我们就能得到我们的最终答案。

```cpp
#include <bits/stdc++.h>

using  namespace std;

int n,b,x;

#define int long long

long long calc(long long m,long long d) {

    long long ans=d*(d-1)/2;

    ans*=(m/d)*(m/d);

    ans+=(d-1)*(m/d)*(m%d);

    m%=d;

    ans+=m*(m-1)/2;

    return ans;

}

void solve(){

    cin>>n>>b>>x;

    map<int,int> cnt;

    vector<int> a(n);

    for(int i=0;i<n;i++){

        cin>>a[i];

        cnt[a[i]]++;

    }

    sort(a.begin(),a.end());

    auto it=unique(a.begin(),a.end());

    a.erase(it,a.end());

    //puts("");

    int m=a.size()-1;

    long long ans=0;

    for(int i=1;i<=a[m];i++){

        long long res=-(i-1)*x;

        for(int j=0;j<a.size();j++){

            res+=calc(a[j],min(a[j],i))*cnt[a[j]]*b;

        }

        ans=max(ans,res);

    }

    cout<<ans<<endl;

  
  

}

signed main(){

    int t;

    cin>>t;

    while(t--){

        solve();

    }

}
```