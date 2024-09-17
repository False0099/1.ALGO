# Very Interesting Game

## 题面翻译

### 题意

在一个非常古老的国家，以下游戏很受欢迎。

开始时玩家 $A$ 写一个字符串 $s_1$ ，由正好九位数组成，表示一个不超过 $a$ 的数字。之后，玩家 $B$ 查看 $s_1$ 并写一个字符串 $s_2$ ，也正好为九位数，表示一个不超过 $b$ 的数字。这里 $a$ 和 $b$ 是一些给定的常数， $s_1$ 和 $s_2$ 由玩家自由选择。字符串允许包含前导零。

如果通过字符串 $s_1$ 和 $s_2$ 连接在一起后形成的数字可以被 $mod$ 整除，则玩家 $B$ 获胜。否则玩家 $A$ 获胜。

现在给你 $a$ ， $b$ ， $mod$ 。如果双方都使用最优策略，请确定谁赢了。如果玩家 $A$ 获胜，您还需要找到字典序最小的获胜字符串 $s_1$ 。

### 输入格式

一行三个整数 $a$ ， $b$ ， $mod$ 。（ $0 \leqslant a,b \leqslant 10^{9}$ ， $1 \leqslant mod \leqslant 10^{7}$ ）

### 输出格式

如果玩家 $A$ 获胜，则输出“ $1$ ”和字典序最小的获胜字符串 $s_1$ 。如果玩家 $B$ 获胜，则输出“ $2$ ”。

## 题目描述

In a very ancient country the following game was popular. Two people play the game. Initially first player writes a string $ s_{1} $ , consisting of exactly nine digits and representing a number that does not exceed $ a $ . After that second player looks at $ s_{1} $ and writes a string $ s_{2} $ , consisting of exactly nine digits and representing a number that does not exceed $ b $ . Here $ a $ and $ b $ are some given constants, $ s_{1} $ and $ s_{2} $ are chosen by the players. The strings are allowed to contain leading zeroes.

If a number obtained by the concatenation (joining together) of strings $ s_{1} $ and $ s_{2} $ is divisible by $ mod $ , then the second player wins. Otherwise the first player wins. You are given numbers $ a $ , $ b $ , $ mod $ . Your task is to determine who wins if both players play in the optimal manner. If the first player wins, you are also required to find the lexicographically minimum winning move.

## 输入格式

The first line contains three integers $ a $ , $ b $ , $ mod $ ( $ 0<=a, b<=10^{9} $ , $ 1<=mod<=10^{7} $ ).

## 输出格式

If the first player wins, print "1" and the lexicographically minimum string $ s_{1} $ he has to write to win. If the second player wins, print the single number "2".

## 样例 #1

### 样例输入 #1

```
1 10 7
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
4 0 9
```

### 样例输出 #2

```
1 000000001
```

## 提示

The lexical comparison of strings is performed by the < operator in modern programming languages. String $ x $ is lexicographically less than string $ y $ if exists such $ i $ ( $ 1<=i<=9 $ ), that $ x_{i}&lt; y_{i} $ , and for any $ j $ ( $ 1<=j&lt; i $ ) $ x_{j}=y_{j} $ . These strings always have length 9.


## 题解
我们本题和我们的牛子寒假集训营中的有一题非常相似，我们考虑能不能直接进行性质的推移，我们发现, 我们可以先预处理出我们 b 出手后，我们取模的范围有哪些，以及取到这些模数的时候，我们的位数是多少位。这里，我们固定了我们的元素只能是 9 位数，于是我们对应的答案就是：$a*10^{9}\text{ mod } M$,如果我们能够找到这么一个 $a$,让他没有 b 和他对应，那么我们就是先手必胜。

注意：我们要记得特判 0 和我们的 a 大小，我们 a 的大小只用枚举到我们的 mod 即可

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e9;
signed main(){
	int a,b,mod;
	cin>>a>>b>>mod;
	if(b>=mod-1){
		cout<<"2"<<endl;
	}else{
		int prev1=N%mod;//(a*prev1)%mod;
		for(int i=0;i<=min(a,mod);i++){
			if((prev1*i)%mod<mod-b&&(prev1*i)%mod>0){
				cout<<"1"<<" ";
				printf("%09d\n",i);
				return 0;
			}
		}
			cout<<2<<endl;
		
	}
}
```