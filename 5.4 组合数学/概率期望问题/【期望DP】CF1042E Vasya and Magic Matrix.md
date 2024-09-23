# Vasya and Magic Matrix

## 题面翻译

一个 $n$ 行 $m$ 列的矩阵, 每个位置有权值 $a_{i,j}$

给定一个出发点, 每次可以等概率的移动到一个权值小于当前点权值的点（不能移动就停止）,同时得分加上两个点之间欧几里得距离的平方 (欧几里得距离: $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$)), 问得分的期望, 对 998244353 取模。

## 题目描述

Vasya has got a magic matrix $ a $ of size $ n \times m $ . The rows of the matrix are numbered from $ 1 $ to $ n $ from top to bottom, the columns are numbered from $ 1 $ to $ m $ from left to right. Let $ a_{ij} $ be the element in the intersection of the $ i $ -th row and the $ j $ -th column.

Vasya has also got a chip. Initially, the chip is in the intersection of the $ r $ -th row and the $ c $ -th column (that is, in the element $ a_{rc} $ ). Vasya performs the following process as long as possible: among all elements of the matrix having their value less than the value of the element with the chip in it, Vasya randomly and equiprobably chooses one element and moves his chip to this element.

After moving the chip, he adds to his score the square of the Euclidean distance between these elements (that is, between the element in which the chip is now and the element the chip was moved from). The process ends when there are no elements having their values less than the value of the element with the chip in it.

Euclidean distance between matrix elements with coordinates $ (i_1, j_1) $ and $ (i_2, j_2) $ is equal to $ \sqrt{(i_1-i_2)^2 + (j_1-j_2)^2} $ .

Calculate the expected value of the Vasya's final score.

It can be shown that the answer can be represented as $ \frac{P}{Q} $ , where $ P $ and $ Q $ are coprime integer numbers, and $ Q \not\equiv 0~(mod ~ 998244353) $ . Print the value $ P \cdot Q^{-1} $ modulo $ 998244353 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ $ (1 \le n, m \le 1\, 000) $ — the number of rows and the number of columns in the matrix $ a $ .

The following $ n $ lines contain description of the matrix $ a $ . The $ i $ -th line contains $ m $ integers $ a_{i 1}, a_{i 2}, \dots, a_{im} ~ (0 \le a_{ij} \le 10^9) $ .

The following line contains two integers $ r $ and $ c $ $ (1 \le r \le n, 1 \le c \le m) $ — the index of row and the index of column where the chip is now.

## 输出格式

Print the expected value of Vasya's final score in the format described in the problem statement.

## 样例 #1

### 样例输入 #1

```
1 4
1 1 2 1
1 3
```

### 样例输出 #1

```
2
```

## 样例 #2

### 样例输入 #2

```
2 3
1 5 7
2 3 1
1 2
```

### 样例输出 #2

```
665496238
```

## 提示

In the first example, Vasya will move his chip exactly once. The expected value of the final score is equal to $ \frac{1^2 + 2^2+ 1^2}{3} = 2 $ .

## 题解
既然是一个**期望有关的题目**，我们就需要去分析我们的**每一步的转移过程**和对应的结果是多少。

我们发现，我们本体只能从我们的**大的格子转移到我们的小的格子**，因此，我们不妨将我们的格子离散化为一个序列，然后对于我们的序列按照权值排序后进行处理。

我们的条件同时说明：我们的转移之间的路径是固定的，是一个**有向无环图**，这也是我们的一般的期望 DP 所遇到的情况，这种情况下，我们就可以写出我们的转移方程：

$$
dp[i]=\frac{\sum dp[j]+dist(i,j)}{cnt}
$$
其中我们的 cnt 表示我们的总个数

观察到我们的转移是可以转换为我们的下面的式子：
$$f_i=\frac{1}{\text{tot}}\sum_{a_i>a_j}x_i^2+x_j^2+y_i^2+y_j^2-2(y_iy_j+x_ix_j)+f_j$$

于是，我们就可以通过我们的前缀和预处理来完成本题（取模部分有点长）

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF=0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int,int> PII;
void init(){
    
}
struct node{
    int x;
    int y;
    int val;
};
int qmi(int a,int b,int mod){
    int res=1;
    while(b){
        if(b&1){
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}
const int mod=998244353;
void solve(){
    int n,m;
    cin>>n>>m;
    vector<node> a;
    a.push_back({1,1,1});
    vector<int> f(n*m+1,0);
    vector<int> sum(n*m+1,0);
    vector<int> sumxx(n*m+1,0);
    vector<int> sumyy(n*m+1,0);
    vector<int> sumx(n*m+1,0);
    vector<int> sumy(n*m+1,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int u;
            cin>>u;
            a.push_back({i,j,u});
//            a[i*m+j]={i,j,u};
        }
    }
    sort(begin(a)+1,end(a),[&](node a,node b){
        return a.val<b.val;
    });
    int last_val_idx=1;
    for(int i=1;i<=n*m;i++){
        if(a[i].val!=a[i-1].val&&i!=1){
            last_val_idx=i-1;
        }
        sumx[i]=(sumx[i-1]+a[i].x)%mod;
        sumxx[i]=(sumxx[i-1]+a[i].x*a[i].x)%mod;
        sumy[i]=(sumy[i-1]+a[i].y)%mod;
        sumyy[i]=(sumyy[i-1]+a[i].y*a[i].y)%mod;
        if(i==1){
            f[i]=0;
            sum[i]=sum[i-1]+f[i];
            last_val_idx=1;
            continue;
        }
        if(last_val_idx==1&&a[i].val==a[last_val_idx].val){
            f[i]=0;
            sum[i]=sum[i-1]+f[i];
            continue;
        }
//        cerr<<sumx[last_val_idx]<<" "<<sumy[last_val_idx]<<endl;
        f[i]=sum[last_val_idx]%mod;
        f[i]=(f[i]+sumxx[last_val_idx])%mod;//y[i]^2
        f[i]=(f[i]+sumyy[last_val_idx])%mod;//x[i]^2
        f[i]=(f[i]-2*a[i].x*sumx[last_val_idx]%mod+mod)%mod;//2*x[i]*x[n]
        f[i]=(f[i]-2*a[i].y*sumy[last_val_idx]%mod+mod)%mod;//2*y[i]*y[n]
        f[i]=(f[i]+(a[i].x*a[i].x)%mod*last_val_idx%mod)%mod;
        f[i]=(f[i]+(a[i].y*a[i].y)%mod*last_val_idx%mod)%mod;
        f[i]=(f[i]*qmi(last_val_idx,mod-2,mod))%mod;
        sum[i]=(sum[i-1]+f[i])%mod;
        //cerr<<last_val_idx<<" ";
        //cerr<<sumxx[last_val_idx]+sumyy[last_val_idx]-2*a[i].x*sumx[last_val_idx]-2*a[i].y*sumy[last_val_idx]+a[i].x*a[i].x*last_val_idx+a[i].y*a[i].y*last_val_idx<<endl;
//        f[i]=(-2*a[i].y*sumy[last_val_idx]%mod)+mod)%mod*qmi(i-1,mod-2,mod)%mod;
        //f[i]=(f[i]+(sum[last_val_idx]+getdist(i,last_val_idx)*qmi(last_val_idx,mod-2,mod))%mod)%mod;
        //cerr<<f[i]<<" "<<last_val_idx<<" "<<endl;
//        sum[i]=(sum[i-1]+f[i])%mod;
    }
    int start,end;
    cin>>start>>end;
    start--;
    end--;
    for(int i=1;i<=n*m;i++){
        if(a[i].x==start&&a[i].y==end){
            cout<<f[i]<<endl;
            return;
        }
    }
}
signed main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int t;
    t=1;
//    cin>>t;
    init();
    while(t--){
        solve();
    }
}
```