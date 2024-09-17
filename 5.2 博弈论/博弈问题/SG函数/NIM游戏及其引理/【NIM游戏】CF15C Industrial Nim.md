# Industrial Nim

## 题面翻译

第一行给出 $N$ 表示有 $N$ 个采石场，接下来 $N$ 行每一行一个 $X_i$ 一个 $M_i$，表示第 $i$ 个采石场有 $M_i$ 辆车，这个采石场中第 $1$ 辆车的石头数量是 $X_i$，第 $2$ 辆车中有 $X_i+1$ 个石头...... 第 $M_i$ 辆车的石头的数量是 $X_i+M_i-1$。

有两个人每次从任意一辆车中取任意数量的石头（不能为 $0$ ），最后一个取完所有石头的赢。若先手赢输出"tolik"，后手赢输出"bolik"。

$1\le n\le 10^5$

$1\le x_i,m_i\le 10^{16}$

## 题目描述

There are $ n $ stone quarries in Petrograd.

Each quarry owns $ m_{i} $ dumpers ( $ 1<=i<=n $ ). It is known that the first dumper of the $ i $ -th quarry has $ x_{i} $ stones in it, the second dumper has $ x_{i}+1 $ stones in it, the third has $ x_{i}+2 $ , and the $ m_{i} $ -th dumper (the last for the $ i $ -th quarry) has $ x_{i}+m_{i}-1 $ stones in it.

Two oligarchs play a well-known game Nim. Players take turns removing stones from dumpers. On each turn, a player can select any dumper and remove any non-zero amount of stones from it. The player who cannot take a stone loses.

Your task is to find out which oligarch will win, provided that both of them play optimally. The oligarchs asked you not to reveal their names. So, let's call the one who takes the first stone «tolik» and the other one «bolik».

## 输入格式

The first line of the input contains one integer number $ n $ ( $ 1<=n<=10^{5} $ ) — the amount of quarries. Then there follow $ n $ lines, each of them contains two space-separated integers $ x_{i} $ and $ m_{i} $ ( $ 1<=x_{i}, m_{i}<=10^{16} $ ) — the amount of stones in the first dumper of the $ i $ -th quarry and the number of dumpers at the $ i $ -th quarry.

## 题解
我们这一题可以通过我们的 NIM 游戏来进行，我们发现每辆车都是一个独立的 nim 游戏，于是我们只需要求出所有车的石头数量的异或和即可。
但是因为我们的数据范围很大，暴力异或不可行，所以我们就需要利用我们的性质：一个偶数和他的下一个奇数的异或和位 1.

于是，我们对于每段连续自然数只需要判断头尾即可，最后异或和非零则先手必胜。
```
#include<iostream>
#include<cstdio>
using namespace std;
int n;
long long ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        long long a,len;
        scanf("%lld%lld",&a,&len);
        if(a%2){ans^=a,++a,--len;}//特判头
        if(len&&len%2){ans^=a+len-1,--len;}//特判尾
        if(len&&(len/2)%2)ans^=1;//中间
    }
    if(ans)printf("tolik\n");
    else printf("bolik\n");
    return 0;
}  
```

## 输出格式

Output «tolik» if the oligarch who takes a stone first wins, and «bolik» otherwise.

## 样例 #1

### 样例输入 #1

```
2
2 1
3 2
```

### 样例输出 #1

```
tolik
```

## 样例 #2

### 样例输入 #2

```
4
1 1
1 1
1 1
1 1
```

### 样例输出 #2

```
bolik
```