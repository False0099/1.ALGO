# 
## 题目描述
The repetition number of a string is defined as the maximum number _R_ such that the string can be partitioned into _R_ same consecutive substrings. For example, the repetition number of "ababab" is 3 and "ababa" is 1.

Given a string containing lowercase letters, you are to find a substring of it with maximum repetition number.

## 输入格式
The input consists of multiple test cases. Each test case contains exactly one line, which  
gives a non-empty string consisting of lowercase letters. The length of the string will not be greater than 100,000.

The last test case is followed by a line containing a '#'.


## 输出格式
For each test case, print a line containing the test case number( beginning with 1) followed by the substring of maximum repetition number. If there are multiple substrings of maximum repetition number, print the lexicographically smallest one.


## 样例 #1

### 样例输入 #1

```
ccabababc
daabbccaa
#
```

### 样例输出 #1

```
Case 1: ababab
Case 2: aa
```

## 提示
省流：给定一个字符串，求重复次数最多的连续重复字符串

## 题解
我们对于这一题，可以**枚举循环节的长度**，对于每一个 len，枚举串的起点 j，每次递增 len，求出后缀与后缀 $j+len$ 的最长公共前缀 L，

## 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>
#include <string>
 
using namespace std;
 
typedef long long ll;
const ll linf = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const int maxn = 200005;
const int mod = 1000000007;
 
char s[maxn];
int wa[maxn],wb[maxn],wv[maxn],Ws[maxn];
int cmp(int *r,int a,int b,int l)
{return r[a]==r[b]&&r[a+l]==r[b+l];}
// 传入参数：str,sa,len+1,ASCII_MAX+1
void da(const char r[],int sa[],int n,int m) {
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++) Ws[i]=0;
    for(i=0; i<n; i++) Ws[x[i]=r[i]]++;//以字符的ascii码为下标
    for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
    for(i=n-1; i>=0; i--) sa[--Ws[x[i]]]=i;
    //for(int i=0;i<n+1;i++)cout<<sa[i]<<' ';
    for(j=1,p=1; p<n; j*=2,m=p) {
        for(p=0,i=n-j; i<n; i++) y[p++]=i;
        for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0; i<n; i++) wv[i]=x[y[i]];
        for(i=0; i<m; i++) Ws[i]=0;
        for(i=0; i<n; i++) Ws[wv[i]]++;
        for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
        for(i=n-1; i>=0; i--) sa[--Ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
            x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+j]==y[sa[i]+j])?p-1:p++;
            //x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
int sa[maxn],rk[maxn],height[maxn];
// sa,rk,height 下标均从1开始，串下标从1开始计数
// str,sa,len
void calheight(const char *r,int *sa,int n) {
      int i,j,k=0;
      for(i=1; i<=n; i++) rk[sa[i]]=i;
      for(i=0; i<n; height[rk[i++]]=k)
            for(k?k--:0,j=sa[rk[i]-1]; r[i+k]==r[j+k]; k++);
      for(int i=n;i>=1;--i) ++sa[i],rk[i]=rk[i-1];
}
int st[maxn][21], Log[maxn];
void ST(int m) {
    for (int i = 0; i < m; ++i) {
        st[i][0] = height[i];
        Log[i + 1] = log(i + 0.5) / log(2.0);
    }
    Log[1] = 0;
    for (int j = 1; j <= Log[m]; ++j) {
        for (int i = 0; i <= m - (1 << j); ++i) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int query(int a, int b) {
    int l = rk[a + 1], r = rk[b + 1];
    if (l > r) swap(l, r);
    ++l;
    int k = Log[r - l + 1];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}
int main() {
    int cas = 0;
    while (~scanf("%s", s) && s[0] != '#') {
        int n = strlen(s);
        s[n] = 0;
        da(s, sa, n + 1, 130);
        calheight(s, sa, n);
        ST(n + 1);
        // ST处理出每个区间内的最小height值，即最长公共前缀
        int l = n / 2, i, j, L, cnt, k;
        int ans = 1, p = sa[1] - 1, len = 1;
        for (i = 1; i <= l; ++i) {  // 枚举循环节长度
            for (j = 0; j + i < n; j += i) {  // 枚举循环节起点
                if (s[j] != s[j + i]) continue;
                L = query(j, j + i);
 
                int en = j + i + L;
                for (k = 0; k < i; ++k) {  // 向前查找循环节起点
                    int beg = j - k;
                    if (beg < 0 || s[beg] != s[beg + i]) break;
                    cnt = (en - beg) / i; // 根据循环节起点终点计算循环次数
                    if (cnt > ans || (cnt == ans && rk[beg + 1] < rk[p + 1])) {
                        ans = cnt, p = beg, len = cnt * i;
                    }
                }
            }
        }
        printf("Case %d: ", ++cas);
        for (i = 0; i < len; ++i) {
            printf("%c", s[i + p]);
        }
        printf("\n");
    }
    return 0;
}

```