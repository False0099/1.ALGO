## Problem Description

In your childhood, do you crazy for collecting the beautiful cards in the snacks? They said that, for example, if you collect all the 108 people in the famous novel Water Margin, you will win an amazing award.  
  
As a smart boy, you notice that to win the award, you must buy much more snacks than it seems to be. To convince your friends not to waste money any more, you should find the expected number of snacks one should buy to collect a full suit of cards.

  

## Input

The first line of each test case contains one integer N (1 <= N <= 20), indicating the number of different cards you need the collect. The second line contains N numbers p1, p2, ..., pN, (p1 + p2 + ... + pN <= 1), indicating the possibility of each card to appear in a bag of snacks.  
  
Note there is at most one card in a bag of snacks. And it is possible that there is nothing in the bag.

  

## Output

Output one number for each test case, indicating the expected number of bags to buy to collect all the N different cards.  
  
You will get accepted if the difference between your answer and the standard answer is no more that 10^-4.

  

## Sample Input

1
0.1
2
0.1 0.4

  

## Sample Output

10.000
10.500

## 题解
本体是一个典型的收集类为题，我们对于本体来说，我们因为我们的范围较小，所以我们可以考虑通过我们的**状态压缩来解决**，我们设我们的 $f[S]$ 表示我们的**未收集情况为 S**时，我们的答案是多少，最后我们的答案是我们的 $f[0]$。

那么我们的**状态**可能会发生下面的转移：
1. 我们买了，啥都没中
2. 我们买了，和我们的 S 重复了
3. 我们买了，和我们的 S 不一样

对于我们的上面三种状态，我们的状态转移可以写成：
$S=\left( 1-\sum p \right)S+\sum_{i \in S} P_{i}S+\sum_{i \notin S}P_{i}\times(S\lor I)$。

最后，我们再给我们的各项加上我们的状态转移和我们的对应的转移条件，就可以得到我们的最终结果：
$dp[s]= （1+\sum dp[(1<<j)|s]*p[j]）/ \sum p[j]$
```
#include<cstdio>
#include<cstring>
using namespace std;
int n;
double p[20],dp[1<<20];
double sum1,sum2;
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++) scanf("%lf",&p[i]);
        for(int i=(1<<n)-2;i>=0;i--)
        {
            sum1=sum2=0;
            for(int j=0;j<n;j++)
             if(!((1<<j)&i))
             {
                 sum1+=p[j];
                 sum2+=dp[(1<<j)|i]*p[j];
             }
            dp[i]=(sum2+1)/sum1;
        }
        printf("%.4lf\n",dp[0]);
    }
}
```