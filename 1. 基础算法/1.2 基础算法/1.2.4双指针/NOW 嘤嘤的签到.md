# 知识点
  ## [[滑动窗口]]
# 题目
        嘤嘤突然发现，今天好像是一个攻击性很强的日子，除此之外，下个月的今天和上上上个月的今天都是很臭的日子，上上个月的今天又是小木曾雪菜的生日，上个月的今天还是 π 节。

  

        世界名画——《你为什么这么熟练啊！》（妮露（左），神里绫华（中），荧（右））（图片加载失败）  

  

        在op414、哼哼啊啊啊、届不到、高等(su)数(tui)学的轮番刺激下，嘤嘤已经对同时出现1、4这两个数字的数字串PTSD了，嘤嘤嘤！

  

        给定一个数字串，问有多少个连续子串不会让嘤嘤PTSD。

# 思路
·我们其实是有办法想到要用滑动窗口的，因为一旦这一个不满足性质，下一个也一定不会满足性质，我们只需要这之后移动前一个就行了
·还有一个问题点在于最后的长度要怎么判断，这个我们只需要知道满足条件的区间的长度，然后这个区间的长度就是一共的个数。（为什么不会漏？）因为这里前一个指针会随时变化，所以我们算的是不会漏也不会重复的
（怎么判断单个的情况）
·
# AC 代码
```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector> 
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <cstdlib>
using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    std::vector<int> cnt(10);    
    
    i64 ans = 0;
    int i = 0, j = 0;
    for (i = 0, j = 0; i < n; i++) {
        cnt[s[i] - '0']++;//更有通用性的一种写法
        while (cnt[1] > 0 && cnt[4] > 0（check）) {//如果
            cnt[s[j] - '0']--;
            j++;
        }
        ans += i - j + 1;
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    solve();
    
    return 0;
}
```
# 备注
