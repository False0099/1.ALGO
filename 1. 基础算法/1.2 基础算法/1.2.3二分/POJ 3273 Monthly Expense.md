## Description

Farmer John is an astounding accounting wizard and has realized he might run out of money to run the farm. He has already calculated and recorded the exact amount of money (1 ≤ _moneyi_ ≤ 10,000) that he will need to spend each day over the next _N_ (1 ≤ _N_ ≤ 100,000) days.

FJ wants to create a budget for a sequential set of exactly _M_ (1 ≤ _M_ ≤ _N_) fiscal periods called "fajomonths". Each of these fajomonths contains a set of 1 or more consecutive days. Every day is contained in exactly one fajomonth.

FJ's goal is to arrange the fajomonths so as to minimize the expenses of the fajomonth with the highest spending and thus determine his monthly spending limit.

## Input

Line 1: Two space-separated integers: _N_ and _M_  
Lines 2.._N_+1: Line _i_+1 contains the number of dollars Farmer John spends on the _i_th day

## Output

Line 1: The smallest possible monthly limit Farmer John can afford to live with.

## Sample Input

7 5
100
400
300
100
500
101
400

## Sample Output

500

Hint

If Farmer John schedules the months so that the first two days are a month, the third and fourth are a month, and the last three are their own months, he spends at most $500 in any month. Any other method of scheduling gives a larger minimum monthly limit.

## 题解
我们这一题采用二分答案，假设我们现在每一段的最大值为 x，我们就可以去在原数组中找，把原数组最多能分成多少段，如果段数比我们的 m 要小，那就说明我们取大了，反之就说明我们取小了。

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N  = 1e5+100;
int a[N];
int n,m;
bool check(int k){
    int cnt = 1;/*一开始写的0 一直wa QAQ 下面判断的时候就该知道最后一个月没有加上 */
    int p = 0;
    for (int i = 0; i < n; ++i){
        if (a[i]>k) return false;
        p += a[i];
        if (p>k){
            p = a[i];
            cnt++;
        }
    }
    if (cnt<=m) return true;
    return false;
}
int main(){
    scanf("%d%d",&n,&m);
    int mx = -1;
    for (int i = 0; i < n; ++i){
        scanf("%d",&a[i]);
        mx = max(a[i],mx);
    }
    int ld = mx,rd = 1e8;
    while (ld<=rd){
        int mid = (ld+rd)>>1;
        if (check(mid)) rd = mid-1;
        else ld = mid+1;
    }
    printf("%d\n",rd+1);
    return 0;
}
```