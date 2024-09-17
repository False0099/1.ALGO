一条道路上有N 个点，每个点有高度hi​。  
举世闻名的马里奥来挑战这条道路。  
现在，你需要回答M个询问，每个询问如下：  
假设马里奥最多跳H这么高，在区间$[l,r]$中，马里奥能跳过多少个点。（不考虑他被挡住）

即询问区间$[l,r]$内有多少个数**不大于**H。

Input

第一行一个整数T，表示共T组数据。  
对于每组数据：  
第一行包含两个整数N,M(1≤N≤105,1≤M≤105), N表示道路的程度, M是询问的个数。  
第二行包含N个整数，表示每个障碍物的高度hi​(0≤hi​≤109)。  
接下来M行，每行33个整数L,R,H(0≤L≤R<N,0≤H≤109)。

Output

对于每组数据, 先输出"**Case X:**" （X表示组数）  
然后有M行每行包含一个整数。  
第i个整数表示第i个询问的答案。

Sample Input/Output

|Inputcopy|Outputcopy|
|---|---|
|1<br>10 10<br>0 5 2 7 5 4 3 8 7 7 <br>2 8 6<br>3 5 0<br>1 3 1<br>1 9 4<br>0 1 0<br>3 5 5<br>5 5 1<br>4 6 3<br>1 5 7<br>5 7 3|Case 1:<br>4<br>0<br>0<br>3<br>1<br>2<br>0<br>1<br>5<br>1|

## 题解
我们这一题，首先，我们可以采用我们的离线+树状数组的方式，先把我们的每一个询问按照右端点 r 来排序，然后以我们的权值构建我们的权值线段树，这样，我们 l，r 中不大于 H 的数就是 $quert(h)$,我们每一次添加也就是 $add(h,1)$ 而已。

但这一题我们同样存在**在线做法**主席树的算法，我们的**主席树直接维护我们的答案**，我们每一次查找相当于找我们前缀和中少于 l 的数目。**我们把我们的 h 离散化后，就等价于我们求区间第 K 大**

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int maxn=1e5+100;
vector<int> v;
int n,m,a[maxn],rt[maxn],tot;
struct node
{
    int l,r,sum;//l代表左儿子，r代表右儿子
}T[maxn*20];
int getid(int x)
{
    return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
void build(int &o,int l,int r)
{
    o=++tot;
    T[o].sum=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(T[o].l,l,mid);
    build(T[o].r,mid+1,r);
}
void update(int l,int r,int &now,int last,int k)
{
    T[++tot]=T[last];//先把左右赋值
    now=tot;
    T[now].sum++;//?
    if(l==r) return;
    int mid=(l+r)>>1;
    if(k<=mid) update(l,mid,T[now].l,T[last].l,k);//哪边不对更新哪一边
    else update(mid+1,r,T[now].r,T[last].r,k);
}
int query(int l,int r,int x,int y,int k)
{
    if(l==r) return T[y].sum-T[x].sum;
    int mid=(l+r)>>1;
    if(k<=mid) return query(l,mid,T[x].l,T[y].l,k);
    else
    {
        int ret=0;
        ret+=T[T[y].l].sum-T[T[x].l].sum;
        ret+=query(mid+1,r,T[x].r,T[y].r,k);
        return ret;
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int kase=1;kase<=t;kase++)
    {
        v.clear();
        tot=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),v.push_back(a[i]);
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        build(rt[0],1,n);
        for(int i=1;i<=n;i++)
            update(1,n,rt[i],rt[i-1],getid(a[i]));
        printf("Case %d:\n",kase);
        for(int i=1;i<=m;i++)
        {
            int l,r,h;
            scanf("%d%d%d",&l,&r,&h);
            l++,r++;
            int k=upper_bound(v.begin(),v.end(),h)-v.begin();//v中有k个元素小于等于h
            //upper的返回值是指向键值<=key的最后一个元素的后一个元素。 
            if(!k) printf("0\n");
            else
                printf("%d\n",query(1,n,rt[l-1],rt[r],k));
        }
    }
    return 0;
}

```