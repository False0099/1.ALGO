# 知识点
  ## [[概率问题]] [[推公式]] [[unsolved]] [[概率DP]]
# 题目
	 嘤嘤有一个只由小写字母组成的字符串，她希望把这个字符串变得跟她一样可爱。  
  
        嘤嘤有一个魔法，可以将字符串中的一个小写字母变成一个小写字母（**可以和原字母相同**），这个魔法可以使用 k 次。  
  
        一个字符串的可爱值定义为这个字符串中含有的 'y' , 'k' , 'a' , 'w' , 'i' 这五种字母的数量，例如"yykawaii"的可爱值是8，"zjkgg"的可爱值是1，而"qcjj"的可爱值……  
  

        由于嘤嘤正在被qcjj追杀，所以嘤嘤留下的魔法只能随机使用了（随机将字符串中的一个小写字母随机变成一个小写字母，可能和原字母相同）。  
  
        现在，嘤嘤给出字符串和 k ，她想知道她的字符串在随机使用 k 次魔法后，可爱值的期望是多少。  

  

        PS：qcjj其实非常可爱哦！（绝对不是qcjj要我加的）附一张qcjj头像同款的白毛萝莉图。

  

        世界名画——《喂！不许这样盯着我看，你这个死萝莉控！！！》（德莉莎·阿波卡利斯）（图片加载失败）

# 思路
$dp_{a,k}$ 表示有 a 个可爱字符情况下施法 $k$ 次得到的期望，那么我们可以根据我们的施法情况进行分类：

1. 施法把可爱字符换成了不可爱字符
2. 施法把可爱字符换成了可爱字符
3. 施法把不可爱字符换成了可爱字符
4. 施法把不可爱字符换成了可爱字符

我们分别计算这四种情况发生的概率是多少，然后再用概率乘上我们的权值就是我们的答案。
```c++
long long dfs(int a,int k){
    if(dp[a][k]!=-1)return dp[a][k];
    if(k==0)return a;
    dp[a][k]=dfs(a,k-1)*a%mod*invn%mod*5*inv26%mod;
    dp[a][k]%=mod;
    if(a>0)dp[a][k]+=dfs(a-1,k-1)*a%mod*invn%mod*21%mod*inv26%mod;
    dp[a][k]%=mod;
    if(a<n)dp[a][k]+=dfs(a+1,k-1)*(n-a)%mod*invn%mod*5%mod*inv26%mod;
    dp[a][k]%=mod;
    dp[a][k]+=dfs(a,k-1)*(n-a)%mod*invn%mod*21%mod*inv26%mod;
    dp[a][k]%=mod;
    return dp[a][k];
}
```
我们的期望就是我们的概率乘以我们的权值，相对来说比较简单。
# AC 代码
```c++
#include<bits/stdc++.h>
using namespace std;
long long n,k;
const long long mod=1e9+7;
long long dp[2023][2023];
int f[200];
void exgcd(long long a, long long b, long long& x, long long& y) { 
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}
long long inv(long long a){
	long long x,y;
	exgcd(a,mod,x,y);
	return (x%mod+mod)%mod;
}
long long invn,inv26;
long long dfs(int a,int k){
    if(dp[a][k]!=-1)return dp[a][k];
    if(k==0)return a;
    dp[a][k]=dfs(a,k-1)*a%mod*invn%mod*5*inv26%mod;
    dp[a][k]%=mod;
    if(a>0)dp[a][k]+=dfs(a-1,k-1)*a%mod*invn%mod*21%mod*inv26%mod;
    dp[a][k]%=mod;
    if(a<n)dp[a][k]+=dfs(a+1,k-1)*(n-a)%mod*invn%mod*5%mod*inv26%mod;
    dp[a][k]%=mod;
    dp[a][k]+=dfs(a,k-1)*(n-a)%mod*invn%mod*21%mod*inv26%mod;
    dp[a][k]%=mod;
    return dp[a][k];//返回我们的期望
}
int main(){
    f['y']=f['k']=f['a']=f['w']=f['i']=1;
    string s;
    memset(dp,-1,sizeof(dp));
    int a=0,b=0;
    cin>>n>>k;
    invn=inv(n);
    inv26=inv(26);
    cin>>s;
    for(auto c:s)
        if(f[c])a++;
    cout<<dfs(a,k)<<endl;
}
```
# 备注
