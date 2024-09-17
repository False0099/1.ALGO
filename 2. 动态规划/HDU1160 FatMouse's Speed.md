FatMouse believes that the fatter a mouse is, the faster it runs. To disprove this, you want to take the data on a collection of mice and put as large a subset of this data as possible into a sequence so that the weights are increasing, but the speeds are decreasing.  

Input

Input contains data for a bunch of mice, one mouse per line, terminated by end of file.  
  
The data for a particular mouse will consist of a pair of integers: the first representing its size in grams and the second representing its speed in centimeters per second. Both integers are between 1 and 10000. The data in each test case will contain information for at most 1000 mice.  
  
Two mice may have the same weight, the same speed, or even the same weight and speed.  

Output

Your program should output a sequence of lines of data; the first line should contain a number n; the remaining n lines should each contain a single positive integer (each one representing a mouse). If these n integers are m[1], m[2],..., m[n] then it must be the case that  
  
W[m[1]] < W[m[2]] < ... < W[m[n]]  
  
and  
  
S[m[1]] > S[m[2]] > ... > S[m[n]]  
  
In order for the answer to be correct, n should be as large as possible.  
All inequalities are strict: weights must be strictly increasing, and speeds must be strictly decreasing. There may be many correct outputs for a given input, your program only needs to find one.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|6008 1300<br>6000 2100<br>500 2000<br>1000 4000<br>1100 3000<br>6000 2000<br>8000 1400<br>6000 1200<br>2000 1900|4<br>4<br>5<br>9<br>7|

## 题解
我们这一题就是二维偏序版本的 LIS，我们需要先按照我们的一个维度排序后，再去进行我们的 LIS 即可。（注：如果要进行三位偏序的 LIS，我们就需要用我们的 CDQ 分治，将我们的前两维度变得有序后，我们再来进行 dp）

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
 
const int maxn=1e3+100;
struct note
{
    int s,w;
    int cnt;
}point[maxn];
int pre[maxn],dp[maxn];
 
bool cmp(struct note a,struct note b)
{
    if (a.w==b.w) return a.s>b.s;
    return a.w<b.w;
}
void print(int pos)
{
    if (pre[pos]!=pos) print(pre[pos]);
    printf("%d\n",point[pos].cnt);
}
int main()
{
    int n=0;
    while (scanf("%d%d",&point[n].w,&point[n].s)!=EOF) {
        point[n].cnt=n+1;
        n++;
    }
    sort(point,point+n,cmp);
    memset (dp,0,sizeof (dp));
    int ans=0,pos;
    for (int i=0;i<n;i++) {
        dp[i]=1;
        pre[i]=i;
        for (int j=0;j<i;j++) {
            if (point[i].s<point[j].s&&point[i].w>point[j].w) {
                if (dp[i]<dp[j]+1) {
                    dp[i]=dp[j]+1;
                    pre[i]=j;//记录路径，它的前一个
                }
            }
        }
        ans=max(ans,dp[i]);
    }
    for (int i=0;i<n;i++) {
        if (ans==dp[i]) {
            pos=i;
            break;
        }
    }
    printf("%d\n",ans);
    print(pos);//递归输出路径
    return 0;
}
```