Ouroboros is a mythical snake from ancient Egypt. It has its tail in its mouth and continously devours itself.  
  
The Ouroboros numbers are binary numbers of 2^n bits that have the property of "generating" the whole set of numbers from 0 to 2^n - 1. The generation works as follows: given an Ouroboros number, we place its 2^n bits wrapped in a circle. Then, we can take 2^n groups of n bits starting each time with the next bit in the circle. Such circles are called Ouroboros circles for the number n. We will work only with the smallest  
Ouroboros number for each n.  
  
Example: for n = 2, there are only four Ouroboros numbers. These are 0011;0110;1100; and 1001. In this case, the smallest one is 0011. Here is the Ouroboros circle for 0011:  

![](https://vj.csgrandeur.cn/0e68cdc35f3b5bf5457ff37df28aad76?v=1697124779)

  
The table describes the function o(n;k) which calculates the k-th number in the Ouroboros circle of the smallest Ouroboros number of size n. This function is what your program should compute.  

Input

The input consists of several test cases. For each test case, there will be a line containing two integers n and k (1<=n<=15; 0<=k<2^n). The end of the input file is indicated by a line containing two zeros. Don抰 process that line.

Output

For each test case, output o(n;k) on a line by itself.

Sample

|Inputcopy|Outputcopy|
|---|---|
|2 0<br>2 1<br>2 2<br>2 3<br>0 0|0<br>1<br>3<br>2|

## 题解
输入一个 n，一个 x，就有一个只包含 $2^n$ 个数的圆盘，这一题类似于我们的 code 哪一题，要用我们的数位去建一个图，然后再去判断我们是否存在一定的欧拉回路即可。

```cpp
#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
#include<cmath>  
#include<vector>  
#include<queue>  
#include<algorithm>  
#define caseT int _T;scanf("%d",&_T);for(int q=1; q<=_T; ++q)
using namespace std;  
typedef long long LL;  
const int mod=1e9+7;  
const int MX=1<<16;  
const int INF=0x3f3f3f3f;    
int n,x,k;
int vis[MX];
vector<int>g[MX];
int pre[MX];
int V[MX];
void Fluery(int u){
    for(int i=0;i<g[u].size();++i){
        int id=g[u][i];
        if(vis[id])continue;
        vis[id]=1;
        Fluery(V[id]);
    }
    pre[k++]=u&1;
}
void init(){
    for(int i=0;i<=(1<<n);++i)g[i].clear();
    k=0;
    memset(vis,0,sizeof(vis));
    memset(pre,0,sizeof(pre));/***这里数组一定要清零，因为后面是直接补位**/
}
int main(){
    while(~scanf("%d%d",&n,&x)&&n){
        if(n==1){
            if(x==0) printf("0\n");
            else printf("1\n");
            continue;    
        }
        init();
        int state=1<<(n);
        for(int i=0;i<state;++i){
            int L=i>>1;
            int R=i^(i&(1<<(n-1)));//将第n位置为0
            g[L].push_back(i);
            V[i]=R;
        }
        vis[0]=1;
        Fluery(0);//此时k=2^n,需要生成2^n+n-1长度的序列才行
        k+=n-1;//补齐后面的n-1个0
        k-=x;
        int sum=0;
        for(int i=k-1,j=0;j<n;++j,--i){
            sum=sum*2+pre[i];
        }
        printf("%d\n",sum );
    }
    return 0;
}

```