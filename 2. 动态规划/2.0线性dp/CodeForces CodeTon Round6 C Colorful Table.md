You are given two integers n and k. You are also given an array of integers a1,a2,…,an of size n. It is known that for all 1≤i≤n, 1≤ai≤k1.

Define a two-dimensional array b of size n×nas follows: bi,j=min(ai,aj)
、. Represent array b as a square, where the upper left cell is b1,1, rows are numbered from top to bottom from 1 to n, and columns are numbered from left to right from 1 to n. Let the color of a cell be the number written in it (for a cell with coordinates (i,j), this is bi,j.

For each color from 1 to k, find the smallest rectangle in the array b containing all cells of this color. Output the sum of width and height of this rectangle.

Input

The first line contains a single integer t (1≤t≤104) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains two integers n and k (1≤n,k≤105) — the size of array a and the number of colors.

The second line of each test case contains n integers a1,a2,…,an (1≤ai≤k) — the array a.

It is guaranteed that the sum of the values of n and k over all test cases does not exceed 105.

Output

For each test case, output k numbers: the sums of width and height of the smallest rectangle containing all cells of a color, for each color from 1 to k.

Example

input

Copy

5

2 1

1 1

2 2

1 2

3 5

3 2 4

4 2

1 2 1 2

5 3

1 2 3 2 1

output

Copy

4 
4 2 
0 6 6 2 0 
8 6 
10 6 2 

Note

In the first test case, the entire array b consists of color 11, so the smallest rectangle for color 11 has a size of 2×22×2, and the sum of its sides is 44.

In the second test case, the array b looks like this:

|     |     |
| --- | --- |
| 1   | 1   |
| 1   | 2   |

One of the corner cells has color 22, and the other three cells have color 11. Therefore, the smallest rectangle for color 11 has a size of 2×22×2, and for color 22 it is 1×11×1.

In the last test case, the array b looks like this:

|     |     |     |     |     |
| --- | --- | --- | --- | --- |
| 1   | 1   | 1   | 1   | 1   |
| 1   | 2   | 2   | 2   | 1   |
| 1   | 2   | 3   | 2   | 1   |
| 1   | 2   | 2   | 2   | 1   |
| 1   | 1   | 1   | 1   | 1   |


## 题解
我们对于每一个数字，他能出现的长度，就是在这个数前面比他大的第一个数和在她后面，比它大的最后一个数，两个数之间的差+1 就是我们的最大边长。我们发现，每一个数的出现，**只和他第一次出现和最后一次出现的位置有关**。于是，我们就可以设置一个数组 $s_{1}[i]，s_{2}[i]$ 表示，**比 i 这个数大的数**在我们**最左侧**出现的位置，和**比 i 这个数大的数**在我们**最右侧**出现的位置。

那么我们就可以推导出下面的转移方程

$s_{1}[i]=min(s_{1}[i],s_{1}[i+1])$
$s_{2}[i]=max(s_{2}[i],s_{2}[i+1])$
![[无标题 2.png]]
我们的初始值
$s_{1}[i]=i出现的最左端的位置$
$s_{2}[i]=i出现的最右端的位置$

```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    std::vector<int> l(k, n), r(k, -1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
        l[a[i]] = std::min(l[a[i]], i);
        r[a[i]] = i;
    }
    auto sl = l, sr = r;//把我们左端初始化为这个数字的第一次出现
    for (int i = k - 2; i >= 0; i--) {
        sl[i] = std::min(sl[i], sl[i + 1]);
        sr[i] = std::max(sr[i], sr[i + 1]);
    }
    for (int i = 0; i < k; i++) {
        if (l[i] > r[i]) {
            std::cout << 0;
        } else {
            std::cout << 2 * (sr[i] - sl[i] + 1);
        }
        std::cout << " \n"[i == k - 1];
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