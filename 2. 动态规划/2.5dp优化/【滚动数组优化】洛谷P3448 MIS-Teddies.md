# [POI 2006] MIS-Teddies

## 题目描述

Byteoian 是一家专业生产儿童玩具的公司。他们生产的玩具质量上乘，广受好评。

但最近，有人发现他们生产的泰迪熊存在致命缺陷。总共有四种泰迪熊型号：$A1$，$A2$，$B1$，$B2$，一旦将三个字母相同或数字相同的泰迪熊放在一块，就会对泰迪熊造成致命损坏。

如果一种摆放泰迪熊的方案中不存在连续三个字母相同或数字相同的泰迪熊，则称这种摆放方案是**安全的**。

现在你收集了一些泰迪熊，你想要知道有多少种安全的摆放泰迪熊的方案。由于安全的方案可能较多，请输出方案数对 $1\,000\,000$ 取模的结果。

## 输入格式

输入包含四个整数：$n_{A1},n_{A2},n_{B1},n_{B2}$，分别代表 $A1$ 型，$A2$ 型，$B1$ 型，$B2$ 型泰迪熊的数量。

## 输出格式

输出一个整数，即安全摆放泰迪熊的方案数对 $1\,000\,000$ 取模的结果。

## 样例 #1

### 样例输入 #1

```
0 1 2 1
```

### 样例输出 #1

```
6
```

## 提示

$0 \leq n_{A1},n_{A2},n_{B1},n_{B2} \leq 38$。

## 题解
本题我们的思路就是设置我们的 $dp[n][a][b][c][s_{1}][s_{2}][s_{3}]$ 来表示我们已经选择了前 $n$ 个，并且我们用了 $a$ 个 $A_{1}$, $b$ 个 $A_{2}$，$c$ 个 $B_{1}$, $d$ 个 $B_{2}$ 的方案数是多少。

于是，我们就可以通过我们的 dp 来进行转移。但是我们如果只想这么做，我们连样例都无法通过，我们需要通过我们的滚动数组来优化我们的空间，我们设置 $dp[o][a][b][c][s_{1}][s_{2}][s_{3}]$ 来表示我们的当前状态。但是，我们发现这样还是不能通过，我们考虑压缩掉我们的某一个状态，比如我们的 $s_{1}$,我们发现这个 $s_{1}$ 和我们的最终结果无关，所以我们可以直接删除。

```
#include <bits/stdc++.h>
using namespace std;
const int A=40;
const int B=40;
const int C=40;
int a,b,c,d;
int f[2][A][B][C][4][4];
const int mod=1000000;
bool check(int a,int b,int c){
	int count_digit_2=((a&1)+(b&1)+(c&1));
	int count_digit_1=3-count_digit_2;
	int count_alpha_a=((a>=2)+(b>=2)+(c>=2));
	int count_alpha_b=3-count_alpha_a;
	if(count_digit_2>=3||count_digit_1>=3||count_alpha_a>=3||count_alpha_b>=3){
		return false;
	}
	return true;
}
bool check(int j,int k,int l,int s1,int s2,int s3){
	int cnta1=j;
	int cnta2=k;
	int cntb1=l;
	int cntb2=3-j-k-l;
	int cnta1_=((s1==0)+(s2==0)+(s3==0));
	int cnta2_=((s1==1)+(s2==1)+(s3==1));
	int cntb1_=((s1==2)+(s2==2)+(s3==2));
	int cntb2_=((s1==3)+(s2==3)+(s3==3));
	if(cnta1==cnta1_&&cntb1==cntb1_&&cnta2==cnta2_&&cntb2==cntb2_){
		return true;
	}
	return false;
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>a>>b>>c>>d;
	int sum=a+b+c+d;
	//check(2,2,3);
	if(sum==2){
		int type=(a!=0)+(b!=0)+(c!=0)+(d!=0);
		if(type>1){
			cout<<2<<endl;
			return 0;
		}else{
			cout<<1<<endl;
			return 0;
		}
	}
	if(sum<=1){
		cout<<1<<endl;
		return 0;
	}
	for(int j=0;j<=a&&j<=3;j++){
		for(int k=0;k<=b&&k+j<=3;k++){
			for(int l=0;l<=c&&l+j+k<=3;l++){
				int m=3-j-k-l;
				if(m>d){
					continue;
				}
				for(int s1=0;s1<4;s1++){
					for(int s2=0;s2<4;s2++){
						for(int s3=0;s3<4;s3++){
							if(check(j,k,l,s1,s2,s3)){
								//cout<<j<<" "<<k<<" "<<l<<" "<<m<<" "<<s1<<" "<<s2<<" "<<s3<<endl;	
								f[0][j][k][l][s2][s3]+=check(s1,s2,s3);
							}
						}
					}
				}
			}
		}
	}
	int o=1;
	int cnt=0;
	for(int i=3;i<sum;i++){
		if(i!=3){
			memset(f[o],0,sizeof f[o]);
		}
		for(int j=0;j<=a&&j<=i;j++){//j表示我们的A1 
			for(int k=0;k<=b&&j+k<=i;k++){//k表示我们的A2 
				for(int l=0;l<=c&&l+j+k<=i;l++){//l表示我们的B1
					int m=i-j-k-l; 
					//assert(m>=0);
					if(m>d){
						continue;
					}
						for(int s2=0;s2<4;s2++){
							for(int s3=0;s3<4;s3++){
								
								if(check(s2,s3,0)){
									f[o][j+1][k][l][s3][0]=(f[o][j+1][k][l][s3][0]+f[o^1][j][k][l][s2][s3])%mod;
								}
								if(check(s2,s3,1)){
									f[o][j][k+1][l][s3][1]=(f[o][j][k+1][l][s3][1]+f[o^1][j][k][l][s2][s3])%mod;
								} 
								if(check(s2,s3,2)){
									f[o][j][k][l+1][s3][2]=(f[o][j][k][l+1][s3][2]+f[o^1][j][k][l][s2][s3])%mod;
								}
								if(check(s2,s3,3)){
									f[o][j][k][l][s3][3]=(f[o][j][k][l][s3][3]+f[o^1][j][k][l][s2][s3])%mod;
								}
							}
						}
					}
				
			} 
		} 
		o^=1;
	}
	int ans=0;
	for(int s2=0;s2<4;s2++){
		for(int s3=0;s3<4;s3++){
			ans=(ans+f[o^1][a][b][c][s2][s3])%mod;
		}
	}
	cout<<ans<<endl;
}

```