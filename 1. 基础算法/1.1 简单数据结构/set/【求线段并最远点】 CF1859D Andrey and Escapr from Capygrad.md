# Andrey and Escape from Capygrad

## 题面翻译

给定 $n$ 对区间，每对区间由大区间 $[l_i,r_i]$ 和小区间 $[a_i,b_i]$ 构成，保证小区间是大区间的子区间。在任意时间，你可以任意多次使用（可以不使用）以下技能来改变你的当前位置：

* 选择一个数 $i(1\le i\le n)$ ，满足你当前位置在第 $i$ 对区间的大区间内，则你可以立即传送到这对区间的小区间里的你指定的任意位置。

$q$ 组询问，每组询问给定一个初始位置 $x$ ，回答当你初始位置为 $x$ 时，你能**只通过传送技能**传送到的最大位置。

## 题目描述

An incident occurred in Capygrad, the capital of Tyagoland, where all the capybaras in the city went crazy and started throwing mandarins. Andrey was forced to escape from the city as far as possible, using portals.

Tyagoland is represented by a number line, and the city of Capygrad is located at point $ 0 $ . There are $ n $ portals all over Tyagoland, each of which is characterised by four integers $ l_i $ , $ r_i $ , $ a_i $ and $ b_i $ ( $ 1 \le l_i \le a_i \le b_i \le r_i \le 10^9 $ ). Note that the segment $ [a_i, b_i] $ is contained in the segment $ [l_i, r_i] $ .

If Andrey is on the segment $ [l_i, r_i] $ , then the portal can teleport him to any point on the segment $ [a_i, b_i] $ . Andrey has a pass that allows him to use the portals an unlimited number of times.

Andrey thinks that the point $ x $ is on the segment $ [l, r] $ if the inequality $ l \le x \le r $ is satisfied.

Andrey has $ q $ options for where to start his escape, each option is characterized by a single integer $ x_i $ — the starting position of the escape. He wants to escape from Capygrad as far as possible (to the point with the maximum possible coordinate). Help Andrey determine how far he could escape from Capygrad, starting at each of the $ q $ positions.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of sets of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of portals.

Each of the next $ n $ lines contains four integers $ l_i $ , $ r_i $ , $ a_i $ , and $ b_i $ $ (1 \le l_i \le a_i \le b_i \le r_i \le 10^9) $ — the characteristics of the portals.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of positions.

The following line contains $ q $ integers $ x_1, x_2, \ldots, x_q $ ( $ 1 \le x_i \le 10^9 $ ) — the position from which Andrey will start his escape in the $ i $ -th options.

It is guaranteed that the sum of $ n $ and the sum of $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line of $ q $ integers, containing the answers to Andrey's questions.

## 样例 #1

### 样例输入 #1

```
5
3
6 17 7 14
1 12 3 8
16 24 20 22
6
10 2 23 15 28 18
3
3 14 7 10
16 24 20 22
1 16 3 14
9
2 4 6 8 18 23 11 13 15
2
1 4 2 3
3 9 6 7
3
4 8 1
5
18 24 18 24
1 8 2 4
11 16 14 14
26 32 28 30
5 10 6 8
9
15 14 13 27 22 17 31 1 7
6
9 22 14 20
11 26 13 24
21 33 22 23
21 33 25 32
1 6 3 4
18 29 20 21
8
11 23 16 5 8 33 2 21
```

### 样例输出 #1

```
14 14 23 15 28 22 
14 14 14 14 22 23 14 14 15 
7 8 7 
15 14 14 30 24 17 31 4 8 
32 32 32 5 8 33 4 32
```

## 提示

In the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1859D/e16f53a0bb292ac32fb706ca20fa668cca5f7c21.png)Optimal actions when starting from each position:

1. Use portal $ 1 $ and teleport to point $ b_1 = 14 $ .
2. Use portal $ 2 $ first and teleport to point $ 6 $ , which is on the segment $ [l_1, r_1] = [6, 17] $ , then use portal $ 1 $ and teleport to point $ b_1 = 14 $ .
3. Stay at point $ x_3=23 $ without using any portals.
4. Stay at point $ x_4=15 $ without using any portals.
5. Point $ x_5=28 $ is not on any segment, so Andrey won't be able to teleport anywhere.
6. Point $ x_6=18 $ is only on the segment $ [l_3, r_3] = [16, 24] $ , use portal $ 3 $ and teleport to point $ b_3 = 22 $ .

In the fifth test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1859D/039563dbba6cbb0aa164e573669410ec3fd16328.png)Optimal actions when starting from each position:

1. Use portal $ 1 $ first and teleport to point $ 15 $ on the segment $ [a_1, b_1] = [14, 20] $ , then use portal $ 2 $ and teleport to point $ 21 $ , which is on the segment $ [l_4, r_4] = [21, 33] $ and on the segment $ [a_2, b_2] = [13, 24] $ , then teleport to point $ b_4 = 32 $ .
2. Use portal $ 6 $ first and teleport to point $ 20 $ on the segment $ [a_6, b_6] = [20, 21] $ , then use portal $ 2 $ and teleport to point $ 22 $ , which is simultaneously on the segment $ [l_4, r_4] = [21, 33] $ and on the segment $ [a_2, b_2] = [13, 24] $ , then teleport to point $ b_4 = 32 $ .
3. Perform the same actions as from the first position.
4. Stay at point $ x_4=5 $ without using any portals.
5. Point $ 8 $ is not on any segment, so Andrey won't be able to teleport anywhere.
6. Stay at point $ x_6=33 $ without using any portals.
7. Use portal $ 5 $ and teleport to point $ b_5 = 4 $ .
8. Perform the same actions as from the first position.

## 题解
本题中，首先我们注意到，如果我们能到达一个点，我们一定是到达我们一个点的最右端，而不会去考虑其他地方，因此，我们的线段长度实际上不需要维护我们的那么多，我们只需要维护我们的 $[le,b]$ 即可，因为我们如果在我们的 $[b,r]$ 我们对我们的答案贡献一定是负的。

综上，因此，我们可以采用一个 set 来维护我们从某一个点除法，能够到达的最远点是哪里。我们谓词需要先预处理我们的每一个线段。我们每一次维护完一个线段后，我们只需要把我们的对应线段添加到我们的 set 中，然后我们再去查询我们的 x 对应的 r 在哪里即可。

```cpp
#include<iostream>
#include<algorithm>
#include<set>
const int sz=2e5+10;
struct segment{
    int l,r;
    bool operator<(const segment &a)const{
        return l<a.l;
    }
}line[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin>>t;
    while(t--){
        int n,q;
        std::cin>>n;
        for(int i=1;i<=n;i++){
            int l,r,a,b;
            std::cin>>l>>r>>a>>b;
            line[i]=segment{l,b};
        }
        std::sort(line+1,line+n+1);//按照我们的左端点排序
        std::set<segment>cur;
        cur.insert(segment{0,0});
        for(int i=1;i<=n;i++){
            int l=line[i].l,r=line[i].r;
            while(i<n&&line[i+1].l>=l&&line[i+1].l<=r)i++,r=std::max(r,line[i].r);//线段合并
            cur.insert(segment{l,r});
        }
        std::cin>>q;
        for(int i=1,x;i<=q;i++){
            std::cin>>x;
            auto it=--cur.upper_bound(segment{x,x});
            if(x<=it->r)std::cout<<it->r<<" ";
            else std::cout<<x<<" ";
        }
        std::cout<<"\n";
    }
    return 0;
}
```

 