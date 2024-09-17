# 知识点
  ## [[二分、三分]] [[Dijstra算法]] [[DFS]]
# 题目
 在郊区有 N座通信基站，P条双向电缆，第 i条电缆连接基站 Ai和 Bi。

 特别地，1号基站是通信公司的总站，N 号基站位于一座农场中。

 现在，农场主希望对通信线路进行升级，其中升级第 i 条电缆需要花费 Li。

 电话公司正在举行优惠活动。

 农产主可以指定一条从 1号基站到 N 号基站的路径，并指定路径上不超过 K
条电缆，由电话公司免费提供升级服务。

 农场主只需要支付在该路径上剩余的电缆中，升级价格最贵的那条电缆的花费即可。

 求至少用多少钱可以完成升级。

# 输入格式
第 1行：三个整数 N，P，K。

第 2-P+1行：第 i+1行包含三个整数 Ai, Bi, Li。

# 输出格式
包含一个整数表示最少花费。

若 1号基站与 N号基站之间不存在路径，则输出 −1。

#  数据范围
$0≤K<N≤1000$

$1≤P≤10000$

$1≤Li≤1000000$
# 输入样例 ：
5 7 1
1 2 5
3 1 4
2 4 8
3 2 3
5 2 9
3 4 7
4 5 6
# 输出样例 ：
4

# 思路
·我们首先将原来的问题转换为可以解决的，能免费 K 条路，并计算后面的那一个最大值，就等价于从 1 到 N 的第 K+1 短路。
·我们可以发现，答案满足一定的性质，比如随着最少花费的增加，能免费的路是不会减少的。这就是典型的满足二分的条件
·所以我们就可以用二分答案的方法来找到最后的结果
·而二分的检查函数就等价于去检查从开始到 N 点的最短距离，此时每两个点之间的距离被我们定义为该节点的值是否小于减免值，如果是，权值为 0，否则权值为 1。如果满足条件，那么两点之间的距离一定是等于 k 的
·又因为我们求的是 0-1 边权，所以我们可以直接用 BFS 的方法求出两点之间的最短路
# AC 代码
```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N=1e6+10,M=2*N;
int h[N],e[M],ne[M],w[M],idx;
void add(int a,int b,int c){
	w[idx]=c;
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}
int dist[N];
bool st[N];
bool check(int bound){
	memset(dist,0x3f3f3f,sizeof dist);
	memset(st,0,sizeof st);
	deque.push_back(1);
	dist[1]=0;
	while(q.size()){
		int t=q.front();
		q.pop_front();
		if(st[t]) continue;
		st[t]=true;
		for(int i=h[t];i!=-1;i=ne[i]){
			int j=e[i];
			int x=w[j]>bound;//同时变更边权
			if(dist[j]>dist[t]+x){
				dist[j]=dist[t]+x;
				if(x==0){
					q.push_front(j);
				}else{
					q.push_back(j);
				}
			}
		}
	}
	return dist[n]<=k;
}
int main(){
	cin>>n>>p>>k;
	memset(h,-1,sizeof h);
	for(int i=0;i<p;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
		add(b,a,c);
	}
	int l=0,r=1e6+10;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	if(r==1e6+10) cout<<-1<<endl;
	else cout<<r<<endl;
	return 0;
}
```
# 备注
