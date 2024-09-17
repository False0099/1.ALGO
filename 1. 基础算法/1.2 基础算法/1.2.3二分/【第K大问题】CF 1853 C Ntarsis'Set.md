#构造 #逆向思维 #二分
Ntarsis has been given a set $S$, initially containing integers $1, 2, 3, \ldots, 10^{1000}$ in sorted order. Every day, he will remove the $a_1$ \-th, $a_2$ \-th, $\ldots$, $a_n$ \-th smallest numbers in $S$ **simultaneously**.

What is the smallest element in $S$ after $k$ days?

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case consists of two integers $n$ and $k$ ($1 \leq n,k \leq 2 \cdot 10^5$) — the length of $a$ and the number of days.

The following line of each test case consists of $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \leq a_i \leq 10^9$) — the elements of array $a$.

It is guaranteed that:

-   The sum of $n$ over all test cases won't exceed $2 \cdot 10^5$;
-   The sum of $k$ over all test cases won't exceed $2 \cdot 10^5$;
-   $a_1 lt; a_2 lt; \cdots lt; a_n$ for all test cases.

**Output**

For each test case, print an integer that is the smallest element in $S$ after $k$ days.


## 题解
本题我们需要通过枚举答案来确定我们在经过了 k 次操作后，排名是多少。
我们可以通过下面的方式检查：
我们记我们这个数字的初始排名为 $rk$,我们每一次操作，需要在我们的所有数字中，找到比我们 $rk$ 小的数字的个数，然后把我们的这个 $rk$ 减去我们的个数。依次类推，如果经过 k 次操作后我们已经小于等于了，我们就让 r 左移，否则让我们的 l 右移

```cpp
1. #include <bits/stdc++.h>
2. using namespace std;
3. void solve()
4. {
5. long long n, k;
6. cin >> n >> k;
7. vector<int> a(n);
8. for (int i = 0; i < n; i++)
9. {
10. cin >> a[i];
11. }
12. long long ans = 1, idx = 0;
13. while (k--)
14. {
15. ans += idx;
16. while (idx < n && a[idx] <= ans)
17. {
18. idx++;
19. ans++;
20. }
21. }
22. cout << ans << endl;
23. }
24. int main()
25. {
26. ios::sync_with_stdio(false);
27. cin.tie(0);
28. int t;
29. cin >> t;
30. while (t--)
31. {
32. solve();
33. }
34. return 0;
35. }
```

