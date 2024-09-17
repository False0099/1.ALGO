# [HAOI 2010] 计数

## 题目描述

你有一组非零数字（不一定唯一），你可以在其中插入任意个 0，这样就可以产生无限个数。比如说给定 $\{1,2\}$，那么可以生成数字 12，21，102，120，201，210，1002，1020 等等。


现在给定一个数，问在这个数之前有多少个数（注意这个数不会有前导 0）。

## 输入格式

只有一行，为一个整数 $n$。

## 输出格式

一行一个整数，表示 $n$ 之前出现的数的个数。

## 样例 #1

### 样例输入 #1

```
1020
```

### 样例输出 #1

```
7
```

## 提示

$n$ 的长度不超过 $50$，答案不超过 $2^{63}-1$。

## 题解
根据题目，我们一致，最后每一种数字出现的次数，应该是我们给定的数字中，每一种数字出现的次数。
那么，如果我们要进行数位 dp 时，就需要用到 1. 当前的位数 2.1-9 各个数字已经出现了多少次 3. 是否达到了限制。这显然就是一个很暴力的 dp，我们对于 11 维空间，我们可以考虑采用 map 来优化，减少我们的存储。

```cpp
#include<bits/stdc++.h>
using namespace std;
short len,a[51];
string s;
map<short,map<short,map<short,map<short,map<short,map<short,map<short,map<short,map<short,map<short,map<short,long long>>>>>>>>>>> F; 
short cnt[10];//存每个数字需要出现的次数 
inline long long dfs(short now_where,short if_le,short if_z,short z,short o,short t,short tr,short f,short fi,short s,short se,short e,short ni){
	if(!now_where) return (o==cnt[1]&&t==cnt[2]&&tr==cnt[3]&&f==cnt[4]&&fi==cnt[5]&&s==cnt[6]&&se==cnt[7]&&e==cnt[8]&&ni==cnt[9])?1:0;
	else if(!if_le&&!if_z&&F[now_where][z][o][t][tr][f][fi][s][se][e].count(ni)) return F[now_where][z][o][t][tr][f][fi][s][se][e][ni];
	long long ans=0,up=if_le?a[now_where]:9;
	for(register short i=0;i<=up;++i){
		if(if_z&&i==0) ans+=dfs(now_where-1,if_le&&i==up,1,z,o,t,tr,f,fi,s,se,e,ni);
		else if(i==0&&z +1<=cnt[0]) ans+=dfs(now_where-1,if_le&&i==up,0,z+1,o,t,tr,f,fi,s,se,e,ni);
		else if(i==1&&o +1<=cnt[1]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o+1,t,tr,f,fi,s,se,e,ni);
		else if(i==2&&t +1<=cnt[2]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t+1,tr,f,fi,s,se,e,ni);
		else if(i==3&&tr+1<=cnt[3]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr+1,f,fi,s,se,e,ni);
		else if(i==4&&f +1<=cnt[4]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f+1,fi,s,se,e,ni);
		else if(i==5&&fi+1<=cnt[5]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi+1,s,se,e,ni);
		else if(i==6&&s +1<=cnt[6]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi,s+1,se,e,ni);
		else if(i==7&&se+1<=cnt[7]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi,s,se+1,e,ni);
		else if(i==8&&e +1<=cnt[8]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi,s,se,e+1,ni);
		else if(i==9&&ni+1<=cnt[9]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi,s,se,e,ni+1);
	}
	if(!if_le&&!if_z) F[now_where][z][o][t][tr][f][fi][s][se][e][ni]=ans;
	return ans;
}
inline void solve(){
	cin>>s;
	for(register short i=s.size()-1;i>=0;--i) a[++len]=s[i]-'0',++cnt[s[i]-'0'];
	printf("%lld",dfs(len,1,1,0,0,0,0,0,0,0,0,0,0)-1);
}
int main(){
	solve();
	return 0;
}

```

当然，我们继续考虑我们 map 的想法，优化掉我们的 a 到 k 部分，我们把它**拼接成一个字符串**的想法是可行的，但我们**不能直接拼接**，因为直接拼接可能会造成歧义，所以我们还可在中间加入一些**特殊字符**来区别每一位数

```cpp
#include<bits/stdc++.h>
using namespace std;
short len,a[51],cnt[10];
string s,all;
map<short,map<string,long long>> F; 
inline string get(short o,short t,short tr,short f,short fi,short s,short se,short e,short ni){
	string nowk="";short w;
	w=o ;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';//加区分的字符 
	w=t ;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';
	w=tr;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';
	w=f ;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';
	w=fi;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';
	w=s ;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';
	w=se;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';
	w=e ;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';
	w=ni;while(w) nowk+=(w%10+'0'),w/=10;nowk+=',';
	return nowk;
}
inline long long dfs(short now_where,bool if_le,bool if_z,short z,short o,short t,short tr,short f,short fi,short s,short se,short e,short ni,string now){
	if(!now_where) return now==all;
	if(!if_le&&!if_z&&F[now_where].count(now)) return F[now_where][now];
	long long ans=0,up=if_le?a[now_where]:9;
	for(register short i=0;i<=up;++i){
		if(if_z&&i==0)ans+=dfs(now_where-1,if_le&&i==up,1,0,0,0,0,0,0,0,0,0,0,"");
		else if(i==0) ans+=dfs(now_where-1,if_le&&i==up,0,z+1,o,t,tr,f,fi,s,se,e,ni,now);
		else if(i==1&&o +1<=cnt[1]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o+1,t,tr,f,fi,s,se,e,ni,get(o+1,t,tr,f,fi,s,se,e,ni));		
		else if(i==2&&t +1<=cnt[2]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t+1,tr,f,fi,s,se,e,ni,get(o,t+1,tr,f,fi,s,se,e,ni));
		else if(i==3&&tr+1<=cnt[3]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr+1,f,fi,s,se,e,ni,get(o,t,tr+1,f,fi,s,se,e,ni));
		else if(i==4&&f +1<=cnt[4]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f+1,fi,s,se,e,ni,get(o,t,tr,f+1,fi,s,se,e,ni));
		else if(i==5&&fi+1<=cnt[5]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi+1,s,se,e,ni,get(o,t,tr,f,fi+1,s,se,e,ni));
		else if(i==6&&s +1<=cnt[6]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi,s+1,se,e,ni,get(o,t,tr,f,fi,s+1,se,e,ni));
		else if(i==7&&se+1<=cnt[7]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi,s,se+1,e,ni,get(o,t,tr,f,fi,s,se+1,e,ni));
		else if(i==8&&e +1<=cnt[8]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi,s,se,e+1,ni,get(o,t,tr,f,fi,s,se,e+1,ni));
		else if(i==9&&ni+1<=cnt[9]) ans+=dfs(now_where-1,if_le&&i==up,0,z,o,t,tr,f,fi,s,se,e,ni+1,get(o,t,tr,f,fi,s,se,e,ni+1));
	}
	if(!if_le&&!if_z) F[now_where][now]=ans;
	return ans;
}
inline void solve(){
	cin>>s;
	for(register short i=s.size()-1;i>=0;--i) a[++len]=s[i]-'0',++cnt[s[i]-'0'];
	all=get(cnt[1],cnt[2],cnt[3],cnt[4],cnt[5],cnt[6],cnt[7],cnt[8],cnt[9]); 
	printf("%lld",dfs(len,1,1,0,0,0,0,0,0,0,0,0,0,"")-1);//-1是减去的s这种情况，因为我们求的值s之前的数的个数
}
int main(){
	solve();
	return 0;
}
```