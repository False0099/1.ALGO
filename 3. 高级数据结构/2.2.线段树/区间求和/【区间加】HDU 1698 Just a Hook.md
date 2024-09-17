In the game of DotA, Pudge’s meat hook is actually the most horrible thing for most of the heroes. The hook is made up of several consecutive metallic sticks which are of the same length.  
  

![](https://vj.csgrandeur.cn/06e06a8171aa23abddf26dca64f45d8c?v=1694941669)

  
  
Now Pudge wants to do some operations on the hook.  
  
Let us number the consecutive metallic sticks of the hook from 1 to N. For each operation, Pudge can change the consecutive metallic sticks, numbered from X to Y, into cupreous sticks, silver sticks or golden sticks.  
The total value of the hook is calculated as the sum of values of N metallic sticks. More precisely, the value for each kind of stick is calculated as follows:  
  
For each cupreous stick, the value is 1.  
For each silver stick, the value is 2.  
For each golden stick, the value is 3.  
  
Pudge wants to know the total value of the hook after performing the operations.  
You may consider the original hook is made up of cupreous sticks.  

## Input

The input consists of several test cases. The first line of the input is the number of the cases. There are no more than 10 cases.  
For each case, the first line contains an integer N, 1<=N<=100,000, which is the number of the sticks of Pudge’s meat hook and the second line contains an integer Q, 0<=Q<=100,000, which is the number of the operations.  
Next Q lines, each line contains three integers X, Y, 1<=X<=Y<=N, Z, 1<=Z<=3, which defines an operation: change the sticks numbered from X to Y into the metal kind Z, where Z=1 represents the cupreous kind, Z=2 represents the silver kind and Z=3 represents the golden kind.  

## Output

For each case, print a number in a line representing the total value of the hook after the operations. Use the format in the example.  

## Sample

|Inputcopy|Outputcopy|
|---|---|
|1<br>10<br>2<br>1 5 2<br>5 9 3|Case 1: The total value of the hook is 24.|


## 题解
我们这一题需要维护：
1. 每一次让我们区间的种类+1
2. 种类为 3 时不能再改变
3. 区间求和

（我们这一题的难点在于种类为 3 时不能再增加，这个就可以看作我们求根号的反向操作，我们再根号哪一题中，如果我们区间的和已经都为 1 了，那么我们就直接暴力修改。这一题我们也一样，如果我们的区间和已经是 $3*length$ 了，我们就直接跳过即可，或者暴力修改也行。）

小丑看错题意了，我们只需要把我们的区间完全修改就可以了，这个就是我们线段树区间修改的模板。（草！）

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
#include<cstring>
#include<set>
#include<map>
#include<queue>
#include<string>
#include<cmath>
 
using namespace std;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
const int MAXN=1000000;
struct {
    int l;
    int r;
    int sum;
}tree[MAXN<<2];
int change[MAXN<<2];//存储我们区间的等级
void push_up(int rt){
    tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
}
void push_down(int l,int r,int rt){
    if (change[rt]){
        if (l==r) {
            change[rt]=0;
            return;
        }
        int mid=(l+r)>>1;
        tree[rt<<1].sum=(mid-l+1)*change[rt];
        tree[rt<<1|1].sum=(r-mid)*change[rt];
        change[rt<<1]=change[rt];
        change[rt<<1|1]=change[rt];
        change[rt]=0;
    }
}
 
void build(int l,int r,int rt){
    tree[rt].sum=0;
    if (l==r) {
        tree[rt].sum=1;
        return;
    }
    int mid=(l+r)>>1;
    build(lson);
    build(rson);
    push_up(rt);
}
 
void update(int a,int b,int c,int l,int r,int rt){
    push_down(l,r,rt);
    if (a<=l && r<=b){
        tree[rt].sum=(r-l+1)*c;
        change[rt]=c;
        return;
    }
    push_down(l,r,rt);
    int mid=(l+r)>>1;
    if (a<=mid) update(a,b,c,lson);
    if (b>mid) update(a,b,c,rson);
    push_up(rt);
}
 
int main()
{
    int C, N, Q;
    int a,b,c;
    scanf("%d",&C);
    for (int i = 1; i <= C; ++i) {
        memset(change,0, sizeof(change));
        scanf("%d",&N);
        build(1,N,1);
        scanf("%d",&Q);
        while (Q--){
            scanf("%d %d %d",&a,&b,&c);
            update(a,b,c,1,N,1);
//            cout<<tree[1].sum;
        }
        printf("Case %d: The total value of the hook is %d.\n",i,tree[1].sum);
    }
    return 0;
}
```