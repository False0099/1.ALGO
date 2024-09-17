# IT Restaurants

## 题面翻译

## 题目描述：   
给定一个 n，表示有 n 个节点（1～n）以及接下来 n-1 条边的树，现用两种颜色（红，蓝）对这颗树的节点染色，染色规则是，每个节点有三种状态，要么染成红色，要么染成蓝色，要么不染色，并且规定用一条边连接的两个节点要么染成颜色相同，要么一个染色一个不染色。问在保证染色节点最多的条件下，红色与蓝色的个数的情况。（要求是至少有一个节点被染成红色，至少一个节点被染成蓝色）。   
## 输入输出格式：
#### 输入格式：
第一行一个 n，接下来 n 行每行两个数，表示一条无向边。  
#### 输出格式：
第一行输出一个数表示可行方案数。
接下来若干行每行输出两个数表示染成红色的数量和染成蓝色的数量。（按红的数量的升序输出）。

## 题目描述

Сity N. has a huge problem with roads, food and IT-infrastructure. In total the city has $ n $ junctions, some pairs of them are connected by bidirectional roads. The road network consists of $ n-1 $ roads, you can get from any junction to any other one by these roads. Yes, you're right — the road network forms an undirected tree.

Recently, the Mayor came up with a way that eliminates the problems with the food and the IT-infrastructure at the same time! He decided to put at the city junctions restaurants of two well-known cafe networks for IT professionals: "iMac D 0 naldz" and "Burger Bing". Since the network owners are not friends, it is strictly prohibited to place two restaurants of different networks on neighboring junctions. There are other requirements. Here's the full list:

- Each junction must have at most one restaurant;
- Each restaurant belongs either to "iMac D 0 naldz", or to "Burger Bing";
- Each network should build at least one restaurant;
- There is no pair of junctions that are connected by a road and contains restaurants of different networks.

The Mayor is going to take a large tax from each restaurant, so he is interested in making the total number of the restaurants as large as possible.

Help the Mayor to analyze the situation. Find all such pairs of $ (a, b) $ that $ a $ restaurants can belong to "iMac D 0 naldz", $ b $ restaurants can belong to "Burger Bing", and the sum of $ a+b $ is as large as possible.

## 输入格式

The first input line contains integer $ n $ $ (3<=n<=5000) $ — the number of junctions in the city. Next $ n-1 $ lines list all roads one per line. Each road is given as a pair of integers $ x_{i}, y_{i} $ $ (1<=x_{i}, y_{i}<=n) $ — the indexes of connected junctions. Consider the junctions indexed from 1 to $ n $ .

It is guaranteed that the given road network is represented by an undirected tree with $ n $ vertexes.

## 输出格式

Print on the first line integer $ z $ — the number of sought pairs. Then print all sought pairs $ (a, b) $ in the order of increasing of the first component $ a $ .

## 样例 #1

### 样例输入 #1

```
5
1 2
2 3
3 4
4 5
```

### 样例输出 #1

```
3
1 3
2 2
3 1
```

## 样例 #2

### 样例输入 #2

```
10
1 2
2 3
3 4
5 6
6 7
7 4
8 9
9 10
10 4
```

### 样例输出 #2

```
6
1 8
2 7
3 6
6 3
7 2
8 1
```

## 提示

The figure below shows the answers to the first test case. The junctions with "iMac D 0 naldz" restaurants are marked red and "Burger Bing" restaurants are marked blue.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF212E/e31e0c50248bfe0f0984b19a32c117d20b449516.png)

## 题解
首先我们分析，我们可以得到，如果我们要我们的颜色最多，那么我们的方案就是把我们的某一个唯一的节点染成白色，其他染成蓝色。

而我们于是就可以考虑枚举我们每一个节点变白时，我们的可能的染色情况。

这个时候，我们就可以通过我们的一个 0-1 背包来进行，

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,cnt,tot,h[5005],w[5005],c[5005];
  bitset<5005>ans,dp;//0-1背包
  struct edge{
      int v,nxt;
  }e[10005];
  void adde(int u,int v){
      e[++cnt].nxt=h[u];
      h[u]=cnt;
      e[cnt].v=v;
  }//链式前向星
  void dfs(int x,int fa){
      w[x]++;
      for(int i=h[x];i;i=e[i].nxt){
          if(e[i].v==fa)continue;
          dfs(e[i].v,x);
          w[x]+=w[e[i].v];
      }
  }//求以1为根时分别以每个点为根的子树的节点数
  void dfs1(int x,int fa){
      int tot=0,sum=0;
      for(int i=h[x];i;i=e[i].nxt){
          if(e[i].v==fa)continue;
          c[++tot]=w[e[i].v];
          sum+=w[e[i].v];
      }
      c[++tot]=n-sum-1;
      dp.reset();
      dp[0]=1;
      for(int i=1;i<=tot;i++){
          for(int j=n;j>=c[i];j--){
              if(dp[j-c[i]])dp[j]=1;
          }
      }
      ans|=dp;//0-1背包
      for(int i=h[x];i;i=e[i].nxt){
          if(e[i].v==fa)continue;
          dfs1(e[i].v,x);
      }
  }
  int main()
  {
      scanf("%d",&n);
      for(int i=2,a,b;i<=n;i++)scanf("%d%d",&a,&b),adde(a,b),adde(b,a);
      dfs(1,0);
      dfs1(1,0);
      tot=0;
      for(int i=1;i<n-1;i++)if(ans[i])tot++;//一共有多少解
      printf("%d\n",tot);
      for(int i=1;i<n-1;i++)if(ans[i])printf("%d %d\n",i,n-i-1);//输出
      return 0;
  }
```