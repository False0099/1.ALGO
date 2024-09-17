## 题目描述

Alice 有一个长度为 N 的数字序列 $A[1 \dots N]$。

Alice 想要按照以下规则，通过一个参数 K 构造序列 B：

- 一开始序列 B 为空。考虑 A 中的每个长度大于等于 K 的区间，请你将该区间中的第 K 大的数字加入到序列 B 中。

Alice 并不关心序列 B 中的元素的排列顺序。她只想知道 B 中的第 M 大元素。请你帮她求出这个元素。

## 输入格式

多组数据。

对于每组数据，第一行包含 $N, K, M（1 \le N \le 10^5, 1 \le K \le N）$，第二行包含 N 个整数 $A_i（1 \le A_i \le 10^9）$。

数据保证 M 不超过序列 B 的长度。


## 输出格式

对于每组数据，输出一行一个数字，表示 B 中的第 M 大元素。

Alice are given an array $A[1..N]$ with N numbers.  
  
Now Alice want to build an array B by a parameter K as following rules:  
  
Initially, the array B is empty. Consider each interval in array A. If the length of this interval is less than K, then ignore this interval. Otherwise, find the K-th largest number in this interval and add this number into array B.  
  
In fact Alice doesn't care each element in the array B. She only wants to know the M-th largest element in the array B. Please help her to find this number.

Input

The first line is the number of test cases.  
  
  
For each test case, the first line contains three positive numbers N(1 \leq N \leq 10^5), K(1 \leq K \leq N), M. The second line contains N numbers A_i (1 \leq A_i \leq 10^9).  
  
  
It's guaranteed that M is not greater than the length of the array B.  

Output

For each test case, output a single line containing the M-th largest element in the array B.

## Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>5 3 2<br>2 3 1 5 4<br>3 3 1<br>5 8 2|3<br>2|

## 题解
我们这一题需要我们可以**二分答案**，**对于我们答案 x，必定存在大于等于 M 个区间的第 k 大数大于 x,**，这个也是我们的笛卡尔法!!!!这一步我想我们是可以记录一下的。假设我们第 K 大的数是 x，这个时候我们利用双指针，得到**第 K 大数大于等于 x** 的区间一共有多少个。我们从头开始记录 $a[i]\geq x$ 的个数，当恰好有 k 个数大于 x 了，那么我们保持前面不动，向后一个个的扩展，**后面的区域也一定满足**能找到第 K 大的数大于等于 x，即在区间 $[1,j+1],[1,j+2],\dots.$ 所以这个开头的贡献就是 $n-i+1$

这一次操作完成后，让我们的左指针也右移，看一下是不是这一段我们的数字都比我们的答案小，如果是的话，那么我们以依然可以扩展。扩展出来的结果还是我们的（n-i+1）。

最后我们拿我们的结果和我们的 M进行比较即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,K;
ll M;
int a[100005];
 
bool judge(int x){
    ll ans = 0;
    int num = 0;
    int j = 1;
    for(int i = 1; i <= N; i++){
        if(a[i] >= x)
            num++;
        if(num == K){
            ans += N - i + 1;
            while(a[j] < x){
                ans += N - i + 1;
                j++;
            }
            num--;
            j++;
        }
    }
    if(ans >= M)
        return true;
    else
        return false;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%lld",&N,&K,&M);
        for(int i = 1; i <= N; i++){
            scanf("%d",&a[i]);
        }
        int l = 1,r = 1000000000;
        int m;
        while(l < r){
            m = l + r >> 1;
            if(judge(m))
                l = m + 1;
            else
                r = m;
        }
        printf("%d\n",l-1);
    }
    return 0;
}
```
