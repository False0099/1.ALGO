## 题目
**easy 与 hard 的唯一区别是** $T$**,** $n$**, 以及字符集的范围。**

**easy, hard 是 EX 的子问题，若能通过 EX，在做简单修改后，必能通过 easy, hard。  
**

  
Tokitsukaze 在古老的遗迹中找到一张破旧的卷轴，上面写着的一串长度为 $n$ 的数字正是打开遗迹深处宝箱的密码。虽然卷轴上的一些数字已经模糊不清，但 Tokitsukaze 可以根据从世界各地打听到关于密码的情报来还原出真正的密码。令密码为整数 $x$，情报如下：  

-    情报 1. $x$ 没有前导 $0$。
-    情报 2. $x$ 是 $8$ 的倍数。
-    情报 3. Tokitsukaze 获得了另一个长度为 $n$ 的整数 $y$，密码 $x$ 满足 $x \leq y$。
-    情报 4. 在模糊不清的数字中，Tokitsukaze 知道其中一些数位上的数字是相同的，她会将这些数位使用小写字母标记出来，**标记着相同字母的数位上的数字一定相同，标记着不同字母的数位上的数字一定互不相同**；而另一些数字没有任何情报，它可能是 '0' 到 '9' 中的任意一个，这种数字 Tokitsukaze 会将它们用下划线 '\_' 标记出来。

  
下面是几个关于情报 4 的例子：  

-    ''1 aa'' 它可以是 ''100'', ''111'',...,''199''，但它不能是 ''123''，因为标记着相同字母的数位上的数字一定相同。
-    ''2 abc'' 它不能是 ''2119'', ''2191'', ''2222''。因为标记着不同字母的数位上的数字一定互不相同。
-    ''9 b\_b\_'' 它可以是 ''91010'', ''95355'', ''95555'' 等，用 '\_' 标记的数位上的数字没有任何限制。


  
现在 Tokitsukaze 想要根据已有情报暴力破解密码，她想尝试所有可能的密码。她告诉你标记后的字符串 $s$，以及整数 $y$，请你告诉她有多少种不同的密码。  
  
不同的密码数量可能特别多，请输出对 $10^9+7$ 取模后的结果。

## 输入：
第一行包含一个整数 $T$ ($1 \leq T \leq 100$)，表示 $T$ 组测试数据。  
  
对于每组测试数据：  
  
第一行包含一个整数 $n$ ($1 \leq n \leq 9$)，表示密码的长度。  
  
第二行包含一个长度为 $n$ 的字符串 $s$，仅包含 '0' 到 '9'， 'a', 'b', 'c', 'd' 以及 '\_'，并且**保证** **'****\_' 最多只会出现一次**。  
  
第三行包含一个长度为 $n$ 的非负整数 $y$，保证 $y$ 不包含前导 $0$。

## 输出：
对于每组测试数据，输出一个整数，表示不同的密码数量对 $10^9+7$ 取模后的结果。

## 样例：
输入

```
5
2
10
99
2
16
99
2
16
15
2
0a
10
2
bb
99
```

输出


````
0
1
0
0
1
````




说明



第一组测试数据：数字是确定的，但不符合情报2，所以答案是 $0$；  
  
第二组测试数据：数字是确定的，并且符合所有情报，所以答案是 $1$；  
  
第三组测试数据：数字是确定的，但不符合情报3，所以答案是 $0$；  
  
第四组测试数据：存在前导 $0$，不符合情报1，所以答案是 $0$；  
  
第五组测试数据：$00$ 存在前导 $0$ 不符合情报1，只有 $88$ 符合所有情报，所以答案是 $1$。  

## 题解
我们这一题只需要暴力进行我们的搜索即可完成，也就是按照我们的要求去进行我们的操作即可。
```cpp
```cpp
// NowCoder Tokitsukaze and Password (easy)
// https://ac.nowcoder.com/acm/contest/67742/K 2024-02-05 15:23:01

#include <bits/stdc++.h>
using namespace std;
#define all(a) begin(a), end(a)
#define int long long
string x, y;
int n, m;
int ans;
map<char, bool> mp;
map<string, bool> ttt;
void dfs(string s, int u, map<char, bool> mp) {
  if (u == n) {
    int val = atoi(s.c_str());
    int tt = atoi(y.c_str());
    if (s[0] >= '1' and val <= tt and ((val % 8) == 0)) {
      ans++;
    } else if (n == 1) {
      if (val <= tt and ((val % 8) == 0)) {
        ans++;
      }
    }
  } else {
    if (s[u] == '_') {
      string ss = s;
      for (char a = '0'; a <= '9'; a++) {
        ss[u] = a;
        dfs(ss, u + 1, mp);
      }
    } else if (s[u] <= 'z' and s[u] >= 'a') {
      for (char a = '0'; a <= '9'; a++) {
        string ss = s;
        if (mp[a] == true)
          continue;
        else {
          for (int i = 0; i < n; i++) {
            if (ss[i] == s[u]) ss[i] = a;
          }
          mp[a] = true;
          dfs(ss, u + 1, mp);
          mp[a] = false;
        }
      }
    } else
      dfs(s, u + 1, mp);
  }
}
void solve() {
  ans = 0;
  cin >> n;
  cin >> x >> y;
  dfs(x, 0, mp);
  ans %= (int)(1e9 + 7);
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cout << fixed << setprecision(15);
  int __;
  cin >> __;
  while (__--) solve();
  return 0;
}
```
```