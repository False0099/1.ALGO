# [NWRRC 2016] CodeCoder vs TopForces

## 题面翻译

- 有 $n$ 个人，每个人有两个能力值 $CC_i$ 和 $TF_i$。第 $i$ 个人能打败第 $j$ 个人当且仅当 $CC_i >CC_j$ 或 $TF_i>TF_j$。

- 强的关系具有传递性，也就是说 $i$ 比 $j$ 强，$j$ 比 $k$ 强，那么 $i$ 比 $k$ 强。求出每个人最多可以打败的人的个数。

- $n \leq10^5$，$CC_i,TF_i \leq10^6$，数据保证 $CC_i$ 两两不同、$TT_i$ 两两不同。

## 题目描述

Competitive programming is very popular in Byteland. In fact, every Bytelandian citizen is registered at two programming sites -- CodeCoder and TopForces. Each site maintains its own proprietary rating system. Each citizen has a unique integer rating at each site that approximates their skill. Greater rating corresponds to better skill.

People of Byteland are naturally optimistic. Citizen A thinks that he has a chance to beat citizen B in a programming competition if there exists a sequence of Bytelandian citizens $A = P_{0}, P_{1},...,P_{k} = B$ for some $k \ge 1$ such that for each $i (0 \le i < k) , P_{i}$ has higher rating than $P_{i+1}$ at one or both sites.

Each Bytelandian citizen wants to know how many other citizens they can possibly beat in a programming competition.

## 输入格式

The first line of the input contains an integer $n$ -- the number of citizens $(1 \le n \le 100 000)$ . $The following n$ lines contain information about ratings. The i-th of them contains two integers $CC_{i} and TF_{i}$ -- ratings of the i-th citizen at CodeCoder and TopForces $(1 \le CC_{i}, TF_{i} \le 10^{6}).$ All the ratings at each site are distinct.

## 输出格式

For each citizen $i$ output an integer $b_{i}$ -- how many other citizens they can possibly beat in a programming competition. Each $b_{i}$ should be printed in a separate line, in the order the citizens are given in the input.

## 样例 #1

### 样例输入 #1

```
4
2 3
3 2
1 1
4 5
```

### 样例输出 #1

```
2
2
0
3
```

## 提示

Time limit: 2 s, Memory limit: 256 MB.

## 题解
本题我们注意到，我们的各个关系之间存在传递性，我们的最朴素的方法，就是**通过我们的暴力枚举两个点**，但这样显然会超时，我们于是只考虑将我们**第 K 大**和我们的**第 K-1 大**之间进行连边。

建完图后，我们发现图中可能会**存在环**，我们考虑缩点，在我们的一个所店内，我们是**任意可达的**，于是，我们就可以通过我们的 tarjan 缩点来进行我们的对应的处理。之后我们再倒序 DP 即可求出，我们从某个点触发，有多少个严格比它小的人。

```
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5+10, M =2e5+10;

int n, m, mod;
int h[N],e[M<<1],ne[M<<1],idx,val[N];//原图参数 
/*tarjan中间量*/
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
/*tarjan中间量*/
int id[N], scc_size[N];//新旧关系 
int scc_cnt;  //新图的n 
int hs[N],sum[N],dp[N],in[N];//新图的参数 
int ans; 
void add(int h[],int a,int b)
{
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u,in_stk[u] = true;
    for(int i =h[u];~i;i=ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u],low[j]);
        }
        else if(in_stk[j])low[u] = min(low[u],dfn[j]);
    }
    if(dfn[u]==low[u])
    {
        ++scc_cnt;
        int y;
        do{
            y=stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            //sum[scc_cnt]+=1;//处理我们的合并点 
            scc_size[scc_cnt]++;
        }while(y!=u);
    }
}

void topsort(){
	queue<int> q;
	int tot=0;
	for(int i=1;i<=scc_cnt;i++){
		if(in[i]==0){
            //cerr<<i<<endl;
			q.push(i);
		}
		sum[i]=scc_size[i];
        dp[i]=scc_size[i]-1;
	}
	while(q.size()){
		int now=q.front();
		q.pop();
		for(int i=hs[now];i!=-1;i=ne[i]){
			int v=e[i];
			in[v]--;
            //cerr<<"edge"<<now<<" "<<v<<endl;
            sum[v]+=sum[now];
			dp[v]+=sum[now];
			if(in[v]==0){
				q.push(v);
			}
            //cerr<<now<<" "<<sum[now]<<" "<<dp[now]<<endl;
            //cerr<<now<<" "<<v<<endl;
		}
	}
}
struct node
{
    int cc;
    int tf;
    int id;
    /* data */
};

signed main()
{
    memset(h,-1,sizeof h);
    memset(hs,-1,sizeof hs);
    int n;
    cin>>n;
    vector<node> people(n+1);
    for(int i=1;i<=n;i++){
        cin>>people[i].cc;
        cin>>people[i].tf;
        people[i].id=i;
    }
    sort(begin(people)+1,end(people),[&](node a,node b){
        return a.cc<b.cc;
    });
    for(int i=2;i<=n;i++){
        add(h,people[i].id,people[i-1].id);
    }
    sort(begin(people)+1,end(people),[&](node a,node b){
        return a.tf<b.tf;
    });
    for(int i=2;i<=n;i++){
        add(h,people[i].id,people[i-1].id);
    }
    //cerr<<1<<endl;
    for(int i = 1;i<=n;i++)
    {
        if(!dfn[i])
        {
            tarjan(i);
        }
    }
    set<pair<int,int>> st;
    st.clear();
    for(int i=1;i<=n;i++)
    {
        for(int j = h[i];~j;j=ne[j])
        {
            int k = e[j];
            int a = id[i],b= id[k];            
            if(a!=b)
            {
                    if(st.count({a,b})){
                        continue;
                    }
                    st.insert({a,b});
                    //cerr<<a<<" "<<b<<endl;
            		add(hs,b,a);
            		in[a]++;
            }
        }
    }
	topsort();
    for(int i=1;i<=n;i++){
        //cerr<<id[i]<<" ";
        //cerr<<scc_size[id[i]]<<endl;
        cout<<dp[id[i]]<<endl;
    }
	//cout<<ans<<endl;
}
```
```