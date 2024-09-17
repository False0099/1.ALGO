CCY 有很多冠军奖杯，包括2019高校大数据挑战赛冠军等等等，CCY 把所有奖杯整齐的放在柜子里，这个柜子可以看成一个 n×m 的矩形。  
但是现在CCY不得不出门去约会，但是他知道小偷会来他的家里面偷他奖杯，所有CCY能也准备了一些保护装置来保护奖杯不被小偷偷走  
CCY准备的每个装置只能保护一个矩形范围内的奖杯。CCY总共安装了 p 个装置，每个装置保护的矩形大小和位置是已知的。  
CCY接下来会有 q 个的小偷来偷奖杯，他也猜到了每个小偷想偷奖杯的矩形范围。CCY想知道他的装置是否能保护奖杯不被偷走。

## Input

有多个测试案例。  
每个案例的开头一行包含两个整数 n,m(1≤n,1≤m,n×m≤10^7)，代表柜子的面积，第二行包含一个整数 p(1≤p≤10^6)，代表CCY安装保护装置的数量。  
之后是 p 行，每行描述一个矩形。每一行都包含四个整数 x1,y1,x2,y2(1≤x1≤x2≤n,1≤y1≤y2≤m)，表示保护装置能够保护矩形的左下角和右上角。  
下一行包含一个整数 q(1≤q≤10^6)，代表有q个小偷，接下来是 q 行，每行描述一个矩形。每一行都包含四个整数 x1,y1,x2y2(1≤x1≤x2≤n,1≤y1≤y2≤m)，表示小偷要偷取矩形的左下角和右上角。

## Output

对于每一种情况，你应该打印 q 行。 每行包含 YES 或 NO，表示这次能否成功保护奖杯不被偷走。

## Sample Input

6 6
3
2 2 4 4
3 3 5 6
5 1 6 2
2
3 2 5 4
1 5 6 5

## Sample Output

YES
NO

## 题解
我们可以先利用差分，给每个装了监控的区域做一个标记，然后计算前缀和，如果某个点能被监控到，就在上面放上 1 这个数，如果区域能被完全覆盖，那么我们该区域的面积应该要等于这一段区域的前缀和。

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e7 + 10;

int n, m, p, q;
int a[N];         //存图，考虑到二维空间肯定是不够，所以需要压缩成一维

int addr(int x, int y){     //(x,y) -> 一个int型的地址
    if(x == 0 || y == 0 || x > n || y > m)      return 0;       //****处理一下边界****
    
    return (x - 1) * m + y;     //自己设置的映射函数
}

void insert(int x1, int y1, int x2, int y2){        //差分
    a[addr(x1, y1)] += 1;
    a[addr(x1, y2 + 1)] -= 1;
    a[addr(x2 + 1, y1)] -= 1;
    a[addr(x2 + 1, y2 + 1)] += 1;     
}

int main(){
    
    while(~scanf("%d%d", &n, &m)){
        int x1, y1, x2, y2;
        memset(a, 0, sizeof a);
        
        scanf("%d", &p);
        while(p --){
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            insert(x1, y1, x2, y2);
        }
        
        //先预处理一遍前缀和，被monito到重复的区域也考虑在内
        for(int i = 1;i <= n;i ++)
            for(int j = 1;j <= m;j ++)
                a[addr(i, j)] = a[addr(i - 1, j)] + a[addr(i, j - 1)] - a[addr(i - 1, j - 1)] + a[addr(i, j)];
        
        //去掉重复区域，将所有被覆盖(> 0)到的区域都置1    
        for(int i = 1;i <= n;i ++)
            for(int j = 1;j <= m;j ++)
                if(a[addr(i, j)] > 0)       a[addr(i, j)] = 1;
        
        //再处理前缀和
        for(int i = 1;i <= n;i ++)
            for(int j = 1;j <= m;j ++)
                a[addr(i, j)] = a[addr(i - 1, j)] + a[addr(i, j - 1)] - a[addr(i - 1, j - 1)] + a[addr(i, j)];
        
        
        scanf("%d", &q);
        while(q --){
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            //区域面积等于区域1的和则表明被全覆盖
            int s = a[addr(x2, y2)] - a[addr(x1 - 1, y2)] - a[addr(x2, y1 - 1)] + a[addr(x1 - 1, y1 - 1)];
            
            if(s == (x2 - x1 + 1) * (y2 - y1 + 1))      cout << "YES" << endl;
            else        cout << "NO" << endl;
        }
    }
    
    return 0;
}

```