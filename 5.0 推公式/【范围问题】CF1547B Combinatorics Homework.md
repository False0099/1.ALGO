# Combinatorics Homework

## 题面翻译

给定整数 $a,b,c,m$。  
求是否存在一个字符串 $s$ 满足：

- $s$ 中正好有 $a$ 个字符 `A`，$b$ 个字符 `B`，$c$ 个字符 `C`，且不包含其他字符。
- **正好**存在 $m$ 个互不相同的整数 $i$ 使得 $1\leq i<n$ 且 $s_i=s_{i+1}$。

存在输出 `YES`，不存在输出 `NO`。$T$ 组数据。

保证：  
$1\leq T\leq 10^4;$  
$1\leq a,b,c\leq10^8;0\leq m\leq10^8;$

## 题目描述

You are given four integer values $ a $ , $ b $ , $ c $ and $ m $ .

Check if there exists a string that contains:

- $ a $ letters 'A';
- $ b $ letters 'B';
- $ c $ letters 'C';
- No other letters;
- Exactly $ m $ pairs of adjacent equal letters (exactly $ m $ such positions $ i $ that the $ i $ -th letter is equal to the $ (i+1) $ -th one).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

Each of the next $ t $ lines contains the description of the testcase — four integers $ a $ , $ b $ , $ c $ and $ m $ ( $ 1 \le a, b, c \le 10^8 $ ; $ 0 \le m \le 10^8 $ ).

## 输出格式

For each testcase print "YES" if there exists a string that satisfies all the requirements. Print "NO" if there are no such strings.

You may print every letter in any case you want (so, for example, the strings yEs, yes, Yes and YES will all be recognized as positive answer).

## 样例 #1

### 样例输入 #1

```
3
2 2 1 0
1 1 1 1
1 2 3 2
```

### 样例输出 #1

```
YES
NO
YES
```

## 提示

In the first testcase strings "ABCAB" or "BCABA" satisfy the requirements. There exist other possible strings.

In the second testcase there's no way to put adjacent equal letters if there's no letter that appears at least twice.

In the third testcase string "CABBCC" satisfies the requirements. There exist other possible strings.

## 题解
我们考虑到我们的下面的这一个问题中，我们要**判断我们的方案是否合法**，而对于我们的判断，我们利用到了我们的一个性质：**我们的取值范围在我们的上界和下界之间是连续的**。

也就是说，只要我们的取值范围在我们的上界和下界之间，我们**一定存在一种构造方法可以构造出来**。

于是，我们考虑怎么找到本题的上下界。我们本题的上界显然是易得的，就是把我们的**每一个元素都连续防止**，最后得到的答案就是我们的上界。

而对于我们的下界，我们的答案就是：我们采用类似于 $abacad$ 的方法，也就是用我们的最大值，减去我们的后续的所有元素的值。

最后，我们只需要判断我们的数字是否在我们的这一个上下界范围当中，如果在的话，我们就直接输出 yes，否则我们就输出我们的 no。
```
#include <bits/stdc++.h>

#define int long long

int INF=0x3f3f3f3f3f;

using namespace std;

void solve(){

    int a,b,c,m;

    cin>>a>>b>>c>>m;

    if(a<b){

        swap(a,b);

    }

    if(b<c){

        swap(b,c);

    }

    if(a<b){

        swap(a,b);

    }

    if(m<=a+b+c-3&&m>=a-b-c-1){

        cout<<"Yes"<<endl;

    }else{

        cout<<"No"<<endl;

    }

  

}

signed main(){

    ios::sync_with_stdio(false),cin.tie(0);

    int t;

    cin>>t;

    while(t--){

        solve();

    }

}
```