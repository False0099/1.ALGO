# [USACO 06 FEB] Backward Digit Sums G/S

## 题面翻译

有这么一个游戏：

写出一个 $1\sim n$ 的排列 $a$，然后每次将相邻两个数相加，构成新的序列，再对新序列进行这样的操作，显然每次构成的序列都比上一次的序列长度少 $1$，直到只剩下一个数字位置。

下面是一个例子：

- $3,1,2,4$；
- $4,3,6$；
- $7,9$；
- $16$。

最后得到 $16$ 这样一个数字。

现在想要倒着玩这样一个游戏，如果知道 $n$，以及最后得到的数字的大小 $sum$，请你求出最初序列 $a_i$（应该是一个 $1\sim n$ 的排列）。若答案有多种可能，则输出字典序最小的那一个。

我们称序列 $a=\lang a_1,a_2,\cdots,a_n\rang$ 的字典序小于序列 $b=\lang b_1,b_2,\cdots,b_n\rang$ 的字典序，当且仅当存在一个位置 $p$，满足 $a_1=b_1,a_2=b_2,\cdots,a_{p-1}=b_{p-1},a_p<b_p$。

## 题目描述

`FJ` and his cows enjoy playing a mental game. They write down the numbers from $1$ to$ N (1 \le N  \le 10)$ in a certain order and then sum adjacent numbers to produce a new list with one fewer number.  They repeat this until only a single number is left.  For example, one instance of the game (when $N=4$) might go like this:

```cpp
    3   1   2   4
      4   3   6
        7   9
         16
```
Behind `FJ` 's back, the cows have started playing a more difficult game, in which they try to determine the starting sequence from only the final total and the number $N$.  Unfortunately, the game is a bit above `FJ` 's mental arithmetic capabilities.


Write a program to help `FJ` play the game and keep up with the cows.

## 输入格式

共一行两个正整数 $n,sum$。

## 输出格式

输出包括一行，为字典序最小的那个答案。

当无解的时候，请什么也不输出。

## 样例 #1

### 样例输入 #1

```
4 16
```

### 样例输出 #1

```
3 1 2 4
```

## 提示

- 对于 $40\%$ 的数据，$1\le n\le 7$；  
- 对于 $80\%$ 的数据，$1\le n \le 10$；
- 对于 $100\%$ 的数据，$1\le n \le 12$，$1\le sum\le 12345$。
##  题解
我们一般面对这种问题一般有两种方法，一种是枚举我们的所有答案，然后我们再去检查这个是否合规，另一种是倒着拆分。我们这一题，显然使用第一种方法更优。
如果要枚举，我们当然可以用我们的 next_permutation 来进行计算，然而，1 因为这一题的数据范围较大，所以我们需要用到**剪枝**，我们可以发现，假设我们由 n 个元素，那么我们第 i 个元素被添加的次数就是我们的组合数 $C_{n}^i$,我们于是就可以根据这个等式对我们的排序做初步的排除，**如果按照我们的加和加过不为 sum，那么我们就直接跳过**


```cpp
#include <cstdio>
using namespace std;

int n,sum;
//以下所有数组的大小都比所需值稍大，是为了防止越界
int visited[25]={0}; //防止重复选数，这是 dfs 枚举排列的要点
int ans[25]; //放置答案
int pc[25];//构造所有i C n-1

int dfs(int i,int num,int v); //写函数原型是（我的）好习惯！

int main(void){
    scanf("%d%d",&n,&sum);
    //下面构造杨辉三角(即组合数表)
    pc[0]=pc[n-1]=1; //杨辉三角性质,两边都是1
    if (n>1)
        for (int i=1;i*2<n;i++)
            pc[i]=pc[n-1-i]=(n-i)*pc[i-1]/i; //利用杨辉三角对称性和组合数公式计算
    //下面枚举计算
    if (dfs(0,0,0)) //0 仅起占位符作用
        for (int i=1;i<=n;i++)
            printf("%d ",ans[i]); //输出答案
    return 0;
}

int dfs(int i,int num,int v){
//参数说明：i 表示已经枚举了前 i 个数(数的序号从 1 开始),num 表示第 i 个数是 num，v 表示前 i 个数的“和”为 v
//返回值说明:返回 0 表示不行(不可能)，返回 1 表示找到了可行解。利用返回值就可以在找到第一个解后直接返回了
    if (v>sum) //“剪枝”，及时排除不可能情况，加速枚举
        return 0; //不可能
    if (i==n){ //已经枚举了前 n 个（全部）,判断一下是否是可行解
        if (v==sum){
            ans[i]=num; //放置解
            return 1;
        }
        else
            return 0;
    }
    visited[num]=1; //标记一下“第 i 个数的值已经使用过了”
    //下面寻找第 i+1 个数
    for (int j=1;j<=n;j++){
        if (!visited[j] && dfs(i+1,j,v+pc[i]*j)){ //v+pc[i]*j表示前(i+1)个数的“和”
            //注意，如果数的序号从 1 开始，那么第 i 个数的系数实际上是 (i-1) C (n-1)
            //执行到这里表示已经找到了可行的解
            ans[i]=num;
            return 1;
        }
    }
    visited[num]=0; //如果没有找到，一定记得复位，为进一步的寻找做准备
    return 0; //执行到这里一定是没有找到解
}
```