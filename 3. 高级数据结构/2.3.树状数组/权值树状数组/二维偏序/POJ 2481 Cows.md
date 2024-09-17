## 题目描述
农夫约翰的牛发现，他的田地里沿着山脊生长的三叶草（我们可以将其视为一维数字线）特别好。

农夫约翰有N头母牛（我们将母牛的编号从1到N）。每位农夫约翰的N头母牛都有她特别喜欢的三叶草范围（这些范围可能重叠）。范围由闭合间隔[S，E]定义。

但是有些母牛很强壮，有些却很弱。给定两个母牛：母牛i和母牛j，它们最喜欢的三叶草范围是[Si，Ei]和[Sj，Ej]。如果Si <= Sj并且Ej <= Ei并且Ei-Si> Ej-Sj，我们说母牛i比母牛j强。

对于每头母牛，有几头母牛比她强？农夫约翰需要您的帮助！

## 输入格式

输入包含多个测试用例。

对于每个测试用例，第一行是整数N（1 <= N <= 10 ^ 5），它是母牛的数量。然后是N行，其第i行包含两个整数：S和E（0 <= S<=E<=1e5 )

## 输出格式

对于每个测试用例，输出一行包含n个以空格分隔的整数，其中第i个数字指定比母牛i强的母牛的数量。

## 样例 #1

### 样例输入 #1

```
3

1 2

0 3

3 4

0
```

### 样例输出 #1

```
1 0 0
```

## 提示

Huge input and output,scanf and printf is recommended.


## 题解
二位偏序问题是对于我们逆序对问题的扩展，我们的逆序对要求的是满足 $(i\leq j),a[i]\geq a[j]$ 的个数，而我们的二维偏序问题，则是求 $(b[i]\leq b[j],a[i]\geq a[j])$ 的个数。我们这个时候就需要我们用到我们的**树状数组**来解决。

我们可以对区间按照 s 从小到大排序，s 相等则按照 e 从大到小排序。这样，我们就构造出了类似于我们的逆序对的条件。这样可以使得后面的区间的起点一定大于前面的，因此我们就不用考虑 s 了，只需要考虑 e 就行了。

之后我们维护一个树状数组记录一段区间内小于当前 e 的区间个数，然后我们求出已经插入所有的区间个数，减去小于的，剩下的就是大于等于当前 e 的区间个数。
![[无标题 9.png]]
## 代码
```cpp
#include <iostream>
#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+10;
struct Cow{
    int l,r;
    int id;
}cow[N];
//左端点从小到大排序，右端点从大到小排序，这样也可以保证先枚举外层区间
bool cmp(Cow c1,Cow c2){
    if(c1.l==c2.l)return c1.r>c2.r;
    return c1.l<c2.l; 
}
int n;
int bit[N];
int cnt[N];
int Lowbit(int i){
    return i&(-i);
}
//求和函数，向下lowbit
int sum(int i){
    int sum=0;
    while(i>0){
        sum+=bit[i];
        i-=Lowbit(i);
    }
    return sum;
}
//加操作，向上lowbit
void add(int i,int x){
    while(i<N){
        bit[i]+=x;
        i+=Lowbit(i);
    }
}
int main()
{
    while(~scanf("%d",&n),n){
        memset(bit,0,sizeof(bit));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&cow[i].l,&cow[i].r);
            cow[i].l++;
			cow[i].r++;
            cow[i].id=i;
        }
        sort(cow+1,cow+n+1,cmp);
        for(int i=n;i>=0;i--){
            if(i>1&&cow[i].l==cow[i-1].l&&cow[i].r==cow[i-1].r)
                cnt[cow[i].id]=cnt[cow[i-1].id];
            else
                cnt[cow[i].id]=sum(N-1)-sum(cow[i].r-1);//求比他大的所有值
            add(cow[i].r,1);
        }
        printf("%d",cnt[1]);
        for(int i=2;i<=n;i++)
          printf(" %d",cnt[i]);
        printf("\n");
    }
    return 0;
}


```