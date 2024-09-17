After finally rounding up the Fluttershies at Sweet Apple Acres, we made our way to Pinkie Pie's Sugarcube Corner.

"Wheee!!! Fluttershies, let's have a party!"

There was no way around it; we had to join in and play with Pinkie Pie.

Pinkie Pie invented a two-player game, and we took turns challenging her. Specifically, the game goes as follows:

There are $n$ integers $1,2,3,\dots,n$ ​ arranged in a row **from left to right**. Both Pinkie Pie and I will take turns trying the following operation:

-   If the bitwise XOR sum of the remaining integers is not $0$ ​, remove either the leftmost or the rightmost integer from the row without changing the order of the remaining numbers.

If the current player cannot make a move, they lose the game.

The game consists of $T$ rounds, assuming "I"   always starts first each round, and both of us aim for victory by making optimal moves. The question is whether "I"   can achieve victory in each round of the game.

The bitwise XOR sum of several numbers $a_1,a_2,\dots,a_m$ is denoted by $a_1 \oplus a_2 \oplus \dots \oplus a_m$. Particularly, the XOR sum of an empty set is $0$.

The XOR operation, denoted by $\oplus$, is a binary operation that compares two binary numbers bit by bit. At each position, if the corresponding bits are not all $1$ or not all $0$, the result is $1$; otherwise, it's $0$.

![](https://espresso.codeforces.com/55c348724e8a405ab2f51f8ba1a9e2c18b392d56.png)

**Input**

The first line contains an integer $T$ ($1 \leq T \leq 10^5$), indicating the number of rounds in the game.

Following that are $T$ lines, each containing an integer $n$ ($1 \leq n \leq 10^6$), representing the number of integers in the corresponding round of the game.

**Output**

For each round of the game, output one line. If "I"   can win, output "Fluttershy"; otherwise, output "Pinkie Pie" (without the quotes).

## 题解
我们首先计算我们的每一场的异或和是多少，显然，我们首先有：因为我们的异或和是一个序列，那么我们就有：$$\oplus_{i=1}^{n}i=\begin{cases}1&\text{n mod 4}=1\\\text{n}+1&\text{n mod 4}=2\\0&\text{n mod 4}=3\\\text{n}&\text{n mod 4}=0\end{cases}$$

之后，我们不难发现，如果我们的起始状态为 0，那么我们是必败的，并且我们的为 1，为 n 的情况可以一部走到必败态，n+1 走一步一定是走到必胜态。

所以，我们就不难写出我们的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		if(n%4==0||n%4==1){
			cout<<"Fluttershy"<<endl;
		}else{
			cout<<"Pinkie Pie"<<endl;
		}
	}
} 
```