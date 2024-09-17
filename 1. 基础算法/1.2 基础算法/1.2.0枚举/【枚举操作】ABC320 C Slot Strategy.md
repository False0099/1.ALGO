C - Slot Strategy 2 (Easy) 
---

Time Limit: 2 sec / Memory Limit: 1024 MB

Score : 300300 points

### Problem Statement

> This problem is an easier version of Problem G.

There is a slot machine with three reels.  
The arrangement of symbols on the i-th reel is represented by the string Si​. Here, Si​ is a string of length M consisting of digits.

Each reel has a corresponding button. For each non-negative integer t, Takahashi can either choose and press one button or do nothing exactly t seconds after the reels start spinning.  
If he presses the button corresponding to the i-th reel exactly t seconds after the reels start spinning, the i-th reel will stop and display the (((tmodM)+1)-th character of Si​.  
Here, tmodM denotes the remainder when t is divided by M.

Takahashi wants to stop all the reels so that all the displayed characters are the same.  
Find the minimum possible number of seconds from the start of the spin until all the reels are stopped so that his goal is achieved.  
If this is impossible, report that fact.

### Constraints

- 1≤M≤100
- M is an integer.
- Si​ is a string of length M consisting of digits.

---

### Input

The input is given from Standard Input in the following format:

M
1S1​
2S2​
3S3​

### Output

If it is impossible to stop all the reels so that all the displayed characters are the same, print `-1`.  
Otherwise, print the minimum possible number of seconds from the start of the spin until such a state is achieved.

---

### Sample Input 1Copy

Copy

10
1937458062
8124690357
2385760149

### Sample Output 1Copy

Copy

6

Takahashi can stop each reel as follows so that 66 seconds after the reels start spinning, all the reels display `8`.

- Press the button corresponding to the second reel 00 seconds after the reels start spinning. The second reel stops and displays `8`, the ((010)+1=1)((0mod10)+1=1)-st character of S2​.
- Press the button corresponding to the third reel 22 seconds after the reels start spinning. The third reel stops and displays `8`, the ((210)+1=3)((2mod10)+1=3)-rd character of S3​.
- Press the button corresponding to the first reel 66 seconds after the reels start spinning. The first reel stops and displays `8`, the ((610)+1=7)((6mod10)+1=7)-th character of S1​.

There is no way to make the reels display the same character in 55 or fewer seconds, so print 66.

---

### Sample Input 2Copy

Copy

20
01234567890123456789
01234567890123456789
01234567890123456789

### Sample Output 2Copy

Copy

20

Note that he must stop all the reels and make them display the same character.

---

### Sample Input 3Copy

Copy

5
11111
22222
33333

### Sample Output 3Copy

Copy

-1

It is impossible to stop the reels so that all the displayed characters are the same.  
In this case, print `-1`.


## 题解
我们发现，我们的的**旋转是具有周期性的**，并且由于我们只能依次确定我们的顺序，我们的周期就一定是 $3T$，如果我们在旋转三周后再找到匹配的数字，我们就永远都不能找到他了，因此，我们只需要三倍倍长我们的每个车轮上的字母，然后再对我们的三个车轮进行匹配即可。要求我们
1. 位置不相同
2. 我们的字母全相同
3. 答案取所有**最大位置中的最小**一个。

```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
#define rep(i, n) for (int i = 0; i < n; i++)

int main() {
	int m;
	cin >> m;
	vector<string> s(3);
	rep(i, 3) cin >> s[i];

	const int INF = 1001001001;
	int ans = INF;
	rep(t0, 300)rep(t1, 300)rep(t2, 300) {
		if (t0 == t1) continue;
		if (t0 == t2) continue;
		if (t1 == t2) continue;
		if (s[0][t0 % m] != s[1][t1 % m]) continue;
		if (s[0][t0 % m] != s[2][t2 % m]) continue;
		ans = min(ans, max({ t0, t1, t2 }));
	}
	if (ans == INF) ans = -1;
	cout << ans << endl;
}
```


