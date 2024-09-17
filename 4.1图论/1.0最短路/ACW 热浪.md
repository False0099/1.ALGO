# 知识点
  ## [[spfa算法]] [[单源最短路问题]]
# 题目
 德克萨斯纯朴的民众们这个夏天正在遭受巨大的热浪！！！

他们的德克萨斯长角牛吃起来不错，可是它们并不是很擅长生产富含奶油的乳制品。

农夫 John 此时身先士卒地承担起向德克萨斯运送大量的营养冰凉的牛奶的重任，以减轻德克萨斯人忍受酷暑的痛苦。

John 已经研究过可以把牛奶从威斯康星运送到德克萨斯州的路线。

这些路线包括起始点和终点一共有 T个城镇，为了方便标号为 1到 T。

除了起点和终点外的每个城镇都由双向道路连向至少两个其它的城镇。

每条道路有一个通过费用（包括油费，过路费等等）。

给定一个地图，包含 C条直接连接 2个城镇的道路。

每条道路由道路的起点 $Rs$，终点 $Re$  和花费 $Ci$ 组成。

求从起始的城镇 $Ts$ 到终点的城镇 $Te$ 最小的总费用。

# 思路
·本题我们可以看得出来我们是要构建一个单源最短路，对于构建单源最短路，我们一共有三个可选的算法（其实是四个），朴素的 dij，有堆优化的 dij 。spfa 算法，或者 bellmanford 算法。
·这里我们选择用 spfa 算法。
·
# AC 代码
```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N=1e6+10,M=2*N;
int h[N],ne[M],e[M],w[M],idx;
void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=h[a];
	h[a]=idx++;
} 
int dist[N];
bool st[N];
void spfa(int a){
	queue<int> q;
	memset(dist,0x3f3f,sizeof dist);
	q.push(a);
	while(!q.empty()){
		int t=q.front();
		q.pop();
		st[t]=false;
		for(int i=h[t];i!=-1;t=ne[t]){
			int j=e[i];
			if(dist[j]>dist[t]+w[i]){
				dist[j]=dist[t]+w[i];
				if(!st[j]){
					q.push(j);
					st[j]=true;
				}
			}
		}
	}
}
int main()
{
    int n,m,st,ed;
    cin>>n>>m>>st>>ed;
    memset(h,-1,sizeof h);
    for(int i=0;i<m;i++)
    {
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        add(a,b,w),add(b,a,w);
    }
    int t=spfa(st,ed);
    cout<< t <<endl;
    return 0;
}


```
# 备注
