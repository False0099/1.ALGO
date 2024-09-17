Vasya is a sorcerer that fights monsters. Again. There are $n$ monsters standing in a row, the amount of health points of the $i$ \-th monster is $a_i$.

Vasya is a very powerful sorcerer who knows many overpowered spells. In this fight, he decided to use a chain lightning spell to defeat all the monsters. Let's see how this spell works.

Firstly, Vasya chooses an index $i$ of some monster ($1 \le i \le n$) and the initial power of the spell $x$. Then the spell hits monsters **exactly** $n$ times, one hit per monster. The first target of the spell is always the monster $i$. For every target **except for the first one**, the chain lightning will choose a **random** monster **who was not hit by the spell and is adjacent to one of the monsters that already was hit**. So, each monster will be hit exactly once. The first monster hit by the spell receives $x$ damage, the second monster receives $(x-1)$ damage, the third receives $(x-2)$ damage, and so on.

Vasya wants to show how powerful he is, so he wants to kill all the monsters with a single chain lightning spell. The monster is considered dead if the damage he received is not less than the amount of its health points. On the other hand, Vasya wants to show he doesn't care that much, so he wants to choose the **minimum** initial power of the spell $x$ such that it kills all monsters, **no matter which monster (among those who can get hit) gets hit on each step**.

Of course, Vasya is a sorcerer, but the amount of calculations required to determine the optimal spell setup is way above his possibilities, so you have to help him find the minimum spell power required to kill all the monsters.

Note that Vasya chooses the initial target and the power of the spell, other things should be considered random and Vasya wants to kill all the monsters even in the worst possible scenario.

**Input**

The first line of the input contains one integer $n$ ($1 \le n \le 3 \cdot 10^5$) — the number of monsters.

The second line of the input contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 10^9$), where $a_i$ is the amount of health points of the $i$ \-th monster.

**Output**

Print one integer — the minimum spell power required to kill all the monsters if Vasya chooses the first target optimally, and the order of spell hits can be any possible within the given rules.


## 题解
我们这一题因为我们的每一个操作的性质不是很明显，我们考虑我们在每一个位置释放闪电所需要的最大的初始值是多少，我们经过手玩之后，可以发现，我们的初始值应该是我们的 $max(a[i],max_{j=1}^ia[j]+(n-i),max_{j=i}^na[j]+i)$,然后，我们就可以通过预处理我们的前缀后缀最大值，然后就可以进行我们的 $o(n)$ 计算。

```cpp
    #include <bits/stdc++.h>
     
    using namespace std;
     
    int main() {
    #ifdef _DEBUG
        freopen("input.txt", "r", stdin);
    //  freopen("output.txt", "w", stdout);
    #endif
        
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &it : a) cin >> it;
        
        vector<int> pref(n), suf(n);
        for (int i = 0; i < n; ++i) {
            pref[i] = a[i] + (n - i - 1);
            suf[i] = a[i] + i;
        }
        for (int i = 1; i < n; ++i) {
            pref[i] = max(pref[i], pref[i - 1]);
        }
        for (int i = n - 2; i >= 0; --i) {
            suf[i] = max(suf[i], suf[i + 1]);
        }
        
        int ans = 2e9;
        for (int i = 0; i < n; ++i) {
            int cur = a[i];
            if (i > 0) cur = max(cur, pref[i - 1]);
            if (i + 1 < n) cur = max(cur, suf[i + 1]);
            ans = min(ans, cur);
        }
        
        cout << ans << endl;
        
        return 0;
    }
```
