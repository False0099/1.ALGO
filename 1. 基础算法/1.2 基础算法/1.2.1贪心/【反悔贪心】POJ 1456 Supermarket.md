## 题目描述
小新特别喜欢动态规划

背包DP、树上DP、状态压缩DP、概率DP、计数DP等等，小新表示：爷很强，放马过来！

现有n道动态规划的题目，第i道题必须在第d天之前写完，否则这道题便会无法提交了！

每通过一道题，小新便能获得p点开心值。

但由于小新忙着学《现代电视原理》，忙着学《数字信号处理》，忙着学《计算机网络》，忙着学《通信原理》，忙着学《数据库》，忙着学......，他每天最多只能写其中的某一道题。 聪明的你肯定知道，综合考虑题目是否过期，以及每道题目的价值，小新应刷那些题才能获得最大的开心值。

## 输入格式

会有多组数据

每组数据第一行为n, 即题目的数量

之后n行数字，第i行为 p, d，表示第i题目能提供的开心值以及日期

n , p, d <= 10000

## 输出格式

对于每一组数据, 输出当前条件下小新能获得的最大开心值

## 样例 #1

### 样例输入 #1

```
4

50 2

10 1

20 2

30 1

7

20 1

2 1

10 3

100 2

8 2

5 20

50 10
```

### 样例输出 #1

```
80

185
```

## 题解
我们这一道题目可以采用反悔贪心的想法，先用一个堆来存储我们的决策结果，然后按照 ddl 为第一关键字，价值为第二关键字，如果某一个点的价值比我们的决策堆中的最小结果还要好，并且堆大小超出了时间，那么我们就可以直接把决策堆里的那个东西给丢了，换上我们新的点。

## 代码
```cpp
#include <cstdio>
#include <string.h>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
 
const int maxn=1e4+5;
typedef struct{
   int profit;
   int deadline;
}product;
 
bool operator < (product a,product b){
  return a.deadline<b.deadline;
}
 
product goods[maxn];
 
int heap[maxn]; //小根堆
int cnt=1;
 
void up(int p){//向上调整
  while(p>1){
     if(heap[p]<heap[p/2]){
        swap(heap[p],heap[p/2]);
        p/=2;
     }
     else break;
  }
}
 
void down(int p){ //向下调整
   int s=p*2;
   while(s<cnt){
      if(s<cnt-1&&heap[s]>heap[s+1]) s++;
      if(heap[s]<heap[p]){
          swap(heap[s],heap[p]);
          p=s;
          s=p*2;
      }
      else break;
   }
}
 
void Insert(int value){
    heap[cnt]=value;
    up(cnt);
    cnt++;
}
 
void Extract(){
    heap[1]=heap[--cnt];
    down(1);
}
 
void Remove(int k){
    heap[k]=heap[--cnt];
    up(k); down(k);
}
 
 
void init(){
  memset(heap,0,sizeof(heap));
  cnt=1;
}
 
int main()
{
  int N;
  while(~scanf("%d",&N)){
     init();
     for(int i=1;i<=N;i++)
       scanf("%d %d",&goods[i].profit,&goods[i].deadline);
     sort(goods+1,goods+N+1);
     int num=0;
     for(int i=1;i<=N;i++){
         if(goods[i].deadline>num){
             Insert(goods[i].profit);
             num++;
         }
         else{
             if(goods[i].profit>heap[1]){
                 Extract();
                 Insert(goods[i].profit);
             }
         }
     }
     int ans=0;
     for(int i=1;i<=num;i++)
         ans+=heap[i];
     printf("%d\n",ans);
  }
	return 0;
}
```