# 题目
 有几个古希腊书籍中包含了对传说中的亚特兰蒂斯岛的描述。其中一些甚至包括岛屿部分地图。但不幸的是，这些地图描述了亚特兰蒂斯的不同区域。您的朋友 Bill 必须知道地图的总面积。你自告奋勇写了一个计算这个总面积的程序。

## 输入格式
输入包含多组测试用例。

对于每组测试用例，第一行包含整数 n，表示总的地图数量。

接下来 n 行，描绘了每张地图，每行包含四个数字 x 1, y 1, x 2, y 2(不一定是整数），(x 1, y 1)和 (x 2, y 2)分别是地图的左上角位置和右下角位置。

注意，坐标轴 x轴从上向下延伸，y轴从左向右延伸。

当输入用例 n=0时，表示输入终止，该用例无需处理。

## 输出格式
每组测试用例输出两行。

第一行输出 Test case # k ，其中 k 是测试用例的编号，从 1开始。

第二行输出 Total explored area: a，其中 a是总地图面积（即此测试用例中所有矩形的面积并，注意如果一片区域被多个地图包含，则在计算总面积时只计算一次），精确到小数点后两位数。

在每个测试用例后输出一个空行。

## 数据范围
$1≤n≤10000$

$0≤x 1<x 2≤100000$

$0≤y 1<y 2≤100000$



## 输入样例 ：
2
10 10 20 20
15 15 25 25.5
0
## 输出样例 ：
Test case #1
Total explored area: 180.00 


# 思路
这是一道理论上属于计算几何的问题，即算出总的区域面积，但是我们这里采用线段树的写法，是因为他给出的区域都是矩形，是相对规则的一些区域。而我们的也因此给出扫描线算法，即将区间按照 x 的位置去划分，划分出来最后的面积就是每一个区间的区间长度，再加上这一个区间里我们有的高度的和。

因此，求出每一个区间里的高度的和就是关键。我们用线段树来储存 y 上的每一个值，扫描到就意味着我们要对应修改区间上的值都加上 1。扫描到末边时，我们就把对应位置上的值都减一。

求高度 h，就等价于求这个区间内不为 0 的区间的总长度。



# AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define p1 (p<<1)
#define p2 (p<<1|1)

const int N=10005;

struct T {
    int l,r,mini,add;
    double len; //区间长度
    double minlen; //区间最小值的区间长度
} t[N*8];
struct A {
    double x,y1,y2;
    int add;
} a[N*2];
int n,len;
double lsh[N*2];

bool cmp(A u,A v) {return u.x<v.x;}
int val(double x) {return lower_bound(lsh+1,lsh+1+len,x)-lsh;}
double raw(int x) {return lsh[x];}

void pushUp(int p) {
    t[p].mini=min(t[p1].mini,t[p2].mini);
    double minlen=0;
    if(t[p].mini==t[p1].mini) minlen+=t[p1].minlen;
    if(t[p].mini==t[p2].mini) minlen+=t[p2].minlen;
    t[p].minlen=minlen;
}

void build(int p,int l,int r) {
    double len=raw(r+1)-raw(l);
    t[p]={l,r,0,0,len,len};
    if(l==r) return;
    int mid=l+r>>1;
    build(p1,l,mid),build(p2,mid+1,r);
}

void pushDown(int p) {
    t[p1].add+=t[p].add,t[p2].add+=t[p].add;
    t[p1].mini+=t[p].add,t[p2].mini+=t[p].add;
    t[p].add=0;
}

void upd(int p,int l,int r,int add) {
    if(t[p].l>=l && t[p].r<=r) {t[p].mini+=add,t[p].add+=add; return;}
    if(t[p].add!=0) pushDown(p);
    int mid=t[p].l+t[p].r>>1;
    if(l<=mid) upd(p1,l,r,add);
    if(r>mid) upd(p2,l,r,add);
    pushUp(p);
}

int main()
{
    for(int tim=1;;tim++) {
        scanf("%d",&n);
        if(!n) break;
        printf("Test case #%d\n",tim);
        for(int i=1;i<=n;i++) {
            double x1,y1,x2,y2;
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            a[i]={x1,y1,y2,1},a[i+n]={x2,y1,y2,-1};//a储存每一个输入
            lsh[i]=y1,lsh[i+n]=y2;//lsh存储每一个y轴上的坐标
        }
        n*=2;
        sort(a+1,a+1+n,cmp),sort(lsh+1,lsh+1+n);
        len=unique(lsh+1,lsh+1+n)-lsh-1;
        build(1,1,len-1);
        double ans=0;
        upd(1,val(a[1].y1),val(a[1].y2)-1,a[1].add);
        for(int i=2;i<=n;i++) {
            double len=t[1].len;
            if(!t[1].mini) len-=t[1].minlen;
            ans+=len*(a[i].x-a[i-1].x);//面积等于区间长乘以高
            upd(1,val(a[i].y1),val(a[i].y2)-1,a[i].add);
        }
        printf("Total explored area: %.2lf\n\n",ans);
    }
    return 0;
}
//不构建down的操作
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100010;

struct segment// 用来存线段信息
{
    double x, y1,y2;
    int d; // 区分它是该矩阵前面的线段还是后面的线段
    bool operator < (const segment&t)const
    {
        return x < t.x;
     } 
}seg[N * 2];//每个矩阵需要存两个线段

// 线段树的每个节点 保存的为线段,0号点为y[0]到y[1]，以此类推
struct node
{
    int l,r;
    int cnt;// 记录这段区间出现了几次
    double len;// 记录这段区间的长度;即线段长度
}tr[N * 8];//由于线段二倍，所以8倍空间
vector<double>ys;//用于离散化
int n;

int find(double y)
{
    // 需要返回vector 中第一个 >= y 的数的下标
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}

void pushup(int u)
{
    //例如：假设tr[1].l = 0,tr[1].r = 1;
    //      y[0]为ys[0]到ys[1]的距离, y[1]为ys[1]到ys[2]的距离
    //      tr[1].len 等于y[0]到y[1]的距离
    //      y[1] = ys[tr[1].r + 1] = ys[2], y[0] = ys[tr[1].l] = ys[0]
    if(tr[u].cnt)tr[u].len = ys[tr[u].r + 1] - ys[tr[u].l];//表示整个区间都被覆盖，该段长度就为右端点 + 1后在ys中的值 - 左端点在ys中的值
    // 借鉴而来
    // 如果tr[u].cnt等于0其实有两种情况:
    // 1. 完全覆盖. 这种情况由modify的第一个if进入. 
    //    这时下面其实等价于把"由完整的l, r段贡献给len的部分清除掉", 
    //    而留下其他可能存在的子区间段对len的贡献
    // 2. 不完全覆盖, 这种情况由modify的else最后一行进入. 
    //    表示区间并不是完全被覆盖，可能有部分被覆盖,所以要通过儿子的信息来更新
    else if(tr[u].l != tr[u].r)
    {
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    }
    else tr[u].len = 0;//表示为叶子节点且该线段没被覆盖，为无用线段，长度变为0
}

void modify(int u,int l,int r,int d)//表示从线段树中l点到r点的出现次数 + d
{
    if(tr[u].l >= l && tr[u].r <= r)//该区间被完全覆盖
    {
        tr[u].cnt += d;//该区间出现次数 + d
        pushup(u);//更新该节点的len
    }
    else
    {
        int mid = tr[u].r + tr[u].l >> 1;
        if (l <= mid)modify(u << 1,l,r,d);//左边存在点
        if (r > mid)modify(u << 1 | 1,l,r,d);//右边存在点
        pushup(u);//进行更新
    }
}

void build(int u,int l,int r)
{
    tr[u] = {l,r,0,0};

    if (l != r)
    {
        int mid = l + r >> 1;
        build(u << 1,l,mid),build(u << 1 | 1,mid + 1,r);
        //后面都为0，不需更新len
    }
}

int main()
{
    int T = 1;
    while (cin>>n,n)//多组输入
    {
        ys.clear();//清空
        int j = 0;//一共j个线段
        for (int i = 0 ; i < n ; i ++)//处理输入
        {
            double x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            seg[j ++] = {x1,y1,y2,1};//前面的线段
            seg[j ++] = {x2,y1,y2,-1};//后面的线段
            ys.push_back(y1),ys.push_back(y2);//y轴出现过那些点
        }
        sort(seg,seg + j);//线段按x排序

        sort(ys.begin(),ys.end());//先排序
        ys.erase(unique(ys.begin(),ys.end()),ys.end());//离散化去重

        //例子：假设现在有三个不同的y轴点,分为两个线段
        //y[0] ~ y[1],y[1] ~ y[2];
        //此时ys.size()为3,ys.size() - 2 为 1;
        //此时为 build(1, 0, 1);
        //有两个点0 和 1,线段树中0号点为y[0] ~ y[1],1号点为y[1] ~ y[2];
        build(1,0,ys.size() - 2);

        double res = 0;

        for (int i = 0 ; i < j ; i ++)
        {
            //根节点的长度即为此时有效线段长度 ，再 * x轴长度即为面积
            if (i)res += tr[1].len * (seg[i].x - seg[i - 1].x);
            //处理一下该线段的信息，是加上该线段还是消去
            //例子：假设进行modify(1，find(10),find(15) - 1,1);
            //      假设find(10) = 0,find(15) = 1;
            //      此时为modify(1, 0, 0, 1);
            //      表示线段树中0号点出现次数加1；
            //      而线段树中0号点刚好为线段(10 ~ 15);
            //      这就是为什么要进行find(seg[i].y2) - 1 的这个-1操作
            modify(1,find(seg[i].y1), find(seg[i].y2) - 1,seg[i].d);
        }

        printf("Test case #%d\n", T ++ );
        printf("Total explored area: %.2lf\n\n", res);
    }
    return 0;
} 

作者：清溪落月诗如洗
链接：https://www.acwing.com/solution/content/49051/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

```
# 备注
