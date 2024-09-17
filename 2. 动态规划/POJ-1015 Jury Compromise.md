在遥远的国家佛罗布尼亚，嫌犯是否有罪，须由陪审团决定。陪审团是由法官从公众中挑选的。先随机挑选 n 个人作为陪审团的候选人，然后再从这 n 个人中选 m 人组成陪审团。选 m 人的办法是： 控方和辩方会根据对候选人的喜欢程度，给所有候选人打分，分值从0到20。为了公平起见，法官选出陪审团的原则是：选出的 m 个人，必须满足辩方总分和控方总分的差的绝对值最小。如果有多种选择方案的辩方总分和控方总分的之差的绝对值相同，那么选辩控双方总分之和最大的方案即可。

## Input

输入包含多组数据。每组数据的第一行是两个整数n和m，n是候选人数目，m是陪审团人数。注意，1<=n<=200, 1<=m<=20 而且 m<=n。接下来的n行，每行表示一个候选人的信息，它包含2个整数，先后是控方和辩方对该候选人的打分。候选人按出现的先后从1开始编号。两组有效数据之间以空行分隔。最后一组数据n=m=0

## Output

对每组数据，先输出一行，表示答案所属的组号,如 'Jury #1', 'Jury #2', 等。接下来的一行要象例子那样输出陪审团的控方总分和辩方总分。再下来一行要以升序输出陪审团里每个成员的编号，两个成员编号之间用空格分隔。每组输出数据须以一个空行结束。

## Sample Input

4 2 
1 2 
2 3 
4 1 
6 2 
0 0 

## Sample Output

Jury #1 
Best jury has value 6 for prosecution and value 4 for defence: 
 2 3 

## Hint

If your solution is based on an inefficient algorithm, it may not execute in the allotted time.

## 题解
我们这一题要求最小化 $|\sum_{i=1}^m(a_{i}-b_{i})|$,于是我们就考虑到先计算出我们每一个位置上的 $c_{i}=a_{i}-b_{i}$,然后，我们再去求我们的 $min\left( |\sum_{i=1}^nc_{i}| \right)$。并且在我们的上面最小的情况下，我们要满足我们的总和尽可能地大。

这是一道具有多个“体积维度的”0/1 背包问题，把 N 个候选人看作 N 个物品，那么每个物品有下面三种体积：
1. 人数
2. 辩方得分
3. 控方得分
因此，我们依次考虑每个候选人是否应该选入评审团，并把我们两方的得分差绝对值作为我们的另外一维的限制，相当于我们对于每一个给定的得分差，枚举我们能否存在一种合理的方案，使得我们达到这一个分差。

于是我们的转移就变为 $f[j][k]=max(f[j][k],f[j-1][k-(a[i]-b[i])]+a[i]+b[i])$,同时，我们还要关注我们的分差。这里我们其实已经用我们的滚动数组优化了一个维度，所以这里的 $f[j][k]$ 其实相当于我们的 $f[i-1][j][k]$,所以我们的转移时没有毛病的
```cpp
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
 
int f[30][1000];//f[j][k]表示取j个候选人，辩控差为k的方案中
//辩控和最大的那个方案
int Path[30][1000];
//记录了最后一个候选人的编号
int P[300];
int D[300];
int Answer[30]; //存放最终方案的人选
 
bool cmp(int a,int b){
    if(a<b)
        return true;
    else
        return false;
}
 
int main(){
    int i,j,k;
    int t1,t2;
    int n,m;
    int nMinP_D;
    int iCase;    //测试编号
    iCase = 0;
    while(scanf("%d %d",&n,&m)){
        if(n==0 && m==0)    break;
        iCase++;
        for(i=1;i<=n;i++){
            scanf("%d %d",&P[i],&D[i]);
        }
        memset(f,-1,sizeof(f));
        memset(Path,0,sizeof(Path));
        nMinP_D = m*20;
        f[0][nMinP_D] = 0;
        for(j=0;j<m;j++){
            for(k=0;k<=nMinP_D*2;k++){
                if(f[j][k]>=0){
                    for(i=1;i<=n;i++){
                        if(f[j][k]+P[i]+D[i]>f[j+1][k+P[i]-D[i]]){
                                t1 = j;
                                t2 = k;
                                while(t1>0&&Path[t1][t2]!=i){    //排除掉选过的情况
                                        t2 -= P[Path[t1][t2]] - D[Path[t1][t2]];
                                        t1--;
                                }
                                if(t1 == 0){
                                        f[j+1][k+P[i]-D[i]] = f[j][k]+P[i]+D[i];
                                        Path[j+1][k+P[i]-D[i]] = i;
                                }
                        }
                    }
                }
            }
        }
                i = nMinP_D;
                j = 0;
                while(f[m][i+j]<0&&f[m][i-j]<0) j++;  //找到辩控差最小的情况
                if(f[m][i+j]>f[m][i-j]) k=i+j;
                else k=i-j;
                printf("Jury #%d\n",iCase);
                printf("Best jury has value %d for prosecution and value %d for defence:\n",(k+f[m][k]-nMinP_D)/2,(f[m][k]+nMinP_D-k)/2); //相当于解一个方程
                //x+y=f[m][k];x-y+MinP_D=k
                for(i=1;i<=m;i++){
                    Answer[i] = Path[m-i+1][k];
                    k -= P[Answer[i]] - D[Answer[i]]; //向上回溯解得 选中的 人
                }
                sort(Answer+1,Answer+m+1,cmp);
                for(i=1;i<=m;i++)
                printf(" %d",Answer[i]);
                printf("\n\n");
                                                    
    }
    
    return 0;
}
```

