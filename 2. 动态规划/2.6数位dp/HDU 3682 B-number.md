# 
## 题目描述
统计区间$[1,n]$ 中含有 '13' 且模 13 为 0 的数字有多少个。

## 输入格式

多组数据  
每行一个正整数n(1 ≤ n ≤ 1e9)  
一直输入到文件结束

## 输出格式

输出一行表示满足条件的答案

## 样例 #1

### 样例输入 #1

```
13
100
200
1000
```

### 样例输出 #1

```
1
1
2
2
```

## 题解
我们这一题遵循我们 dp 的规律，但是我们在传递的过程中，我们需要传递 1. 我们进行到哪一位 2. 我们到目前为止我们的总共模 13 为几 3. 上一个数字是否是 1 4. 是否出现过 13

那么我们的 dp 就可以写出

## 代码
```cpp
int dfs(int d,int mod,int last,int have,bool limit){
	if(d==n){
		return;
	}
	if(limit==0&&dp[len][mod][status][limit]!=-1) {
		return dp[len][mod][status]; 
	}
	int ans=0;
	int end=limit?digit[len]:9;
	for(int digit=0;digit<=end;digit++){
		int mod=(mod*10+digit)%13;
		if(status==2||(status==1&&digit==3)){
			ans+=dfs(len-1,mod_temp,2,limit&&digit==end);
		}else if(digit==1){
			ans+=dfs(len-1,mod_temp,1,limit&&digit==end);
		}else{
			ans+=dfs(len-1,mod_temp,0,limit&&digit==end);
		}
	}
	if(limit==0) dp[len][mod][status]=ans;
	return ans;
}
```