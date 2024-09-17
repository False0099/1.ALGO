# 
## 题目描述
格鲁吉亚和鲍勃决定一起玩一个自创的游戏。

他们在纸上绘制一排网格，将网格从左到右依次编号 1,2,3......，并将 N 个西洋棋棋子放在不同的网格上，如下图所示：

![1704_1.jpg](https://www.acwing.com/media/article/image/2019/01/19/19_01841f9e1b-1704_1.jpg)

格鲁吉亚和鲍勃依次移动西洋棋棋子。

每次玩家选择一个棋子，并将其向左移动，但是不能越过任何其他西洋棋棋子或超过左边界。

玩家可以自由选择棋子移动的步数，其限制是棋子必须至少移动一步，一个网格最多可以包含一个棋子。

无法移动任何棋子的玩家将输掉游戏。

假设格鲁吉亚和鲍勃在游戏中都能够采取最好的策略，每次都由格鲁吉亚先手。

在给定你 N 个棋子的具体位置的情况下，请你预测出谁将获得胜利。


## 题解
我们这一题把题目中看成一对一对的，那么一对之中的距离就可以忽略不计，那么我们只需要关注，每两对棋子之间的距离，然后我们只需要把每两对之间看成一个 nim 游戏就完成了

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int t,n,fl,p[maxn];
void freo(){
    freopen("GB.in" ,"r",stdin );
    freopen("GB.out","w",stdout);
}
void prep(){
    scanf("%d",&t);
}
void init(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&p[i]);
}
void work(){
    fl=0;
    if(n&1) p[++n]=0;
    sort(p+1,p+n+1);
    for(int i=2;i<=n;i+=2)
        fl^=p[i]-p[i-1]-1;
}
void prin(){
    if(0)       printf("Not sure\n");//这是不可能的，所以来搞笑一波 
    else if(fl) printf("Georgia will win\n");
    else        printf("Bob will win\n");
}
int main(){
    freo();
    prep();
    while(t--){
        init();
        work();
        prin();
    }
    return 0;
}
```