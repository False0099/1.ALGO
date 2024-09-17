FatMouse has stored some cheese in a city. The city can be considered as a square grid of dimension n: each grid location is labelled (p,q) where 0 <= p < n and 0 <= q < n. At each grid location Fatmouse has hid between 0 and 100 blocks of cheese in a hole. Now he's going to enjoy his favorite food.  
  
FatMouse begins by standing at location (0,0). He eats up the cheese where he stands and then runs either horizontally or vertically to another location. The problem is that there is a super Cat named Top Killer sitting near his hole, so each time he can run at most k locations to get into the hole before being caught by Top Killer. What is worse -- after eating up the cheese at one location, FatMouse gets fatter. So in order to gain enough energy for his next run, he has to run to a location which have more blocks of cheese than those that were at the current hole.  
  
Given n, k, and the number of blocks of cheese at each grid location, compute the maximum amount of cheese FatMouse can eat before being unable to move.  

Input

There are several test cases. Each test case consists of  
  
a line containing two integers between 1 and 100: n and k  
n lines, each with n numbers: the first line contains the number of blocks of cheese at locations (0,0) (0,1) ... (0,n-1); the next line contains the number of blocks of cheese at locations (1,0), (1,1), ... (1,n-1), and so on.  
The input ends with a pair of -1's.  

Output

For each test case output in a line the single integer giving the number of blocks of cheese collected.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|3 1<br>1 2 5<br>10 11 6<br>12 12 7<br>-1 -1|37|


## 题解
我们本题的初始思路应该是：我们这一题应该考虑贡献：如果一个人能够对我们的答案有贡献，那么在若干步内，一定有一个满足我们的条件。虽然这其实已经有一点图论的味道了（）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
const int MAXN = 105;
#define PI acos(-1)
int n,k;
int a[MAXN][MAXN],dp[MAXN][MAXN],dir[4][2]={1,0,-1,0,0,1,0,-1};
int dfs(int x,int y){
    if(dp[x][y])return dp[x][y];
    dp[x][y]=a[x][y];
    for(int i=0;i<4;i++){
        for(int j=1;j<=k;j++){
            int xx=x+j*dir[i][0];
            int yy=y+j*dir[i][1];
            if(xx>=1&&xx<=n&&yy>=1&&yy<=n&&a[x][y]<a[xx][yy]){
                dp[x][y]=max(dp[x][y],dfs(xx,yy)+a[x][y]);
            }
            if(xx<1||xx>n||yy<1||yy>n)break;
        }
    }
    return dp[x][y];
}
int main()
{
    while(~scanf("%d%d",&n,&k)&&n!=-1){
        memset(dp,0,sizeof(dp));
        rep(i,1,n){
            rep(j,1,n){
                scanf("%d",&a[i][j]);
            }
        }
        memset(dp,0,sizeof(dp));
        dfs(1,1);
        printf("%d\n",dp[1][1]);
    }
    return 0;
}
```
}