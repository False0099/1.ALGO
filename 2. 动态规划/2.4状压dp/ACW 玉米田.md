# 知识点
  ## [[状态压缩DP]]
# 题目
 农夫约翰的土地由 M×N个小方格组成，现在他要在土地里种植玉米。

非常遗憾，部分土地是不育的，无法种植。

而且，相邻的土地不能同时种植玉米，也就是说种植玉米的所有方格之间都不会有公共边缘。

现在给定土地的大小，请你求出共有多少种种植方法。

土地上什么都不种也算一种方法。

## 输入格式
第 1 行包含两个整数 M 和 N。

第 2.. M+1 行：每行包含 N 个整数 0或 1，用来描述整个土地的状况，1 表示该块土地肥沃，0 表示该块土地不育。

## 输出格式
输出总种植方法对 108 取模后的值。

## 数据范围
1≤M, N≤12
## 输入样例 ：
2 3
1 1 1
0 1 0
## 输出样例 ：
9

# 思路
***初始化还是和一般的状压 dp 思路相同，但是因为这题我们有限制条件，所以我们在进行状态转移方程的时候要去注意这个问题。（任何的限制条件都是只有在状态转移的时候去思考）

# AC 代码
```cpp
#include <iostream>
using namespace std;
vector<int> state;
vector<int> head[N];
bool check(int state){
	return  !(state & state << 1);
}
int main(){
	int n,m;
	cin>>n>>m;
	for (int i = 1; i <= n; i ++ )
        for (int j = 0; j < m; j ++ )
        {
            int t;
            cin >> t;
            w[i] += !t * (1 << j);
        }

	for(int i=0;i<1<<n;i++){
		if(check(i)){
			state.push_back(i);
		}
	}
	for(int i=0;i<state.size();i++){
		for(int j=0;j<state.size();j++){
			int a=state[i],b=state[j];
			if(!(a&b)){
				head[i].push_back(j);
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<state.size();j++){
			if(!state[j]&w[i]{
				for(auto k:head[i]){
					f[i][j]+=f[i-1][k];
				}
			}
		}
	}
}
```
# 备注
