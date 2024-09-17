# 知识点
  ## [[双指针]] [[求最值]] [[二分答案]]
# 题目
塔沃节快到了，Libra 和 Rahn 决定享用家乡的传统美食：烤兔头。  
  
桌上有 nnn 盘烤兔头排成一排，从左到右编号 1∼n1\sim n1∼n，第 iii 个盘子里有 aia_iai​ 个烤兔头。经过商量，Libra 和 Rahn 决定各自从桌子的两端同时开始吃烤兔头，Libra 从左往右吃，Rahn 从右往左吃，两人吃兔头的速度相等，且都会先将当前的盘子内的烤兔头吃完后再吃下一盘，吃完的盘子会被后勤立刻撤走。由于 Libra 和 Rahn 还邀请了一些好友来品尝美食，所以当两人吃完一个烤兔头后发现桌下只剩下 ≤k\le k≤k **盘**烤兔头时会同时停止，剩余的烤兔头等好友们赴宴后再共同享用。  
  
晚宴正在筹备的过程中，而 Libra 已经迫不及待的想要知道自己能吃多少烤兔头。你能帮 Libra 算出她能够吃到多少烤兔头吗？

# 思路
· ![[Pasted image 20230416195540.png]]
·第二种思路是去二分答案，这样保证时间复杂度是 $o（logn）$
·
# AC 代码
```cpp
#include <iostream>
#include <vector>
using ll = long long;

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<int> v(n + 1);
        for (int i = 1; i <= n; i++) cin >> v[i];
        int l = 1, r = n;
        ll res = 0;
        while (r - l >= k) {
            if (v[l] == v[r]) {
                res += v[l];
                l++, r--;
            }
            else if (v[l] < v[r]) {
                v[r] -= v[l];
                res += v[l];
                l++;
            }
            else {
                v[l] -= v[r];
                res += v[r];
                r--;
            }
        }
        cout << res << endl;
    }
}
```
# 备注

