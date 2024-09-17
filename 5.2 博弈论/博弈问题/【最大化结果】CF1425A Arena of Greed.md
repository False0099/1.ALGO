# Arena of Greed

## 题面翻译

最初，有一个宝箱，里面装着 $N$ 枚金币。如果箱子里没有金币，游戏就结束了。在每一回合中，玩家可以进行以下动作之一：

1. 从箱子里拿出一枚金币。

2. 把箱子上一半的金币拿走。只有当箱子里的硬币数是偶数时，这个移动才可用。

两个玩家都会尽量使他们拥有的硬币数量最大化。查内克先生请你帮忙找出在游戏结束时他能得到的硬币的最大数量，如果他和对手都玩得很好。

## 题目描述

Lately, Mr. Chanek frequently plays the game Arena of Greed. As the name implies, the game's goal is to find the greediest of them all, who will then be crowned king of Compfestnesia.

The game is played by two people taking turns, where Mr. Chanek takes the first turn. Initially, there is a treasure chest containing $ N $ gold coins. The game ends if there are no more gold coins in the chest. In each turn, the players can make one of the following moves:

- Take one gold coin from the chest.
- Take half of the gold coins on the chest. This move is only available if the number of coins in the chest is even.

Both players will try to maximize the number of coins they have. Mr. Chanek asks your help to find the maximum number of coins he can get at the end of the game if both he and the opponent plays optimally.

## 输入格式

The first line contains a single integer $ T $ $ (1 \le T \le 10^5) $ denotes the number of test cases.

The next $ T $ lines each contain a single integer $ N $ $ (1 \le N \le 10^{18}) $ .

## 输出格式

$ T $ lines, each line is the answer requested by Mr. Chanek.

## 样例 #1

### 样例输入 #1

```
2
5
6
```

### 样例输出 #1

```
2
4
```

## 提示

For the first case, the game is as follows:

1. Mr. Chanek takes one coin.
2. The opponent takes two coins.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

For the second case, the game is as follows:

1. Mr. Chanek takes three coins.
2. The opponent takes one coin.
3. Mr. Chanek takes one coin.
4. The opponent takes one coin.

## 题解
我们本题首先注意到，贪心的每一次能减半就减半是**错误的**，因为以 8 为例，我们按照贪心策略，只能达到 5 枚。其实我们还有一种策略，能够帮助我们拿到更多的金币。

我们不妨从我们的反问题来考虑，如果我们每一次自己拿到尽可能多的金币，等价于我们让我们的对手拿到尽可能少的金币。也就是说，我们应该尽可能的让我们的对手只能每一次拿一个金币。于是，我们就有了下面的策略：

如果我们的当前只能选取-1 操作，那么我们显然只能跟着走，否则，如果当前的元素个数是满足%4!=0 并且%2=0 的，那么我们就直接取。**这一个方案对双方都适用**。

```
/* light_chaser */
  #include<bits/stdc++.h>
  using namespace std;
  int T;
  long long n;
  long long ans1,ans2;
  
  template<typename T>void read(register T& a){
      T x=0,f=1; 
      register char c=getchar();
      while(!isdigit(c)){
          if(c=='-')f=-1; 
          c=getchar();
      }
      while(isdigit(c))
      x=(x<<1)+(x<<3)+c-'0',c=getchar();
      a=x*f;
  }//快读
  
  int main(){
      /*cin>>T;*/read(T);
      while(T--){//T组数据
          ans1=0;
          //ans2=0;每次清零A，B持有的硬币数
          /*cin>>n;*/read(n);
          while(1){
              if(n==1){
                  ans1++;
                  goto sp;
              }//只剩下1枚硬币可提前结束
              if(n==4){
                  ans1+=3;
                  //ans2++;
                  goto sp;
              }//特判剩下4枚硬币的情况
              if( n%4==0 || n%2==1 ){
                  n--;
                  ans1++;
                  goto sp1;
              }
              if( n%2==0 && n%4!=0 ){
                  n/=2;
                  ans1+=n;
                  goto sp1;
              }//A的回合
              sp1 : ;
              if(n==1){
                  //ans2++;
                  goto sp;
              }//只剩下1枚硬币可提前结束
              if(n==4){
                  ans1++;
                  //ans2+=3;
                  goto sp;
              }//特判剩下4枚硬币的情况
              if( n%4==0 || n%2==1 ){
                  n--;
                  //ans2++;
                  goto sp2;
              }
              if( n%2==0 && n%4!=0 ){
                  n/=2;
                  //ans2+=n;
                  goto sp2;
              }//B的回合
              sp2 : ;
          }
          sp : ;
          cout<<ans1<<"\n";//输出最后A持有的硬币数
      }
      return 0;
  }

```