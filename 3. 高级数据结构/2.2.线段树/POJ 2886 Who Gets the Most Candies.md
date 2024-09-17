_N_ children are sitting in a circle to play a game.

The children are numbered from 1 to _N_ in clockwise order. Each of them has a card with a non-zero integer on it in his/her hand. The game starts from the _K_-th child, who tells all the others the integer on his card and jumps out of the circle. The integer on his card tells the next child to jump out. Let _A_ denote the integer. If _A_ is positive, the next child will be the _A_-th child to the left. If _A_ is negative, the next child will be the (−_A_)-th child to the right.

The game lasts until all children have jumped out of the circle. During the game, the _p_-th child jumping out will get _F_(_p_) candies where _F_(_p_) is the number of positive integers that perfectly divide _p_. Who gets the most candies?

给定人数n，及他们的名字和卡片值，这n个人顺时针围成圈进行一场游戏，从第k个人开始，这个人出圈，并根据他的卡片值A来确定下一个出圈的人，正值为她顺时针的第A个人，负为逆时针的第-A个人。并根据出圈顺序来确定每人得到的糖数，假设Saber第x个出圈，那么Saber得到的糖果数为x的因子数。求该游戏中获得糖果最多的人和他获得的数量，如果存在多个最大值，则输出最先出圈的。

Input

There are several test cases in the input. Each test case starts with two integers _N_ (0 < _N_ ≤ 500,000) and _K_ (1 ≤ _K_ ≤ _N_) on the first line. The next _N_ lines contains the names of the children (consisting of at most 10 letters) and the integers (non-zero with magnitudes within 108) on their cards in increasing order of the children’s numbers, a name and an integer separated by a single space in a line with no leading or trailing spaces.  
多组样例  
第一行，n， k, 接下来n行，每行一个人的名字，和其卡片值。

Output

Output one line for each test case containing the name of the luckiest child and the number of candies he/she gets. If ties occur, always choose the child who jumps out of the circle first.

Sample

|Inputcopy|Outputcopy|
|---|---|
|4 2<br>Tom 2<br>Jack 4<br>Mary -1<br>Sam 1|Sam 3|

## 题解
首先是数学问题，可通过唯一分解定理或筛法打表计算出 n 个人时第几个出局的人的约数最多 f 1[n]，和约数的数量 f 2[n]，数据很小，不打表的话会超时。然后**进行 f 1[n]次循环**，
用线段树记录空位，k 表示当前需要从剩余人第几个位置寻找，只要推出 k，则转化为线段树的求位置. 也就是线段树求第 K 大。

```cpp
#include<cstdio>
using namespace std;
const int maxn=500005;

struct node1{
    char s[12];
    int val;
}boy[maxn];

struct node2{
    int l,r,sum;
}tr[maxn<<2];

int f1[40]={0,1,2,4,6,12,24,36,48,60,120,180,240,360,720,
            840,1260,1680,2520,5040,7560,10080,15120,
            20160,25200,27720,45360,50400,55440,83160,
            110880,166320,221760,277200,332640,498960,500001};
int f2[40]={0,1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,
            48,60,64,72,80,84,90,96,100,108,120,128,
            144,160,168,180,192,200};
int n,k;

void build(int v,int l,int r){
    tr[v].l=l,tr[v].r=r,tr[v].sum=r-l+1;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(v<<1,l,mid);
    build(v<<1|1,mid+1,r);
}

int update(int v,int k){
    --tr[v].sum;
    if(tr[v].l==tr[v].r)
        return tr[v].r;
    if(tr[v<<1].sum>=k) return update(v<<1,k);
    else return update(v<<1|1,k-tr[v<<1].sum);
}

int main(){
    while(~scanf("%d%d",&n,&k)){
        for(int i=1;i<=n;++i)
            scanf("%s%d",boy[i].s,&boy[i].val);
        int num,nump,nw=0,Mod=n,pos;
        for(int i=1;i<=39;++i)
            if(n>=f1[i]&&n<f1[i+1]){
                num=f1[i];
                nump=f2[i];
                break;
            }
        build(1,1,n);
        while(1){
            --Mod;
            pos=update(1,k);//选取第k个-1
            if(++nw==num) break;
            int tmp=boy[pos].val;
            if(tmp>0) 
                k=((k-1+tmp-1)%Mod+Mod)%Mod+1;
            else
                k=((k+tmp-1)%Mod+Mod)%Mod+1;
        }
        printf("%s %d\n",boy[pos].s,nump);
    }
    return 0;
}
```
　　            