# Stripe

## 题面翻译

给定一整数 n，下面有 n 个数 a[i]，求将该数列分割成两个非空数列且两个数列内数字的和相等的方案数
1<=n<=10^5
A[i]的绝对值不大于 10000

Translated by 稀神探女

## 题目描述

Once Bob took a paper stripe of $ n $ squares (the height of the stripe is 1 square). In each square he wrote an integer number, possibly negative. He became interested in how many ways exist to cut this stripe into two pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece, and each piece contains positive integer amount of squares. Would you help Bob solve this problem?

## 输入格式

The first input line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of squares in the stripe. The second line contains $ n $ space-separated numbers — they are the numbers written in the squares of the stripe. These numbers are integer and do not exceed 10000 in absolute value.

## 输出格式

Output the amount of ways to cut the stripe into two non-empty pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece. Don't forget that it's allowed to cut the stripe along the squares' borders only.

## 样例 #1

### 样例输入 #1

```
9
1 5 -6 7 9 -16 0 -2 2
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
3
1 1 1
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
2
0 0
```

### 样例输出 #3

```
1
```

## 题解
因为我们是要求分成两端完全相同，因此我们可以采用我们的前缀和，找到我们的某一个点满足我们的 $s[i]+s[i]=s[n]$
的所有的 i，然后我们进行一个计数即可。

```cpp
#include<iostream>
using namespace std;

int n,a[100010],s[100010];//s为记录前缀和的数组

int ans;//记录答案

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }//读入+统计前缀和
    for(int i=1;i<=n-1;i++){
        if(s[i]==s[n]-s[i])//比较两个区间的和是否一样
            ans++;//如果一样，答案++
    }
    cout<<ans<<endl;//输出答案
    return 0;//完结撒花！
}
```