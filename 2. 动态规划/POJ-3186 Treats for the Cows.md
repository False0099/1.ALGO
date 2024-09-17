FJ has purchased N (1 <= N <= 2000) yummy treats for the cows who get money for giving vast amounts of milk. FJ sells one treat per day and wants to maximize the money he receives over a given period time.  
  
The treats are interesting for many reasons:

- The treats are numbered 1..N and stored sequentially in single file in a long box that is open at both ends. On any day, FJ can retrieve one treat from either end of his stash of treats.
- Like fine wines and delicious cheeses, the treats improve with age and command greater prices.
- The treats are not uniform: some are better and have higher intrinsic value. Treat i has value v(i) (1 <= v(i) <= 1000).
- Cows pay more for treats that have aged longer: a cow will pay v(i)*a for a treat of age a.

Given the values v(i) of each of the treats lined up in order of the index i in their box, what is the greatest value FJ can receive for them if he orders their sale optimally?  
  
The first treat is sold on day 1 and has age a=1. Each subsequent day increases the age by 1.

Input

Line 1: A single integer, N  
  
Lines 2..N+1: Line i+1 contains the value of treat v(i)

Output

Line 1: The maximum revenue FJ can achieve by selling the treats

Sample

|Inputcopy|Outputcopy|
|---|---|
|5<br>1<br>3<br>1<br>5<br>2|43|

Hint

Explanation of the sample:  
  
Five treats. On the first day FJ can sell either treat #1 (value 1) or treat #5 (value 2).  
  
FJ sells the treats (values 1, 3, 1, 5, 2) in the following order of indices: 1, 5, 2, 3, 4, making 1x1 + 2x2 + 3x3 + 4x1 + 5x5 = 43.

## 题解
我们原问题的划分应该有下面的思路：我们维护我们的双指针 i，j，我们的 $dp[i][j]$ 就表示我们的双指针在 $i,j$ 时，我们能获得的最大值是多少。于是我们的转移就可以写出
```cpp
1 #include<cstdio>
 2 #include<algorithm>
 3 using namespace std; 4 
 5 int n,res; 6 int a[2005],dp[2005][2005];
 7 
 8 int main(){ 9     scanf("%d",&n);
10     for(int i=1;i<=n;++i)
11         scanf("%d",&a[i]);
12     dp[1][n]=0;
13     for(int i=1;i<=n;++i)
14         for(int j=n;j>=i;--j){
15             if(i>1&&j<n)
```