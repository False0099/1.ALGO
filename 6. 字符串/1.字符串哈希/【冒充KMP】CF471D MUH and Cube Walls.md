# MUH and Cube Walls

## 题面翻译

给两堵墙，问 $a$ 墙中与 $b$ 墙顶部形状相同的区间有多少个。

Translated by @aface 0427


## 题目描述

Polar bears Menshykov and Uslada from the zoo of St. Petersburg and elephant Horace from the zoo of Kiev got hold of lots of wooden cubes somewhere. They started making cube towers by placing the cubes one on top of the other. They defined multiple towers standing in a line as a wall. A wall can consist of towers of different heights.

Horace was the first to finish making his wall. He called his wall an elephant. The wall consists of $ w $ towers. The bears also finished making their wall but they didn't give it a name. Their wall consists of $ n $ towers. Horace looked at the bears' tower and wondered: in how many parts of the wall can he "see an elephant"? He can "see an elephant" on a segment of $ w $ contiguous towers if the heights of the towers on the segment match as a sequence the heights of the towers in Horace's wall. In order to see as many elephants as possible, Horace can raise and lower his wall. He even can lower the wall below the ground level (see the pictures to the samples for clarification).

Your task is to count the number of segments where Horace can "see an elephant".

## 输入格式

The first line contains two integers $n$ and $w$ ( $1\le n,w \le 2 \times 10^5$ ) — the number of towers in the bears' and the elephant's walls correspondingly. The second line contains $n$ integers $a_i$ ($1 \le a_i \le 10^9$) — the heights of the towers in the bears' wall. The third line contains $w$ integers $b_i$ ($1 \le b_i \le 10^9$) — the heights of the towers in the elephant's wall.

## 输出格式

Print the number of segments in the bears' wall where Horace can "see an elephant".

## 样例 #1

### 样例输入 #1

```
13 5
2 4 5 5 4 3 2 2 2 3 3 2 1
3 4 4 3 2
```

### 样例输出 #1

```
2
```

## 提示

The picture to the left shows Horace's wall from the sample, the picture to the right shows the bears' wall. The segments where Horace can "see an elephant" are in gray.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF471D/4bab2ce5008bc40c15cf28d8ffc04197c7f77d57.png)
## 题解
本题我们要抹去我们的**初始元素对于我们的结果的影响**，我们显然应该想到使用我们的**差分数组**，我们每一次对于我们的差分数组所有长度为 $o(len)$ 的串，都去查询她是否与我们的对应的墙相等。

如果相等，我们直接答案+1 即可，否则我们不进行处理。

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
    int n,w;
    cin>>n>>w;
    vector<int> a(n);
    vector<int> d;
    for(int i=0;i<n;i++){
        cin>>a[i];
    } 
    vector<int> b(w);
    //vector<int> d1(n);
    for(int i=0;i<w;i++){
        cin>>b[i];
    }
    for(int i=1;i<w;i++){
        d.push_back(b[i]-b[i-1]);
    }
    d.push_back(INF);
    for(int i=1;i<n;i++){
        d.push_back(a[i]-a[i-1]);
    }
    if(w==1){
        cout<<n<<endl;
        return;
    }
    // for(auto u:d){
    //     cerr<<u<<" ";
    // }
    // cerr<<endl;
    vector<int> pi(d.size(),0);
    int cnt=0;
    for(int i=1;i<d.size();i++){
        int len=pi[i-1];
        while(len!=0&&d[i]!=d[len]){
            len=pi[len-1];
        }
        if(d[i]==d[len]){
            pi[i]=len+1;
            if(pi[i]==w-1){
                cnt++;
            }
        }
    }
    cout<<cnt<<endl;
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
 //   cin>>t;
    init();
    while(t--){
        solve();
    }
}
```