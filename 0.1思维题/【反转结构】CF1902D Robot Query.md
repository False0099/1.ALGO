# Robot Queries

## 题面翻译

给你一个操作序列，其中包含 $UDLR$ 。

- $U$ 表示从 $(x,y)\to (x,y+1)$

- $D$ 表示从 $(x,y)\to (x,y-1)$

- $L$ 表示从 $(x,y)\to (x-1,y)$

- $R$ 表示从 $(x,y)\to (x+1,y)$

给你 $q$ 个询问，每次询问给你 $x,y,l,r$ 。

相当于将操作序列中 $l\to r$ 的操作序列取反。$(s_1s_2\dots s_{l-1}s_rs_{r-1}\dots s_{l+1}s_ls_{r+1}\dots s_{n-1}s_n)$

然后按顺序执行操作序列，是否有可能到达 $(x,y)$

每个询问互相独立。

## 题目描述

There is an infinite $ 2 $ -dimensional grid. Initially, a robot stands in the point $ (0, 0) $ . The robot can execute four commands:

- U — move from point $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from point $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from point $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from point $ (x, y) $ to $ (x + 1, y) $ .

You are given a sequence of commands $ s $ of length $ n $ . Your task is to answer $ q $ independent queries: given four integers $ x $ , $ y $ , $ l $ and $ r $ ; determine whether the robot visits the point $ (x, y) $ , while executing a sequence $ s $ , but the substring from $ l $ to $ r $ is reversed (i. e. the robot performs commands in order $ s_1 s_2 s_3 \dots s_{l-1} s_r s_{r-1} s_{r-2} \dots s_l s_{r+1} s_{r+2} \dots s_n $ ).

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the length of the command sequence and the number of queries, respectively.

The second line contains a string $ s $ of length $ n $ , consisting of characters U, D, L and/or R.

Then $ q $ lines follow, the $ i $ -th of them contains four integers $ x_i $ , $ y_i $ , $ l_i $ and $ r_i $ ( $ -n \le x_i, y_i \le n $ ; $ 1 \le l \le r \le n $ ) describing the $ i $ -th query.

## 输出格式

For each query, print YES if the robot visits the point $ (x, y) $ , while executing a sequence $ s $ , but the substring from $ l $ to $ r $ is reversed; otherwise print NO.

## 样例 #1

### 样例输入 #1

```
8 3
RDLLUURU
-1 2 1 7
0 0 3 4
0 1 7 8
```

### 样例输出 #1

```
YES
YES
NO
```

## 样例 #2

### 样例输入 #2

```
4 2
RLDU
0 0 2 2
-1 -1 2 3
```

### 样例输出 #2

```
YES
NO
```

## 样例 #3

### 样例输入 #3

```
10 6
DLUDLRULLD
-1 0 1 10
-1 -2 2 5
-4 -2 6 10
-1 0 3 9
0 1 4 7
-3 -1 5 8
```

### 样例输出 #3

```
YES
YES
YES
NO
YES
YES
```

## 提示

In the first query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/4aac546138020132b74e07749db84bb06a513da8.png)In the second query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/b189da90dcd98cd79a3624a3015d7f2cf2e922e4.png)In the third query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/5220422eecc4ff8d70f683171d72758af4ccdbfe.png)

## 题解
我们首先考虑如果没有我们的反转操作，我们应该怎么样统计，我们考虑使用一个 map<点，vector>来维护我们每一个元素出现的位置在哪里。

现在考虑怎么维护我们反转操作，我们注意到，操作反转前后，我们的起始点和终点是没有改变的。而我们反转后的图形是存在一个对称中心：
![[Pasted image 20240304173040.png]]

而我们的对称中心，可以通过我们的起点和终点两个点计算出来，计算出我们的对称中心，一个点对应的源点，就可以通过我们的 (xend, yend)=(xstart+(xmid-xstart) * 2, ystart+(ymid-ystart) * 2)。

也就是说，xstart=2* xmid-xend, ystart=2 * ymid-yend。于是，我们就可以通过判断它的源点是否在我们的原来的位置从而判断。

**注意：本题需要卡常

```
#include <bits/stdc++.h>
using namespace std;
long long hashe(int x,int y){
	return 13311331*x+y;
}
map<long long,vector<int>> mp;
const int N=2e5+10;

pair<int,int> pos[N];
signed main(){
	int n,q;
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	string s;
	cin>>s;
	s=' '+s;
	//vector<pair<int,int>> pos(n+1);
	int xx=0,yy=0;
	
	mp[hashe(0,0)].push_back(0);
	pos[0]={0,0};
	for(int i=1;i<n+1;i++){
		if(s[i]=='U'){
			yy++;
			pos[i]={xx,yy};
			mp[hashe(xx,yy)].push_back(i);
		}
		if(s[i]=='D'){
			yy--;
			pos[i]={xx,yy};
			mp[hashe(xx,yy)].push_back(i);
		}
		if(s[i]=='L'){
			xx--;
			pos[i]={xx,yy};
			mp[hashe(xx,yy)].push_back(i);
		}
		if(s[i]=='R'){
			xx++;
			pos[i]={xx,yy};
			mp[hashe(xx,yy)].push_back(i);
		}
	}
	while(q--){
		int x,y,l,r;
		cin>>x>>y>>l>>r;
		pair<int,int> u1=pos[l-1];
		pair<int,int> u2=pos[r];
		int xtrans=(u1.first+u2.first)-x;
		int ytrans=(u1.second+u2.second)-y;
		if(!mp.count(hashe(x,y))&&!mp.count(hashe(xtrans,ytrans))){
			cout<<"No"<<endl;
			continue;
		}
		vector<int> posl=mp[hashe(x,y)];
		bool flag=false;
		
		if(posl.size()){
			if(posl[0]<l){
				flag=true;
				cout<<"Yes"<<endl;
				continue;
			}
		}
		auto u=lower_bound(posl.begin(),posl.end(),r);
		if(u!=posl.end()&&*u<=n){
			flag=true;
			cout<<"Yes"<<endl;
			continue;
		}
		posl=mp[hashe(xtrans,ytrans)];
		u=lower_bound(posl.begin(),posl.end(),l);
		if(u!=posl.end()&&*u<=r-1){
			flag=true;
			cout<<"Yes"<<endl;
			continue;
		}
		if(flag){
			cout<<"Yes"<<endl;
		}else{
			cout<<"No"<<endl;
		}
	} 
}
```