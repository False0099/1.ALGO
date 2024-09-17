# Running Miles

## 题面翻译

给定一个长度为 $n$ 的数列 $a$，请找出其中的一个区间 $[l,r]$，最大化区间内的前三大值之和与 $r-l$ 的差，并求出这个值。

## 题目描述

There is a street with $ n $ sights, with sight number $ i $ being $ i $ miles from the beginning of the street. Sight number $ i $ has beauty $ b_i $ . You want to start your morning jog $ l $ miles and end it $ r $ miles from the beginning of the street. By the time you run, you will see sights you run by (including sights at $ l $ and $ r $ miles from the start). You are interested in the $ 3 $ most beautiful sights along your jog, but every mile you run, you get more and more tired.

So choose $ l $ and $ r $ , such that there are at least $ 3 $ sights you run by, and the sum of beauties of the $ 3 $ most beautiful sights minus the distance in miles you have to run is maximized. More formally, choose $ l $ and $ r $ , such that $ b_{i_1} + b_{i_2} + b_{i_3} - (r - l) $ is maximum possible, where $ i_1, i_2, i_3 $ are the indices of the three maximum elements in range $ [l, r] $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 3 \leq n \leq 10^5 $ ).

The second line of each test case contains $ n $ integers $ b_i $ ( $ 1 \leq b_i \leq 10^8 $ ) — beauties of sights $ i $ miles from the beginning of the street.

It's guaranteed that the sum of all $ n $ does not exceed $ 10^5 $ .

## 输出格式

For each test case output a single integer equal to the maximum value $ b_{i_1} + b_{i_2} + b_{i_3} - (r - l) $ for some running range $ [l, r] $ .

## 样例 #1

### 样例输入 #1

```
4
5
5 1 4 2 3
4
1 1 1 1
6
9 8 7 6 5 4
7
100000000 1 100000000 1 100000000 1 100000000
```

### 样例输出 #1

```
8
1
22
299999996
```

## 提示

In the first example, we can choose $ l $ and $ r $ to be $ 1 $ and $ 5 $ . So we visit all the sights and the three sights with the maximum beauty are the sights with indices $ 1 $ , $ 3 $ , and $ 5 $ with beauties $ 5 $ , $ 4 $ , and $ 3 $ , respectively. So the total value is $ 5 + 4 + 3 - (5 - 1) = 8 $ .

In the second example, the range $ [l, r] $ can be $ [1, 3] $ or $ [2, 4] $ , the total value is $ 1 + 1 + 1 - (3 - 1) = 1 $ .

## 题解
首先，我们这一题是一定可以用我们的 dp 来解决的，我们设 $dp[i][k]$ 为我们在 i 之前，走了一共 k 段，其中我们获得的最大价值是多少。

```cpp
1. #include<bits/stdc++.h>
2. using namespace std;
3. #define isDigit(ch) ('0'<=ch&&ch<='9')
4. #define i64 long long
5. inline i64 rd()
6. {
7. i64 num=0;char ch=getchar();bool opt=0;
8. for(;!isDigit(ch);ch=getchar())
9. if(ch=='-')opt=1;
10. for(;isDigit(ch);ch=getchar())
11. num=num*10+(ch-'0');
12. return opt?-num:num;
13. }
14. inline void pYes(bool ans){ans?printf("Yes\n"):printf("No\n");}
15. inline void Max(int &x,int y){x=max(x,y);}
16. const int N=1e5+10,M=1e5+10;
17. const int inf=1e9;
18. int n;
19. int a[N];
20. int F[3][N];

22. int Ans=0;

24. inline int work()
25. {
26. Ans=0;
27. n=rd();for(int i=1;i<=n;i++)a[i]=rd();
28. for(int i=0;i<=n;i++)F[0][i]=F[1][i]=F[2][i]=-inf;
29. for(int i=1;i<=n;i++)F[0][i]=a[i],Max(F[0][i],F[0][i-1]-1);
30. for(int x=1;x<=2;x++)
31. for(int i=1;i<=n;i++)
32. F[x][i]=max(F[x][i-1]-1,F[x-1][i-1]+a[i]-1);
33. for(int i=1;i<=n;i++)Max(Ans,F[2][i]);
34. printf("%d\n",Ans);
35. return 0;
36. }

38. int main(){int test=rd();while(test--)work();return 0;}
```