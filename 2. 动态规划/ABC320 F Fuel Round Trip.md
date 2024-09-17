## F - Fuel Round Trip  

---

Time Limit: 2 sec / Memory Limit: 1024 MB

Score : 550 points

### Problem Statement

You are planning to travel from coordinate 00 to coordinate XN​ on a number line, then turn around and return to coordinate 00. Here, you can only move in the positive direction on the outbound trip and in the negative direction on the return trip.  
You will travel by car. The car consumes one liter of fuel for every unit distance it travels. You can carry up to H liters of fuel and cannot move without fuel.  
For each i=1,2,…,N−1, there is a gas station at coordinate Xi​, where you can get Fi​ liters of fuel for Pi​ yen. However, you cannot carry more than H liters of fuel. More precisely, if you have x liters of fuel and use the gas station at coordinate Xi​, you must pay Pi​ yen, and your amount of fuel becomes min(x+Fi​,H) liters. Each gas station can be used at most once **in total during the round trip**.  
Determine if you can achieve this plan when you initially have H liters of fuel, and if it is possible, find the minimum amount of money required.

### Constraints

- 1≤N,H≤300
- 0<X1​<X2​<…<XN​≤105
- 1≤Pi​≤105
- 1≤Fi​≤H
- All input values are integers.

---

### Input

The input is given from Standard Input in the following format:

N H
X1​ X2​ …… XN​
P1​ F1​
P2​ F2​
⋮
PN−1​ FN−1​

### Output

If the plan can be achieved, print the minimum amount of money required; otherwise, print `-1`.

---

### Sample Input 1Copy

Copy

4 10
2 5 9 11
8 10
5 8
4 9

### Sample Output 1Copy

Copy

9

You can achieve the plan by using the gas station at coordinate 55 on the outbound trip and the one at coordinate 99 on the return trip, paying a total of 99 yen.  
It is impossible to achieve the plan by paying 88 yen or less. Note that you cannot use the same gas station on both the outbound and return trips.

---

### Sample Input 2Copy

Copy

1 1
100000

### Sample Output 2Copy

Copy

-1

---

### Sample Input 3Copy

Copy

5 20
4 13 16 18 23
1 16
2 8
4 11
8 13

### Sample Output 3Copy

Copy

13

## 题解
我们设置我们的 dp 数组 $dp_{i,j,k}$ 表示我们从 $x_{1}$ 走到 $x_{i}$ ，还剩下 $J$ 升油, 回来的时候还剩 k 升油

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=305;
int n,h,x[N],p[N],f[N];
int dp[2][N][N];
void chkmin(int &x,int y){
	if (x>y) x=y;
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>h;
	for (int i=1;i<=n;i++) cin>>x[i];
	for (int i=1;i<=n-1;i++)
	{
		cin>>p[i]>>f[i];
	}
	int t=0;
	memset(dp,0x3f,sizeof(dp));
	for (int i=0;i<=h;i++) dp[0][h][i]=0;
	for (int i=1;i<=n;i++)
	{
		memset(dp[t^1],0x3f,sizeof(dp[t^1]));
		int dis=x[i]-x[i-1];
		for (int j=0;j<=h;j++)
			for (int k=0;k<=h;k++)
			{
				if (j+dis<=h&&k-dis>=0)
					chkmin(dp[t^1][j][k],dp[t][j+dis][k-dis]);
				if (j+dis<=h&&k-dis>=0)
					chkmin(dp[t^1][min(j+f[i],h)][k],dp[t][j+dis][k-dis]+p[i]);
				if (j+dis<=h&&min(k+f[i],h)-dis>=0)
					chkmin(dp[t^1][j][k],dp[t][j+dis][min(k+f[i],h)-dis]+p[i]);
			}
		t^=1;
	}
	int ans=1e18;
	for (int i=0;i<=h;i++) ans=min(ans,dp[t][i][i]);
	if (ans==1e18) cout<<-1;
	else cout<<ans;
	return 0;
}
```