# Unforgivable Curse (easy version)

## 题面翻译

与 E 2 的差异仅在 $k$ 的取值不同。

给定两个长度为 $n$ 的字符串 $s_1,s_2$ 以及一个正整数 $k$，你可以进行任意次操作（可以不操作）：

若 $|i-j|=k$ 或 $|i-j|=k+1$，交换 $s_2$ 第 $i$ 个位置的字符与第 $j$ 个位置的字符。

问最终能否使得 $s_1,s_2$ 完全相同。

本题有多组测试数据。

$1\leq T\leq 10^4,1\leq n\leq 2\times 10^5,k=3,\sum n\leq 2\times 10^5$

translated by @ [StayAlone](https://www.luogu.com.cn/user/409236)

## 题目描述

This is an easy version of the problem. In this version, $ k $ is always $ 3 $ .

The chief wizard of the Wizengamot once caught the evil wizard Drahyrt, but the evil wizard has returned and wants revenge on the chief wizard. So he stole spell $ s $ from his student Harry.

The spell — is a $ n $ -length string of lowercase Latin letters.

Drahyrt wants to replace spell with an unforgivable curse — string $ t $ .

Drahyrt, using ancient magic, can swap letters at a distance $ k $ or $ k+1 $ in spell as many times as he wants. In this version of the problem, you can swap letters at a distance of $ 3 $ or $ 4 $ . In other words, Drahyrt can change letters in positions $ i $ and $ j $ in spell $ s $ if $ |i-j|=3 $ or $ |i-j|=4 $ .

For example, if $ s =  $ "talant" and $ t =  $ "atltna", Drahyrt can act as follows:

- Swap the letters at positions $ 1 $ and $ 4 $ to get spell "aaltnt".
- Swap the letters at positions $ 2 $ and $ 6 $ to get spell "atltna".



You are given spells $ s $ and $ t $ . Can Drahyrt change spell $ s $ to $ t $ ?

## 输入格式

The first line of input gives a single integer $ T $ ( $ 1 \le T \le 10^4 $ ) — the number of test cases in the test.

Descriptions of the test cases are follow.

The first line contains two integers $ n, k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ k = 3 $ ) — the length spells and the number $ k $ such that Drahyrt can change letters in a spell at a distance $ k $ or $ k+1 $ .

The second line gives spell $ s $ — a string of length $ n $ consisting of lowercase Latin letters.

The third line gives spell $ t $ — a string of length $ n $ consisting of lowercase Latin letters.

It is guaranteed that the sum of $ n $ values over all test cases does not exceed $ 2 \cdot 10^5 $ . Note that there is no limit on the sum of $ k $ values over all test cases.

## 输出格式

For each test case, output on a separate line "YES" if Drahyrt can change spell $ s $ to $ t $ and "NO" otherwise.

You can output the answer in any case (for example, lines "yEs", "yes", "Yes" and "YES" will be recognized as positive answer).

## 样例 #1

### 样例输入 #1

```
7
6 3
talant
atltna
7 3
abacaba
aaaabbc
12 3
abracadabraa
avadakedavra
5 3
accio
cicao
5 3
lumos
molus
4 3
uwjt
twju
4 3
kvpx
vxpk
```

### 样例输出 #1

```
YES
YES
NO
YES
NO
YES
NO
```

## 提示

The first example is explained in the condition.

In the second example we can proceed as follows:

- Swap the letters at positions $ 2 $ and $ 5 $ (distance $ 3 $ ), then we get the spell "aaacbba".
- Swap the letters at positions $ 4 $ and $ 7 $ (distance $ 3 $ ), then you get the spell "aaaabbc".

In the third example, we can show that it is impossible to get the string $ t $ from the string $ s $ by swapping the letters at a distance of $ 3 $ or $ 4 $ .

In the fourth example, for example, the following sequence of transformations is appropriate:

- "accio" $ \rightarrow $ "aocic" $ \rightarrow $ "cocia" $ \rightarrow $ "iocca" $ \rightarrow $ "aocci" $ \rightarrow $ "aicco" $ \rightarrow $ "cicao"

In the fifth example, you can show that it is impossible to get the string $ s $ from the string $ t $ .

In the sixth example, it is enough to swap the two outermost letters.

## 题解
我们注意到将 $s_{i}$ 向右移动 k 为在再向左移动 k 位，等价于向右移动 1 位，(也就是说，只要我们的移动位置在我们的字符串范围内，那么我们就可以把这个位置的字母进行任意的移动）所以当 $s_{1}[i]\neq s_{2}[i]$ 时，只要第 i 位可以交换，必然可以使得我们的 $s_{1}[i]=s_{2}[i]$,而 $s_{1}[i]$ 不能交换当且仅当 $i-k<0$ 且 $n\leq i+k$,



因此，我们只需要判断下面两个：
第一个：如果我们的 $s_{1}$ 和 $s_{2}$ 中出现的**字母种类或者个数不一样**，我们认为是不能实现的，我们直接输出一个 false。
第二个：如果相同，但是我们再后面的若干位，我们**不能操作**，并且这个位置需要更改：我们认为也是不能实现的，直接输出一个 false。

其他情况下，我们都是 true。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int t;
int vis1[30],vis2[30];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read(),k=read();
	string a,b;
	cin>>a>>b;
	memset(vis1,0,sizeof(vis1));
	memset(vis2,0,sizeof(vis2));
	for(int i=0;i<n;i++){
		vis1[a[i]-'a'+1]++;
		vis2[b[i]-'a'+1]++;
	}
	for(int i=1;i<=26;i++) {
		if(vis1[i]!=vis2[i]){//数量不同无法实现
			cout<<"NO"<<endl;
			return ;
		}
	}
	for(int i=0;i<n;i++){
	    if(i+k>=n&&i-k<0){//无法操作
	        if(a[i]!=b[i]){
	            cout<<"NO"<<endl;
	            return ;
	        }
	    }
	}
	cout<<"YES"<<endl;
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```