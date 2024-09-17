# Arpa and a game with Mojtaba

## 题面翻译

Mojtaba 和 Arpa 在玩一个游戏。  

游戏中有一个 n 个数的数列，在一个回合中，他可以选取一个形如 $p^k$ 的数，其中 $p$ 是个质数，而 $k$ 是一个正整数，并且满足这个数列中至少有一个数能被它整除。每一个回合结束时将整个数列中所有的能被这个数整除的数都将除以这个数。  

（例如数列{$1$，$1$，$17$，$289$}. 如果选取了 $17$，经过一个回合之后数列将变成{$1$，$1$，$1$，$17$}）  而游戏胜负的条件是有一个人如果无法选出这样一个数就输了。

游戏中 Mojtaba 先手，游戏双方都将用最优策略，输出胜利者的名字。  
## 输入格式 ：  
第一行 n，表示这个数列的长度  
第二行 n 个数，表示这个数列  

## 输出格式 ：  
一个名字，无论大小写（即答案如果是 Arpa，arpa，ARPA，aRpA 都可）  
## 说明 ：
第一个样例中 Mojtaba 无法选取任何数字，Arpa 胜；   
第二个样例中 Mojtaba 选取 $17$（$17^1$），数列变为{$1$，$1$，$1$，$1$}，Arpa 无法选取，Mojtaba 胜；  
第三个样例中 Mojtaba 选取 $17$（$17^1$），Arpa 选取 $17$（$17^1$），胜。或者 Mojtaba 选取 $289$（$17^2$），Arpa 选取 $17$（$17^1$）胜。

## 题目描述

Mojtaba and Arpa are playing a game. They have a list of $ n $ numbers in the game.

In a player's turn, he chooses a number $ p^{k} $ (where $ p $ is a prime number and $ k $ is a positive integer) such that $ p^{k} $ divides at least one number in the list. For each number in the list divisible by $ p^{k} $ , call it $ x $ , the player will delete $ x $ and add ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850C/850f475308e1a5d29f90bf50cce5258d86ba6e49.png) to the list. The player who can not make a valid choice of $ p $ and $ k $ loses.

Mojtaba starts the game and the players alternatively make moves. Determine which one of players will be the winner if both players play optimally.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100 $ ) — the number of elements in the list.

The second line contains $ n $ integers $ a_{1}, a_{2},..., a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of the list.

## 输出格式

If Mojtaba wins, print "Mojtaba", otherwise print "Arpa" (without quotes).

You can print each letter in any case (upper or lower).

## 样例 #1

### 样例输入 #1

```
4
1 1 1 1
```

### 样例输出 #1

```
Arpa
```

## 样例 #2

### 样例输入 #2

```
4
1 1 17 17
```

### 样例输出 #2

```
Mojtaba
```

## 样例 #3

### 样例输入 #3

```
4
1 1 17 289
```

### 样例输出 #3

```
Arpa
```

## 样例 #4

### 样例输入 #4

```
5
1 2 3 4 5
```

### 样例输出 #4

```
Arpa
```

## 提示

In the first sample test, Mojtaba can't move.

In the second sample test, Mojtaba chooses $ p=17 $ and $ k=1 $ , then the list changes to $ [1,1,1,1] $ .

In the third sample test, if Mojtaba chooses $ p=17 $ and $ k=1 $ , then Arpa chooses $ p=17 $ and $ k=1 $ and wins, if Mojtaba chooses $ p=17 $ and $ k=2 $ , then Arpa chooses $ p=17 $ and $ k=1 $ and wins.


## 题解
我们本体的思路是：因为我们的各个质数是互补干扰的，因此，我们就可以转换为：对于我们的每一个质数，**我们都构成一个取石子游戏**，游戏要求我们**每一次可以选择一群石子都降低 k 个。

然后问你，这几个游戏叠加起来的结果是多少。叠加起来的结果显然是我们每一次进行异或即可得到我们的答案。而对于我们的每一个数字的质因数分解。

接下来考虑如何转移。首先我们肯定可以把每一个质数分开考虑 (即按质数分别 grundy 分解), 假设我们对于一个质数 $p$,要除以它的 $i$ 次方，我们想，现在这个数的状态该如何表示。假设原状态为 $x$,那么，所有大于 $i$ 的位置，都会右移 $i$ 位，而前 $i-1$ 位不变 (因为不能整除，所以不除)。因此，新状态就可以表示成
$$x>>i|(x\&(1<<i-1)-1)$$



```
#include<cstdio>
#include<map>
#include<cstring>
#define maxn 1000010
using namespace std;
int n,tot=0,flag=0,prime[maxn];
bool isprime[maxn];
map<int,int>sg,st;
inline int read()
{
   char c=getchar();
   int x=0;
   while(c<'0'||c>'9') c=getchar();
   while(c>='0'&&c<='9')
   	x=(x<<3)+(x<<1)+c-48,c=getchar();
   return x;
}
int ssg(int x){//SG函数 
   if(x==0)return 0;
   if(sg.count(x))return sg[x];
   map<int,int>vis;
   int p=x,t=0;
   while(p)p>>=1,t++;
   for(int i=1;i<=t;i++)
       vis[ssg((x>>i)|(x&((1<<i-1)-1)))]=1; //主要步骤   
   for(int i=0;;i++)
       if(!vis[i])return sg[x]=i;
}
inline void work(int x){//分解质因数 
   for(int i=1;prime[i]*prime[i]<=x;i++){
       int t=0;
       while(x%prime[i]==0){
           x/=prime[i];
           t++;
       }
       if(t)
   		st[prime[i]]|=1<<(t-1);
   }
   if(x!=1)
   	st[x]|=1;
}
inline void prepare(){//筛素数 
   memset(isprime,true,sizeof(isprime));
   isprime[1]=false;
   for(int i=2;i<=maxn-10;i++){
       if(isprime[i])prime[++tot]=i;
       for(int j=1;j<=tot&&i*prime[j]<=maxn-10;j++){
           isprime[i*prime[j]]=false;
           if(i%prime[j]==0)break;
       }
   }
}
int main(){
   prepare();
   n=read();
   for(int i=1;i<=n;i++){
       int x;
       x=read();
       work(x);
   }
   map<int,int>::iterator it;
   for(it=st.begin();it!=st.end();it++)
   	flag^=ssg(it->second);
   if(flag)puts("Mojtaba");
   else puts("Arpa");
   return 0;
}

```