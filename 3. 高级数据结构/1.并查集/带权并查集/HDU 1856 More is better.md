房间里一共有10000000个人，你想选择其中的一些人跟你一起完成任务。

但是有一些限制，假设你选择了房间中的k个人，那么这k个人中的任何两个人都必须有直接或者间接的朋友关系。

你觉得人越多越好，请问你最多能选择多少人？

## Input

输入的第一行包含整数 n (0 ≤ n ≤ 100 000) - 表示有n个朋友关系. 以下n行各包含一对数字A和B，用一个空格隔开，表示A和B是朋友。(A ≠ B, 1 ≤ A, B ≤ 10000000)

## Output

输出你最多能选择多少人  

## Sample

|Inputcopy|Outputcopy|
|---|---|
|4<br>1 2<br>3 4<br>5 6<br>1 6<br>4<br>1 2<br>3 4<br>5 6<br>7 8|4<br>2|

## Hint

  
A and B are friends(direct or indirect), B and C are friends(direct or indirect),  
then A and C are also friends(indirect).  
  
In the first sample {1,2,5,6} is the result.  
In the second sample {1,2},{3,4},{5,6},{7,8} are four kinds of answers.

## 题解
我们这一题等效于求我们的最大连通块，我们只需要按照题目给定的要求连边后求即可，为此，我们可以采用带权并查集的方法。

```cpp
 #include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int N = 200005;
const int M = 10000001;
int Hash[M];
int cnt[N];
int father[N],dep[N];//统计每一个人的深度，启发式并查集

int _find(int x){
    if(x==father[x]) return x;
    return _find(father[x]);
}
int Union(int a,int b){
    int x = _find(a);
    int y = _find(b);
    if(x==y) return 0;
    if(dep[x]==dep[y]){//由深度小的向深度大的合并
        father[x] = y;
        dep[y]++;
    }else if(dep[x]<dep[y]){
        father[x] = y;
    }else father[y]=x;
    return 1;
}
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF){
        if(n==0) {
            printf("1\n");
            continue;
        }
        memset(Hash,-1,sizeof(Hash));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=2*n;i++){
            father[i] = i;
            dep[i]=0;
        }
        int k=0;
        for(int i=0;i<n;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            if(Hash[a]==-1){
                Hash[a]=++k;
            }
            if(Hash[b]==-1){
                Hash[b]=++k;
            }
            Union(Hash[a],Hash[b]);
        }
        for(int i=1;i<=2*n;i++){
            cnt[_find(i)]++;
        }
        int Max = -1;
        for(int i=1;i<=2*n;i++){
            Max = max(Max,cnt[i]);
        }
        printf("%d\n",Max);
    }
}
```

