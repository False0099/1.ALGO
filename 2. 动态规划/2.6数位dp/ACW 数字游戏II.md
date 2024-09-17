# 知识点
  ## [[数位DP]] [[动态规划]]
# 题目
 由于科协里最近真的很流行数字游戏。

某人又命名了一种取模数，这种数字必须满足各位数字之和 $mod N$   为 0。

现在大家又要玩游戏了，指定一个整数闭区间 $[a.b]$，问这个区间内有多少个取模数。

# 思路
·f 数组的处理
$F[i][j][k]$ 表示一共有 i 位，且最高位数字是 j，且所有位数字和模 N 结果为 k 的数的个数

状态转移： 因为第 i 位已经是 j，且所有数字之和模 N 为 k，所以我们考虑第 i-1 位，假设第 i-1 位数字是 x，由于 j 已经知道，
那么剩下的 i-1 位数字之和模 N 的结果就是 (k-j)%N，那么状态转移方程就是：

$F[i][j][k]=∑N−1 k=0∑9 x=0 f[i−1][x][mod (k−j, N)]$
·
·
# AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 12, M = 102;

int f[N][10][M];  //f[i][j][k] 表示一共有i位，且最高位数字是j，且所有位数字和模p位k的数字个数
int p;

int mod(int u,int v){
    return (u%v+v)%v;  //c++的%会得到负数，需要做一个偏移
}

void init(){
    memset(f,0,sizeof f);   //多组测试数据，f数组要清空
    for(int i = 0; i<=9; i++) f[1][i][i%p]++;

    for(int i = 2; i<N; i++)
        for(int j = 0; j<=9; j++)
            for(int k = 0; k<p; k++)
                for(int x = 0; x<=9; x++)
                    f[i][j][k] += f[i-1][x][mod(k-j,p)];
}

int dp(int n){
    if(!n) return 1;
    int res = 0,last = 0;

    vector<int> a;
    while(n) a.push_back(n%10),n/=10;

    int len = a.size()-1;
    for(int i = len; i>=0; --i){
        int x =a[i];    
        for(int j = 0; j<x; j++)  //第i位放0~x-1
            res += f[i+1][j][mod(-last,p)]; //0~i位，所以一共有i+1位

        last += x;
        if(!i && last % p == 0) res ++; 
    }
    return res;
}
int main()
{

    int l,r;
    while(cin>>l>>r>>p){
        init();
        cout<<dp(r)-dp(l-1)<<endl;
    }

    return 0;
}

作者：Moon_light
链接：https://www.acwing.com/solution/content/15556/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
