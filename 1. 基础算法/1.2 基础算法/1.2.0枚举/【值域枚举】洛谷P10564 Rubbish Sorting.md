# [ICPC 2024 Xi'an I] Rubbish Sorting

## 题目描述

Bob has many pieces of rubbish. One day, he wants to sort them.
    
    
    
For every piece of rubbish, its type is expressed as a positive integer.
    
    
    
He has $q$ operations. For each operation, it is one of the following two operations.

- `1 s x` He tells you that the piece of rubbish named $s$ has a type of $x$.
- `2 s` He wants to ask you the type of rubbish $s$.


    
But his memories are not always accurate.
    
    
    
For each operation $2$, $s$ may not have appeared in the previous operation $1$ s.
    
    
    
We define the similarity of two strings $s_1$ and $s_2$ as $\sum_{i=1}^{\min\{|s_1|,|s_2|\}} [s_{1,i}=s_{2,i}]$.
    
    
    
Here all the strings' indexes start at $1$.
    
    
    
For a string $s$, its type is the type of string which has the maximum similarity to $s$ among all the strings that have appeared in the previous operations $1$ s. Note that if there are multiple strings that all have the maximum similarity to $s$, the type of $s$ is the minimum type of these strings' type.
    
    
    
Now, he wants you to solve this problem.

## 输入格式

The first line contains an integer $q(1\le q\le 3\times 10^5)$, which is the number of operations.
    
    
    
Next $q$ lines contain operations, one per line. They correspond to the description given in the statement.
    
    
    
It is guaranteed that for every operation $2$ there is at least one operation $1$ before it.
    
    
    
But some pieces of rubbish will have more than one type, you can consider it as the minimum type you have read.
    
    
    
The rubbish's names only consist of lowercase Latin letters.
    
    
    
$1 \le |s| \le 5, 1 \le x \le 10^9$

## 输出格式

For every operation $2$, you should print an integer in a single line that is the rubbish $s$ 's type.

## 样例 #1

### 样例输入 #1

```
4
1 aaa 1
2 aa
1 ab 2
2 bb
```

### 样例输出 #1

```
1
2
```


## 题解
本题我们注意到，我们的**字符串长度都很小**，我们于是考虑有没有**基于字符串长度的做法**。我们考虑枚举我们的最后的匹配长度是多少，我们发现，我们可以使用一个类似于**通配符**的方法，来找到我们的所有可能的匹配的模板有哪些。可以知道，对于一个字符串，通配符的数目不会超过 32 个，于是我们可以**存储我们的所有的通配符**，然后每一次通过我们的 map 来进行我们的 $o (1)$ 查找，我们每一次最多查找 32 次，因此我们一定可以通过本题。

```
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

unordered_map<int,int> mp;
const int p=1331;
const int mod1=1e9+7;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int q;
	cin>>q;
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int type;
			string s;
			cin>>s>>type;
			while(s.length()<5){
				s+='*';
			}
			for(int i=0;i<32;i++){
				//0-不使用通配符，1-使用通配符 
				int states=i;
				int hash_=0;
				bool valid=true;
				for(int j=0;j<5;j++){
					int u=((states)>>j)&1;
					if(u==0&&s[j]=='*'){
						valid=false;
						break;
					}else{
						if(u==0){
							hash_=(hash_*p+(s[j]-'a'+1))%mod1;
						}else{
							hash_=(hash_*p+('z'-'a'+1+1))%mod1;
						}
					}
				}
				if(valid==false){
					continue;
				}
				//cout<<regex<<" ";
				if(mp.count(hash_)){
					mp[hash_]=min(mp[hash_],type);
				}else{
					mp[hash_]=type;
				}
			}
		}else{
			string s;
			cin>>s;
			while(s.length()<5){
				s+='*';
			}
			int res_count=0;
			int res_type=0x3f3f3f3f3f;
			for(int i=0;i<32;i++){
				int states=i;
				int count=0;
				int hash_=0;
				bool valid=true;
				for(int j=0;j<5;j++){
					int u=((states)>>j)&1;
					if(u==0&&s[j]=='*'){
						valid=false;
						break;
					}else{
						if(u==0){
							hash_=(hash_*p+(s[j]-'a'+1))%mod1;
						}else{
							hash_=(hash_*p+('z'-'a'+1+1))%mod1;
						}
					}
					if(u==0){
						count++;
					}
				}
				if(valid==false){
					continue;
				}
				if(mp.count(hash_)){
					if(count>res_count){
						res_type=mp[hash_];
						res_count=count;
					}else if(count==res_count){
						res_type=min(res_type,mp[hash_]);
					}
				}
			}
			//cout<<res_count<<endl;
			cout<<res_type<<endl;
		}
	}
} 
```