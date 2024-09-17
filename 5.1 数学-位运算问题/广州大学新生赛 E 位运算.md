https://ac.nowcoder.com/acm/contest/72487/E

## 题目：
给定两个整数 $a$ 和 $c$ ，请你找出一个**最小**的整数 $b(0≤b≤10^{16})$ ，使得 $(a \oplus b)+(a\And b)+(a|b)=c$。

其中，$\oplus$ 表示按位异或，$\And$ 表示按位与，$|$ 表示按位或。

## 输入：
第一行输入两个整数 $a,c(0≤a,c≤10^{16})$。

## 输出：
输出一个满足条件的整数 $b(0≤b≤10^{16})$；  
  
若没有满足条件的 $b$ ，输出 $-1$。

## 题解
我们这一题的关键在于列出我们的真值表。
![[Pasted image 20240120182033.png]]
不难发现，我们的上述运算的最终结果可以化简为我们的：
$2(a|b)=c$,
于是，我们可以先进行第一次判断，如果我们的 $c$ 是一个奇数，那么一定是不可行的。
同时，如果我们 $a$ 中某一位为 1，但是在 c 中为 0，也是一定不可行的。

判断完上面两种情况后，我们的答案就可以直接用我们的 $a |\dfrac{c}{2}$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
ios::sync with stdio(false);cin.tie(0),cout.tie(0);
ll a,c;cin>>a>>c;
if((c&1)||(a&(c/2))!=a)cout<<" 1\n";else cout<<(a^(c/2))<<'\n';
return 0;
}
```