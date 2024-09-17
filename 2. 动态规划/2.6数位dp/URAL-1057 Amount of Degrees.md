## 题目描述
求出区间$[a,b]$中有多少个数能够写成 K 个 B 的不同幂次之和。

数据范围：1≤a≤b≤2^31-1, 1≤k≤20, 2≤B≤10。

17 = 2^4 + 2^0  
18 = 2^4 + 2^1  
20 = 2^4 + 2^2

## 输入格式
单组输入  
第一行两个整数a, b  
接下来两行分别为K，B


## 输出格式
输出一个整数，即个数。


## 样例 #1

### 样例输入 #1

```
15 20  
2  
2
```

### 样例输出 #1

```
3
```

## 题解
我们所求的数为互不相等的幂的和，亦其 B 进制表示的各位数字都只能是 0 和 1，但是，**我们可以把它转化成二进制的条件来进行判断**，我们首先把我们的原数字 n，转换成 k 进制，然后我们把**第一个非 0/1 的数位变成 1，并把后面的所以位置都设置成 1**，这一步是我们进行的一个**放缩**，之后我们只需要对这个**二进制串**进行我们的 dp，**即从 n 位中一共选择 k 位**，问**有多少可行的方案**。这样，我们就可以从了。



## 代码
```cpp
int dfs(int pos,int k,int limit){
	if(k==0) return 1;
	if(pos<0) return 0;
	if(!limt&&f[pos][k]!=-1) return f[pos][k];
	int up=limit?a[pos]:9;
	int tmp=0;
	for(int i=0;i<=up&&i<=1;i++){
		tmp+=dfs(pos-1,k-i,limit&&i==up);
	}
	if(!limit) f[pos][k]=tmp;
	return tmp;
}
int get_num(int x){
	int pos=0;
	while(x){
		a[pos++]=x%b;
		x/=b;
	}
	return dfs(pos-1,K,true);
}
int X,Y;
int main(){
	init();
	cin>>X>>Y>>K>>B;
	cout<<get_num(Y)-getnum(X-1)<<endl;
	return 0;
}
```