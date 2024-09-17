#特殊要求 #构造元素
# Splitting the Uniqueness

## 题面翻译

题目大意：给定 n 个互不相同的非负整数数列 s。构造两个非负整数数列 a 与 b。使得 ai+bi=si。满足 a 与 b 都近似不同。一个数列 S 被称为近似不同当且仅当可以移去不超过 S/3 上取整后互不相同。（例如 4 就是移去 2 个数） n<=100000,0<=si<=10^9。

## 题目描述

Polar bears like unique arrays — that is, arrays without repeated elements.

 You have got a unique array $ s $ with length $ n $ containing non-negative integers. Since you are good friends with Alice and Bob, you decide to split the array in two. Precisely, you need to construct two arrays $ a $ and $ b $ that are also of length $ n $ , with the following conditions for all $ i $ $ (1<=i<=n) $ :

- $ a_{i}, b_{i} $ are non-negative integers;
- $ s_{i}=a_{i}+b_{i} $ .

Ideally, $ a $ and $ b $ should also be unique arrays. However, life in the Arctic is hard and this is not always possible. Fortunately, Alice and Bob are still happy if their arrays are almost unique. We define an array of length $ n $ to be almost unique, if and only if it can be turned into a unique array by removing no more than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297C/c5d8ea1c11ba761a920db324eef984cdbae28ef7.png) entries.

For example, the array $ [1,2,1,3,2] $ is almost unique because after removing the first two entries, it becomes $ [1,3,2] $ . The array $ [1,2,1,3,1,2] $ is not almost unique because we need to remove at least $ 3 $ entries to turn it into a unique array.

So, your task is to split the given unique array $ s $ into two almost unique arrays $ a $ and $ b $ .

## 输入格式

The first line of the input contains integer $ n $ $ (1<=n<=10^{5}) $ .

The second line contains $ n $ distinct integers $ s_{1}, s_{2},...\ s_{n} $ $ (0<=s_{i}<=10^{9}) $ .



## 输出格式

If it is possible to make Alice and Bob happy (if you can split the given array), print "YES" (without quotes) in the first line. In the second line, print the array $ a $ . In the third line, print the array $ b $ . There may be more than one solution. Any of them will be accepted.

If it is impossible to split $ s $ into almost unique arrays $ a $ and $ b $ , print "NO" (without quotes) in the first line.

## 样例 #1

### 样例输入 #1

```
6
12 5 8 3 11 9
```

### 样例输出 #1

```
YES
6 2 6 0 2 4
6 3 2 3 9 5
```

## 提示

In the sample, we can remove the first two entries from $ a $ and the second entry from $ b $ to make them both unique.

## 题解
我们这一题即把 a 数组分割成两个数组 b 和 c，满足 b+c=a; 要求我们至少有 $\frac{2n}{3}$ 个数不同，其中，我们的红色代表 b，蓝色代表 c。 
![[Pasted image 20230912130606.png]]

我们分成三段考虑问题，我们的目标是让至多 $\frac{s}{3}(下取整)$ 个数重复，我们就看也 i 按照如下的方法构造：
将 $s[i]$ 按照数值大小排序后，设 k= $\frac{s}{3}(上取整)$，对于第一段，我们构造 $a[i]=i-1,b[i]=s[i]-a[i]$;对于第二段，我们构造 $b_{i}=i-1,a_{i}=s[i]-b[i]$,对于第三段，我们构造 $b_{i}=n-i,a_{i}=s[i]-b[i]$

这样构造，我们就能发现，b 的第一段和 b 的第三段一定是不同的，c 的第二段和第三段一定是不同的。·

| 第一部分 | 第二部分 | 第三部分 |
| ---------------- | ----------------- | ------------------ |
| 1，2，3，4....   | $a_i-c_i$           | $a_i-c_i$           |
| $a_i-c_i$          | $1/3 n+1.....$      | $3/n....... 1$       |

我们可以证明 $a_{i}-c_{i}$ 再第二部分 $a_{i}$ 是递增的，$c_{i}$ 是递减的，所以一定是递增的，并且在第三部分一定是递增的，并且我们的边界一定是比我们的第二部分的最大值还要大，所以我们一定能

```cpp
```cpp

#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 100005
struct node{
    int a,b,c,id;
}s[MAXN];
int n;
bool cmp(node x,node y){
    return x.a<y.a;
}
bool cmp2(node x,node y){
    return x.id<y.id;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i].a;
        s[i].id=i;
    }
    sort(s+1,s+1+n,cmp);
    int t=n/3+(n%3!=0);
    for(int i=1;i<=t;i++){
        s[i].b=i-1;
        s[i].c=s[i].a-s[i].b;
    }
    for(int i=t+1;i<=n-t;i++){
        s[i].c=i-1;
        s[i].b=s[i].a-s[i].c;
    }
    for(int i=n-t+1;i<=n;i++){
        s[i].c=n-i;
        s[i].b=s[i].a-s[i].c;
    }
    sort(s+1,s+1+n,cmp2);
    puts("YES");
    for(int i=1;i<=n;i++) cout<<s[i].b<<" ";
    puts("");
    for(int i=1;i<=n;i++) cout<<s[i].c<<" ";
    return 0;
}
```
```