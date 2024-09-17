# Circle of Monsters

## 题面翻译

有 $N$ 头怪兽，他们围成一个环，顺时针编号 $1,2,3,4,\dots ,N$ 每一头怪兽都有 2 个属性，一个是它的生命值 $a_i$，第二个是它的爆炸值 $b_i$。

你有一把手枪，每开一枪可以对你选定的一只怪兽造成 $1$ 伤害（使其生命值 $-1$）

当一个怪兽死后（生命值 $\leq 0$），它会发生爆炸，并对下一个怪兽（假设当前怪兽为编号 $i$，则下一个为 $i+1$。如果 $i=n$，则下一个为 $1$ 号）
造成 $b_i$ 点伤害。如果下一个怪兽已经死了，则没有事发生。如果下一个怪兽被炸死了，那么他也会爆炸，并对下下个怪兽造成伤害。以此类推。

询问你最少开几枪可以杀死所有怪兽。

**每个测试点多组数据**，$\sum N\leq 3\times 10^5$，$a_i,b_i\leq 10^{12}$

## 题目描述

You are playing another computer game, and now you have to slay $ n $ monsters. These monsters are standing in a circle, numbered clockwise from $ 1 $ to $ n $ . Initially, the $ i $ -th monster has $ a_i $ health.

You may shoot the monsters to kill them. Each shot requires exactly one bullet and decreases the health of the targeted monster by $ 1 $ (deals $ 1 $ damage to it). Furthermore, when the health of some monster $ i $ becomes $ 0 $ or less than $ 0 $ , it dies and explodes, dealing $ b_i $ damage to the next monster (monster $ i + 1 $ , if $ i < n $ , or monster $ 1 $ , if $ i = n $ ). If the next monster is already dead, then nothing happens. If the explosion kills the next monster, it explodes too, damaging the monster after it and possibly triggering another explosion, and so on.

You have to calculate the minimum number of bullets you have to fire to kill all $ n $ monsters in the circle.

## 输入格式

The first line contains one integer $ T $ ( $ 1 \le T \le 150000 $ ) — the number of test cases.

Then the test cases follow, each test case begins with a line containing one integer $ n $ ( $ 2 \le n \le 300000 $ ) — the number of monsters. Then $ n $ lines follow, each containing two integers $ a_i $ and $ b_i $ ( $ 1 \le a_i, b_i \le 10^{12} $ ) — the parameters of the $ i $ -th monster in the circle.

It is guaranteed that the total number of monsters in all test cases does not exceed $ 300000 $ .

## 输出格式

For each test case, print one integer — the minimum number of bullets you have to fire to kill all of the monsters.

## 样例 #1

### 样例输入 #1

```
1
3
7 15
2 14
5 3
```

### 样例输出 #1

```
6
```

## 题解
本题我们显然可以考虑通过我们的枚举，枚举我们从哪一个怪物作为我们的起点来进行攻击，那么我们显然之后我们的所有的攻击都是固定的，**且我们的这一个值是可以通过我们的预处理计算得到的**。于是，我们就可以通过我们的简单计算和预处理得到我们的答案;

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
using PIII=pair<PII,int>;
void init(){
    
}
void solve(){
    int n;
    cin>>n;
    vector<int> a(n);
    vector<int> b(n);
    //set<PIII> st;
    int sum=INF;
    for(int i=0;i<n;i++){
        cin>>a[i]>>b[i];
        //st.insert({{a[i],-b[i]},i});
    }
    //a[i]相同时，优先对谁开枪？好像不是能贪的。还和后续的其他元素有关，似乎只能枚举。。。
    vector<int> c(n);
    int res=0;
    for(int i=0;i<n;i++){
        if(i==0){
            c[i]=max(0ll,a[i]-b[n-1]);
        }else{
            c[i]=max(0ll,a[i]-b[i-1]);
        }
        res+=c[i];
    }
    //cerr<<res<<endl;
    for(int i=0;i<n;i++){
        sum=min(sum,res-c[i]+a[i]);
    }
    cout<<sum<<endl;
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