给出一片森林。  
每棵树有两个参数，节点数𝑛和特殊参数𝑘，其中𝑘意义为：  
第𝑖个节点的父亲为第 $max\left( 1,\left[ \frac{i}{k} \right] \right)$ 个节点。两人进行游戏，每次可以删除一棵树（该数必须存在非叶子）或树中一个叶子。其中，叶子定义为度数为1的点。无法操作的人输。询问先手是否必胜。

## 题解
考虑一颗大小为 n 的树，$n=1$ 时，sg 为 0 。$n=2$ 时，$sg=0$,当我们 $n>2$ 时，我们有下面两种决策：第一种，我们直接减到 $n-1$,或者直接变没。于是我们的 sg 递推就有下面的结论 $sg(n)=mex(sg(n-1),0)$,我们就能得到结论，当我们的 n 为奇数时，我们 sg=1，否则我们 sg=2.

```cpp
#include<cstdio>
#include<algorithm>
#define fo(i,a,b) for(i=a;i<=b;i++)
using namespace std;
int i,j,k,l,t,n,m,ca;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main(){
    ca=read();
    while (ca--){
        n=read();
        t=0;
        fo(i,1,n){
            j=read();k=read();
            if (j==1) t^=1;
            else if (j>2){
                if (j%2==1) t^=1;
                else t^=2;
            }
        }
        if (t) printf("BOB\n");else printf("BEN\n");
    }
}
```