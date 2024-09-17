时间来到20210年，科学家终于发明出了与二进制星人沟通的方式。二进制星人只能理解完全由1和0组成的数字，聪明的科学家发现，如果想表示数字 n，只要用数字1和数字0写出一个为 n 的倍数的数字，把它拿给二进制星人看，他们就能理解了。如想表示6这个数字，只要拿着“100100100100100100”（6的16683350016683350倍）给二进制星人看，他就会明白这是6的意思了。给出 n，请你模拟这一过程。  
提示：本题采用Special Judge，你无需输出所有符合条件的m，你只需要输出任一符合条件的m即可。

Input

输入包含多组数据，每组数据仅一行，只包含一个正整数n，n=0时输入结束 (1 <= n <= 200).

Output

对于输入的每组n，都输出任一符合条件的m，m为只由1和0构成的十进制数，且m是n的倍数。即使有多个符合条件的m，你也只需要输出一个即可。

Sample Input

2
6
19
0

Sample Output

10
100100100100100100
111111111111111111

Hint

本题来自 POJ，无法使用 c++11的特性。

## 题解
我们这一题可以采用**类似于数位dp构造**的方式，因为我们的答案保证了一定在 unsigned ll 范围内，所以我们可以直到，我们的数字的最大长度一定是 20，所以当我们的长度大于 20 时，我们直接退出即可。另外，如果我们在构造过程中，已经出现了余数为 0 的情况，那么我们后面直接补零即可，这也是我们的一个剪枝策略

```cpp
#include<cstdio>
#include<queue>
#include<string.h>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=500;
int found;
void dfs(int n,unsigned __int64 p,int k)
{
    if(k==19)
        return ;
        if(found==1)
        return ;
    if(p%n==0)
    {
        found=1;
        printf("%I64u\n",p);
        return ;
    }
 
  dfs(n,p*10,k+1);//下一个为0
  dfs(n,p*10+1,k+1);//下一个为1
}
 
int main()
{
    int n;
    while(scanf("%d",&n)==1&&n!=0)
    {
       found=0;
        dfs(n,1,0);
    }
    return 0;
}该题考虑的是二叉树的解法，并设置树的深度k避免过大的数无法读取。
```