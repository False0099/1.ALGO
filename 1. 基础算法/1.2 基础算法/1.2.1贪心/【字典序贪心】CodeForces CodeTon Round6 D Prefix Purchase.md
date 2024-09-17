## 题目
You have an array a of size n, initially filled with zeros (a1=a2=…=an=0=). You also have an array of integers c of size n.

Initially, you have k coins. By paying ci coins, you can add 1 to all elements of the array a from the first to the i-th element (aj+=1 for all 1≤j≤i). You can buy any ci any number of times. A purchase is only possible if k≥ci, meaning that at any moment k≥0 must hold true.

Find the lexicographically largest array a that can be obtained.

An array a is lexicographically smaller than an array b of the same length if and only if in the first position where a and b differ, the element in array a is smaller than the corresponding element in b.

## Input

The first line contains a single integer t (1≤t≤104) — the number of test cases. This is followed by a description of the test cases.

The first line of each test case contains a single integer n (1≤n≤2⋅105) — the size of arrays a and c.

The second line of each test case contains n integers c1,c2,…,cn (1≤ci≤109) — the array c.

The third line of each test case contains a single integer k (1≤k≤109) — the number of coins you have.

It is guaranteed that the sum of all n values across all test cases does not exceed 2⋅105

## Output

For each test case, output n integers a1,a2,…,an — the lexicographically largest array a that can be obtained.

## 题解
首先，对于每一个位置，如果他的后面有比他更小的，那么我们这个位置可以完全不考虑，我们只需要用在他后面的比他更小的哪一个即可。这就引诱我们使用**最小后缀和**即可。我们就把我们**每一个点的权值换成这个位置之后的，最小的数字即可**
我们处理出来每一个位置的最小后缀和后，我们就可以贪心的处理这个问题，我们想要首先最大化第一个元素，这**个元素所能最大达到的大小**，就是我们的 $\frac{k}{c_{1}}$,之后，之后，我们可能会有一些剩余，所以我们现在可以**把某些 $c_{1}$ 中的购买给替换成后面的，来更大化我们的值**。那么我们每一次把一个 $c_{1}$ 替换成后面的 $c_{i}$ 需要花费多少呢？答案显然是 $c_{i}-c_{1}$ 个硬币。但是，我们可**以通过把连续操作**改成**相邻操作**的想法（类似于我们的股票买卖 dp），把区间问题，转换为连续两个数之间的转换。于是，我们只需要**贪心相邻两个数即可**

现在，假设我们已经最大化了前 i-1 个元素，我们还剩下 x 个，我们想要用我们的一些来替换我们的后面的元素，我们可以替换多少次，我们的替换次数不超过 $\frac{x}{c_{i}-c_{i-1}}$。于是，我们就可以用我们的


```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    for (int i = n - 2; i >= 0; i--) {
        c[i] = std::min(c[i], c[i + 1]);//处理我们的最小后缀
    }
    
    int k;
    std::cin >> k;
    
    std::vector<int> a(n);
    int t = k;
    for (int i = 0; i < n; i++) {
        int v = c[i] - (i ? c[i - 1] : 0);//这个是我们把这一个位置最大化需要的花费
        if (v > 0) {
            t = std::min(t, k / v);//我们让这个位置获得一个最大所需要的代价。
        }
        k -= t * v;//我们剩下多少钱
        a[i] = t;//这个位置是多少
        std::cout << a[i] << " \n"[i == n - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
```

