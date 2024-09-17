# [ICPC 2016 WF] Swap Space

## 题面翻译

你有 $n$ 个硬盘 $(n\leqslant10^{6})$ ，现在需要对所有硬盘进行格式化。格式化后，第 $i$ 个硬盘的容量会由原来的 $a_{i}$ 变为 $b_{i}$。由于容量的改变，你需要购买硬盘容量来实现数据转移。数据可以分段转移，如把大小为 $(a+b)\ G$ 的数据分别存放在两个硬盘中，一个存 $a\ G$ 一个存 $b\ G$ 。一个硬盘被格式化后可以直接使用。求购买额外容量的最小值。

## 题目描述

You administer a large cluster of computers with hard drives that use various file system types to store data. You recently decided to unify the file systems to the same type. That is quite a challenge since all the drives are currently in use, all of them are filled with important data to the limits of their capacities, and you cannot afford to lose any of the data. Moreover, reformatting a drive to use a new file system may significantly change the drive’s capacity. To make the reformat possible, you will have to buy an extra hard drive. Obviously, you want to save money by minimizing the size of such extra storage.

You can reformat the drives in any order. Prior to reformatting a drive, you must move all data from that drive to one or more other drives, splitting the data if necessary. After a drive is reformatted, you can immediately start using it to store data from other drives. It is not necessary to put all the data on the same drives they originally started on – in fact, this might even be impossible if some of the drives have smaller capacity with the new file system. It is also allowed for some data to end up on the extra drive.

As an example, suppose you have four drives $A$, $B$, $C$, and $D$ with drive capacities $6$, $1$, $3$, and $3$ GB. Under the new file system, the capacities become $6$, $7$, $5$, and $5$ GB, respectively. If you buy only $1$ GB of extra space, you can move the data from drive $B$ there and then reformat drive $B$. Now you have $7$ GB free on drive $B$, so you can move the $6$ GB from drive $A$ there and reformat drive $A$. Finally, you move the six total gigabytes from drives $C$ and $D$ to drive $A$, and reformat $C$ and $D$.

## 输入格式

The input begins with a line containing one integer $n$ ($1 \le n \le 10^6$), which is the number of drives in your cluster. Following this are $n$ lines, each describing a drive as two integers $a$ and $b$, where $a$ is the capacity with the old file system and $b$ is the capacity with the new file system.

All capacities are given in gigabytes and satisfy $1 \le a,b \le 10^9$. (One thousand petabytes should be enough for everyone, right?)

## 输出格式

Display the total extra capacity in gigabytes you must buy to reformat the drives.

## 样例 #1

### 样例输入 #1

```
4
6 6
1 7
3 5
3 5
```

### 样例输出 #1

```
1
```

## 样例 #2

### 样例输入 #2

```
4
2 2
3 3
5 1
5 10
```

### 样例输出 #2

```
5
```

## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016

## 题解
我们本题的思路是：首先，我们将我们的原本的哪些硬盘分为两类，一类是我们换硬盘后容量会变大的，另一类是我们换了之后容量不变或者会缩小的。

对于我们的第一类，我们肯定要首先满足，因为我们这么安排的话，我们一是不需要用我们的额外空间去扩容，二是我们可以把多余的空间用于暂时存储，于是我们就把我们的第一类按照我们的其实容量来进行排序，然后从小到大选择我们的对应的元素是什么。

对于我们的第二类，我们希望格式化后的剩余容量尽可能的大，这样我们需要转移的元素就会少一些。

于是我们就一边存储一边更改即可。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace Std
{
    template<typename tp>
    void read(tp &x)
    {
        x=0;
        tp nev=1;
        char c=getchar();
        while(c<'0'||c>'9'){if(c=='-'){nev=-1;}c=getchar();}
        while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    }
    int n,cnt1=0,cnt2=0;
    ll ans=0,now=0;
    struct node
    {
        ll st,ed;
        node(){}
        node(ll _st,ll _ed){st=_st,ed=_ed;}
    }k1[1000001],k2[1000001];
    bool cmp1(node x,node y)
    {
        return x.st<y.st;
    }
    bool cmp2(node x,node y)
    {
        return x.ed>y.ed;
    }
    int main(void)
    {
        read(n);
        ll st,ed;
        for(int i=1;i<=n;++i)
        {
            read(st),read(ed);
            if(st<ed) k1[++cnt1]=node(st,ed);
            else k2[++cnt2]=node(st,ed);
        }
        sort(k1+1,k1+1+cnt1,cmp1);
        sort(k2+1,k2+1+cnt2,cmp2);
        for(int i=1;i<=cnt1;++i)
        {
            if(k1[i].st>now)
            {
                ans+=k1[i].st-now;
                now=k1[i].ed;
            }
            else
            {
                now+=k1[i].ed-k1[i].st;
            }
        }
        for(int i=1;i<=cnt2;++i)
        {
            if(k2[i].st>now)
            {
                ans+=k2[i].st-now;
                now=k2[i].ed;
            }
            else
            {
                now+=k2[i].ed-k2[i].st;
            }
        }
        printf("%lld\n",ans);
        return 0;
    }
}
int main()
{
    return Std::main();
}

```