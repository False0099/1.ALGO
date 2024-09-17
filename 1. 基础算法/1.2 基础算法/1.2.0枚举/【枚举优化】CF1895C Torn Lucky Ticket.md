# Torn Lucky Ticket

## 题目描述

A ticket is a non-empty string of digits from $ 1 $ to $ 9 $ .

A lucky ticket is such a ticket that:

- It has an even length;
- The sum of digits in the first half is equal to the sum of digits in the second half.

You are given $n$ ticket pieces $s_1, s_2, \dots, s_n$ . How many pairs $(i, j)$ (for $1 \le i, j \le n$ ) are there such that $s_i + s_j$ is a lucky ticket? Note that it's possible that $i=j$ .

Here, the + operator denotes the concatenation of the two strings. For example, if $ s_i $ is 13, and $ s_j $ is 37, then $ s_i + s_j $ is 1337.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of ticket pieces.

The second line contains $ n $ non-empty strings $ s_1, s_2, \dots, s_n $ , each of length at most $ 5 $ and consisting only of digits from $ 1 $ to $ 9 $ .

## 输出格式

Print a single integer — the number of pairs $ (i, j) $ (for $ 1 \le i, j \le n $ ) such that $ s_i + s_j $ is a lucky ticket.

## 样例 #1

### 样例输入 #1

```
10
5 93746 59 3746 593 746 5937 46 59374 6
```

### 样例输出 #1

```
20
```

## 样例 #2

### 样例输入 #2

```
5
2 22 222 2222 22222
```

### 样例输出 #2

```
13
```

## 样例 #3

### 样例输入 #3

```
3
1 1 1
```

### 样例输出 #3

```
9
```


## 题解
我们这一题，可以考虑我们每一位的贡献，然后我们就来计算我们的总长度是多少，这里我们就可以用我们的 map 统计我们长为 k，和为 v 的数量有多少，然后我们就可以用我们的 map 来计算了。

另外要注意的一点是，我们需要分我们的前 k 个和后 k 个，因为我们的 6+2, 此时我们就需要我们的前 2 位的和和我们后 6 位的后 4 位

如果是我们的 6+8, 此时我们就要计算我们的 7+(6+1)的和
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  vector<string> s(n);
  map<pair<int, int>, int> count;
  i64 ans = 0;
  for (auto& si : s) {
    cin >> si;
    int sum = 0, len = ssize(si);
    for (char c : si) { sum += c - '0'; }
    ans += count[{len, sum}];//统计同长度聚合的贡献 
    count[{len, sum}] += 1;
  }
  ans = ans * 2 + n;//两倍自身，再加上自我聚合 
  for (auto si : s) {
    int m = si.size();//获得字符串长度
	//先枚举我们的前面k个聚合的长度 
    for (int i = 1; i * 2 < m; i += 1) {
      int diff = 0, mid = 0, len = m - 2 * i;
      //diff表示我们前后的差
	  //mid表示我们的
	  //len表示我们合成道具的后缀长度 
      for (int j = 0; j < m; j += 1) {//对我们的所有子串长度来说 
        if (j < i) {
          diff += si[j] - '0';
        } else if (j >= m - i) {
          diff -= si[j] - '0';
        } else {
          mid += si[j] - '0';
        }
      }
      ans += count[{len, mid + diff}];
      ans += count[{len, mid - diff}];
    }
  }
  cout << ans;
}

```