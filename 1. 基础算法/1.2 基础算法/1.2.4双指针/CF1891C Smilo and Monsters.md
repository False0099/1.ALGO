A boy called Smilo is playing a new game! In the game, there are $n$ hordes of monsters, and the $i$ \-th horde contains $a_i$ monsters. The goal of the game is to destroy all the monsters. To do this, you have two types of attacks and a combo counter $x$, initially set to $0$:



-   The first type: you choose a number $i$ from $1$ to $n$, such that there is at least one monster left in the horde with the number $i$. Then, you kill one monster from horde number $i$, and the combo counter $x$ increases by $1$.
-   The second type: you choose a number $i$ from $1$ to $n$, such that there are at least $x$ monsters left in the horde with number $i$. Then, you use an ultimate attack and kill $x$ monsters from the horde with number $i$. After that, $x$ is reset to zero.

Your task is to destroy all of the monsters, meaning that there should be no monsters left in any of the hordes. Smilo wants to win as quickly as possible, so he wants to the minimum number of attacks required to win the game.

**Input**

The first line contains a single integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases. The descriptions of the test cases follow.

The first line of each input data set contains a single integer $n$ ($1 \leq n \leq 2 \cdot 10^5$) — the number of hordes of monsters.

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \leq a_i \leq 10^9$) — the number of monsters in each horde.

It is guaranteed that the sum of $n$ across all test cases does not exceed $2 \cdot {10^5}$.

**Output**

For each test case, out put the minimum number of attacks required to kill all monsters.


## 题解
我们这一题的思路就是先将我们的数组排序，我们优先打我们数量较少的那一组，然后我们在把我们的大招拿去打我们目前比较多的那一组。然而，对于这一类题目，我们有一种思路：我们计算如果我们全部都用我们的第一类攻击，我们能有多少剩余，然后再计算每一次大招对于我们答案的贡献是多少。

```cpp
1. #include<bits/stdc++.h>
2. using namespace std;
3. #define pii pair<int, int>
4. #define pdd pair<double, double>
5. typedef long long ll;
6. //long long !
7. inline void solve()
8. {
9. int n;
10. cin >> n;
11. vector<ll> a(n+5);
12. ll res = 0;
13. for(int i=1; i<=n; i++)
14. cin >> a[i], res += a[i];
15. ll sum = 0;
16. //cout << res << endl;
17. sort(a.begin()+1, a.begin()+1+n);
18. int i, j;
19. for(i=1, j=n; i<j; i++)
20. {
21. sum += a[i];
22. if(sum >= a[j])
23. {
24. sum -= a[j];
25. res -= a[j] - 1;
26. //cout << a[j-1] << endl;
27. j --;
28. }
29. }
30. if(i == j) sum += a[j];
31. res -= max(sum/2-1ll, 0ll);
32. cout << res << endl;
33. }
34. int main()
35. {
36. int t;
37. cin >> t;
38. while(t--)
39. solve();
40. return 0;
41. }
```