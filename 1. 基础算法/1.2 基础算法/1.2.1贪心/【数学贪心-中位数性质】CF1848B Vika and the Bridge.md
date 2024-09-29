# Vika and the Bridge

## 题面翻译

有 $n$ 块木板排成一排，第 $i$ 块木板的颜色是 $c_i$，你站在第一块木板前面，需要跳跃到第 $n$ 块木板后面，每一次只能跳相同颜色的木板。现在你可以更改一块木板的颜色，使得你每一次跳跃的距离 (指两块木板中间部分，不计两端点)的最大值最小，请求出这个值。

## 题目描述

In the summer, Vika likes to visit her country house. There is everything for relaxation: comfortable swings, bicycles, and a river.

There is a wooden bridge over the river, consisting of $ n $ planks. It is quite old and unattractive, so Vika decided to paint it. And in the shed, they just found cans of paint of $ k $ colors.

After painting each plank in one of $ k $ colors, Vika was about to go swinging to take a break from work. However, she realized that the house was on the other side of the river, and the paint had not yet completely dried, so she could not walk on the bridge yet.

In order not to spoil the appearance of the bridge, Vika decided that she would still walk on it, but only stepping on planks of the same color. Otherwise, a small layer of paint on her sole will spoil the plank of another color. Vika also has a little paint left, but it will only be enough to repaint one plank of the bridge.

Now Vika is standing on the ground in front of the first plank. To walk across the bridge, she will choose some planks of the same color (after repainting), which have numbers $ 1 \le i_1 < i_2 < \ldots < i_m \le n $ (planks are numbered from $ 1 $ from left to right). Then Vika will have to cross $ i_1 - 1, i_2 - i_1 - 1, i_3 - i_2 - 1, \ldots, i_m - i_{m-1} - 1, n - i_m $ planks as a result of each of $ m + 1 $ steps.

Since Vika is afraid of falling, she does not want to take too long steps. Help her and tell her the minimum possible maximum number of planks she will have to cross in one step, if she can repaint one (or zero) plank a different color while crossing the bridge.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5 $ ) — the number of planks in the bridge and the number of different colors of paint.

The second line of each test case contains $ n $ integers $ c_1, c_2, c_3, \dots, c_n $ ( $ 1 \le c_i \le k $ ) — the colors in which Vika painted the planks of the bridge.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum possible maximum number of planks that Vika will have to step over in one step.

## 样例 #1

### 样例输入 #1

```
5
5 2
1 1 2 1 1
7 3
1 2 3 3 3 2 1
6 6
1 2 3 4 5 6
8 4
1 2 3 4 2 3 1 4
3 1
1 1 1
```

### 样例输出 #1

```
0
1
2
2
0
```

## 提示

In the first test case, Vika can repaint the plank in the middle in color $ 1 $ and walk across the bridge without stepping over any planks.

In the second test case, Vika can repaint the plank in the middle in color $ 2 $ and walk across the bridge, stepping over only one plank each time.

In the third test case, Vika can repaint the penultimate plank in color $ 2 $ and walk across the bridge, stepping only on planks with numbers $ 2 $ and $ 5 $ . Then Vika will have to step over $ 1 $ , $ 2 $ and $ 1 $ plank each time she steps, so the answer is $ 2 $ .

In the fourth test case, Vika can simply walk across the bridge without repainting it, stepping over two planks each time, walking on planks of color $ 3 $ .

In the fifth test case, Vika can simply walk across the bridge without repainting it, without stepping over any planks.

## 题解
本题我们可以发现，为了让我们两个人之间跨国的距离尽可能的小，我们首先**每一种颜色**是独立的，于是我们就可以对我们的每一种颜色单独计算。因为我们的目标是让我们的最大值最小，所以我们最好的决策就是在我们的最大值**均分为两端**，然后在和我们的 **次大值进行比较**。最后就能得到我们的答案。

```
/*
 * @Author:Kaneki
 * @Date:2023-11-04 14:21:38
 * @Last Modified by:Kaneki
 * @Last Modified Time:2023-11-04 14:21:38
 * @Description:Kaneki
*/
#include<bits/stdc++.h>
using namespace std;
int T,N,K,num[200005],pre[200005],Max[200005],SecMax[200005];
int main(){
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>N>>K;
        for(int i=1;i<=N;i++){
            cin>>num[i];
            if(i-pre[num[i]]-1>Max[num[i]])SecMax[num[i]]=Max[num[i]],Max[num[i]]=i-pre[num[i]]-1;//更新最大值
            else if(i-pre[num[i]]-1>SecMax[num[i]])SecMax[num[i]]=i-pre[num[i]]-1;//更新次大值
            pre[num[i]]=i;//记录num[i]颜色上次出现的位置
        }
        int ans=0x7fffffff;
        for(int i=1;i<=K;i++){//考虑每个颜色最后走出去对答案的贡献
            if(N-pre[i]>Max[i])SecMax[i]=Max[i],Max[i]=N-pre[i];
            else if(N-pre[i]>SecMax[i])SecMax[i]=N-pre[i];
        }
        for(int i=1;i<=K;i++){//更新答案
            ans=min(max(SecMax[i],Max[i]/2),ans);
        }
        printf("%d\n",ans);
        for(int i=1;i<=N;i++) pre[i]=0;
        for(int i=1;i<=K;i++) Max[i]=0,SecMax[i]=0;//多测清空
    }
    return 0;
}
```