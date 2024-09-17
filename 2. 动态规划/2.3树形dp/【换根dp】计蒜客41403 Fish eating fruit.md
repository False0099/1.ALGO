State Z is a underwater kingdom of the Atlantic Ocean. This country is amazing. There are �n cities in the country and �−1n−1 undirected underwater roads which connect all cities.

In order to save energy and avoid traffic congestion, the king promulgated a series of traffic regulations:

1. Residents have to travel on fish!
    
2. Residents need to feed the fish before you start your trip!The amount of food you feed the fish should be exactly the total distance of your journey.
    
3. What kind of food to feed depends on the total distance of your journey!Total distance is a multiple of three. You should feed the fish with Durian. Total distance modulus 33 equaling 11. It should be Papaya.Total distance modulus 33 equaling 22. It should be Avocado!!!
    

Sure, fish like to eat these fruits very much.

Today is the first day of the king's decree. Because the residents here are not good at mathematics, they don't know how much fruit they need to give fish to go to other cities. So the king give an order to the energy minister Ynaonlctrm **From all cities to all cities directly**, which means that he will make �∗(�−1)n∗(n−1) trips.

For example, A - (5 _mile_) - B - (5 _mile_) - C, he needs to run the fish, starting at A, passing B, finally arriving C (papaya 10 _kg_), also he needs to start at C and end at A (papaya 10 _kg_). Indirect passage is useless. "I've passed City B, my dear emperor." "Oh! It's no use! Not directly! People in cities will never know how much the fish need to eat! The fish will surely die!!! You also need to take several trips which start at B or end with B!" The Emperor said.

It's really a tough task. Can you help him figure out how much fruit he needs to prepare for the emperor's mission?

## Input

Multiple input!

Fist line is �N. next �−1N−1 line has three integer �a, �b and �c. It represent city �a and city �b is connected by a road of �c nautical miles. (1<�≤1041<n≤104, 0≤�,�<�0≤a,b<n, 1≤�<1051≤c<105, ∑�≤105∑n≤105)

## Output

For each data, output three number, the amount of Durian, Papaya and Avocado he need. (the result could be very large, please output the result mod 109+7109+7)

### Sample 1

|Inputcopy|Outputcopy|
|---|---|
|5<br>0 1 2<br>0 2 3<br>0 3 7<br>0 4 6|54 60 30|

  

### Sample 2

| Inputcopy                                                        | Outputcopy |                  |
| ---------------------------------------------------------------- | ---------- | ---------------- |
| 8<br>4 7 1<br>7 5 1<br>4 6 1<br>6 3 1<br>5 2 1<br>2 1 1<br>7 0 1 | 48 54 48   | <br><br><br><br> |
|                                                                  |            |                  |
|                                                                  |            |                  |

## 题意
给你一颗树，要你求出任意两点之间的距离和按照模 3 分类后的和是多少。

## 题解
首先，如果我们不考虑所有点，只考虑我们的以 0 为根节点的答案，那么我们就可以通过我们的 $dp[i][0,1,2]$ 来计算出我们从某个点开始往后我们的模 $[0,1,2]$ 的路径大小是多少。

记录两个数组， $dp[i][k]$ 为距 i 模 3 为 k 的子节点到 i 的距离和
 $f[i][k]$ 为距 i 模 3 为 k 的子节点的个数
 $ans[k]$ 为所有简单路径长度模 3 为 k 的距离和
 $v$ 是 $u$ 的儿子，$c$ 是 u 到 v 的边长度，$0<i,j<3,k=(j-c\%3+3)\%3$

· $dp[u][(i+c\%3)\%3]+=dp[v][i]+f[v][i]*c$ · $f[u][(i+c\%3)\%3]+=f[v][i]$
 · $ans[(i+j+c\%3)\%3]+=f[v][i]*(d[u][j]-d[v][k]-f[v][k]*c)$,算 u 的子节点跨越 u 的答案

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define lson l,mid,p<<1
#define rson mid+1,r,p<<1|1
#define ll long long
using namespace std;
const int inf=1e9;
const int mod=1e9+7;
const int maxn=1e5+10;
int n;
typedef pair<int,int>pii;
vector<pii>g[maxn];
ll d[maxn][3],f[maxn][3],ans[3];
void dfs(int u,int fa){
	f[u][0]=1;
	for(pii x:g[u]){
		if(x.fi==fa) continue;
		int v=x.fi;ll c=x.se;
		dfs(x.fi,u);
		for(int i=0;i<3;i++){
            (d[u][(i+c%3)%3]+=(d[v][i]+f[v][i]*c%mod)%mod)%=mod;
            (f[u][(i+c%3)%3]+=f[v][i])%=mod;
		}
	}
}
void dfs1(int u,int fa){
	ans[0]=(ans[0]+d[u][0])%mod;
	ans[1]=(ans[1]+d[u][1])%mod;
	ans[2]=(ans[2]+d[u][2])%mod;
	for(pii x:g[u]){
		if(x.fi==fa) continue;
        int v=x.fi;ll c=x.se;
		for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                int k=(j-c%3+3)%3;
                (ans[(i+j+c%3)%3]+=f[v][i]*(d[u][j]-d[v][k]-f[v][k]*c%mod)%mod)%=mod;
            }
		}
        dfs1(x.fi,u);
	}
}
int main(){
	//ios::sync_with_stdio(false);
	//freopen("in","r",stdin);
	while(~scanf("%d",&n)){
		for(int i=1,a,b,c;i<n;i++){
			scanf("%d%d%d",&a,&b,&c);
			++a;++b;
			g[a].pb(pii(b,c));
			g[b].pb(pii(a,c));
		}
		ans[0]=ans[1]=ans[2]=0;
		dfs(1,0);dfs1(1,0);
		printf("%lld %lld %lld\n",ans[0]*2%mod,ans[1]*2%mod,ans[2]*2%mod);
		for(int i=1;i<=n;i++) g[i].clear(),d[i][0]=d[i][1]=d[i][2]=f[i][0]=f[i][1]=f[i][2]=0;
	}
	return 0;
}

```