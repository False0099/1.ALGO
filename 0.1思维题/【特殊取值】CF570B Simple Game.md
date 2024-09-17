# Simple Game

## 题面翻译

给 n，m (m <= n)，求一个数 a (1<= a <=n), 使得当 c 在 1 到 n 的整数中随机取值时
,|c-a| < |c-m| 成立的概率最大。

感谢@凉凉提供的翻译

## 题目描述

One day Misha and Andrew were playing a very simple game. First, each player chooses an integer in the range from $ 1 $ to $ n $ . Let's assume that Misha chose number $ m $ , and Andrew chose number $ a $ .

Then, by using a random generator they choose a random integer $ c $ in the range between $ 1 $ and $ n $ (any integer from $ 1 $ to $ n $ is chosen with the same probability), after which the winner is the player, whose number was closer to $ c $ . The boys agreed that if $ m $ and $ a $ are located on the same distance from $ c $ , Misha wins.

Andrew wants to win very much, so he asks you to help him. You know the number selected by Misha, and number $ n $ . You need to determine which value of $ a $ Andrew must choose, so that the probability of his victory is the highest possible.

More formally, you need to find such integer $ a $ ( $ 1<=a<=n $ ), that the probability that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF570B/fcf679a711cde29d2e9f9a082e28c313061224e7.png) is maximal, where $ c $ is the equiprobably chosen integer from $ 1 $ to $ n $ (inclusive).

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=m<=n<=10^{9} $ ) — the range of numbers in the game, and the number selected by Misha respectively.

## 输出格式

Print a single number — such value $ a $ , that probability that Andrew wins is the highest. If there are multiple such values, print the minimum of them.

## 样例 #1

### 样例输入 #1

```
3 1
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
4 3
```

### 样例输出 #2

```
2
```

## 提示

In the first sample test: Andrew wins if $ c $ is equal to $ 2 $ or $ 3 $ . The probability that Andrew wins is $ 2/3 $ . If Andrew chooses $ a=3 $ , the probability of winning will be $ 1/3 $ . If $ a=1 $ , the probability of winning is $ 0 $ .

In the second sample test: Andrew wins if $ c $ is equal to $ 1 $ and $ 2 $ . The probability that Andrew wins is $ 1/2 $ . For other choices of $ a $ the probability of winning is less.

## 题解
我们本题源自于一个经典的模型：也就是我们七年级上册的去绝对值的知识，如果我们想要满足我们题目中的条件，那么我们就一定要满足：
$c<a<m$,或者 $c>a>m$ 或者 $a<c<m$ 并且 $c-a<m-c$ 。
![[Pasted image 20240406141204.png]]
然后我们经过计算后，不难发现，如果我们要满足上面的条件，那么我们一定要满足：如果我们的最佳答案只可能有 $m-1$ 和 $m+1$ 两种情况，并且我们如果选择了一侧，我们另一侧一定是不满足的。
那么选择哪一种呢？很显然，如果我们的 $m$ 在我们的 $\frac{n}{2}$ 的右侧，那么我们选择我们的左侧 $m-1$，反之，我们就选择我们的右侧，也就是我们的 $m+1$ 。

另外，注意特判 $n=1,m=1$ 的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n,m;
	cin>>n>>m;
	if(n==1&&m==1){
		cout<<1<<endl;
		return 0;
	}
	if(m>n/2){
		cout<<m-1<<endl;
	}else{
		cout<<m+1<<endl;
	}
}

```
