一组研究人员正在设计一项实验，以测试猴子的智商。他们将香蕉挂在建筑物的屋顶，同时，提供一些砖块给这些猴子。如果猴子足够聪明，它应当能够通过合理的放置一些砖块建立一个塔，并爬上去吃他们最喜欢的香蕉。

研究人员有n种类型的砖块，每种类型的砖块都有无限个。第i块砖块的长宽高分别用xi，yi，zi来表示。 同时，由于砖块是可以旋转的，每个砖块的3条边可以组成6种不同的长宽高。

在构建塔时，当且仅当A砖块的长和宽都分别小于B砖块的长和宽时，A砖块才能放到B砖块的上面，因为必须留有一些空间让猴子来踩。

你的任务是编写一个程序，计算猴子们最高可以堆出的砖块们的高度。

Input

输入文件包含多组测试数据。

每个测试用例的第一行包含一个整数n，代表不同种类的砖块数目。n<=30.

接下来n行，每行3个数，分别表示砖块的长宽高。

当n= 0的时候，无需输出任何答案，测试结束。

Output

对于每组测试数据，输出最大高度。格式：Case 第几组数据: maximum height = 最大高度

Sample Input

1

10 20 30  
2  
6 8 10  
5 5 5  
7  
1 1 1  
2 2 2  
3 3 3  
4 4 4  
5 5 5  
6 6 6  
7 7 7  
5  
31 41 59  
26 53 58  
97 93 23  
84 62 64  
33 83 27  
0 

Sample Output

Case 1: maximum height = 40

Case 2: maximum height = 21  
Case 3: maximum height = 28  
Case 4: maximum height = 342

## 题解
我们本题采用类似于我们 LIS 的方法，我们可以先把我没得每一个砖头按照长宽高全排列出六种方块，然后再把所有的方块按长为第一关键字，宽为第二关键字，从大到小排序，然后我们再进行 dp，转移即可。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T=0,n,x,y,z,mx,f[10005];
struct book{int a,b,h;}k[10005];
int Max(int t1,int t2){return t1>t2?t1:t2;}
bool cmp(book t1,book t2){return t1.a==t2.a?t1.b>t2.b:t1.a>t2.a;}
int main(){
    scanf("%d",&n);
    while(n!=0){
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&x,&y,&z);mx=0;
            k[i+n*0].a=x;k[i+n*0].b=y;k[i+n*0].h=z;
            k[i+n*1].a=x;k[i+n*1].b=z;k[i+n*1].h=y;
            k[i+n*2].a=y;k[i+n*2].b=x;k[i+n*2].h=z;
            k[i+n*3].a=y;k[i+n*3].b=z;k[i+n*3].h=x;
            k[i+n*4].a=z;k[i+n*4].b=x;k[i+n*4].h=y;
            k[i+n*5].a=z;k[i+n*5].b=y;k[i+n*5].h=x;
        }
        sort(k+1,k+n*6+1,cmp);T++;
        for(int i=1;i<=6*n;i++){
            f[i]=k[i].h;
            for(int j=1;j<i;j++){
                if(k[j].a>k[i].a&&k[j].b>k[i].b&&f[j]+k[i].h>f[i])f[i]=f[j]+k[i].h;
            }
            mx=Max(f[i],mx);
        }
        printf("Case %d: maximum height = %d\n",T,mx);
        scanf("%d",&n);
    }
}

```
