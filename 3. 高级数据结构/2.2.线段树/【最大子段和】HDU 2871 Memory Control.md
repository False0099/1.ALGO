Memory units are numbered from 1 up to N.  
A sequence of memory units is called a memory block.  
The memory control system we consider now has four kinds of operations:  
1.  Reset Reset all memory units free.  
2.  New x Allocate a memory block consisted of x continuous free memory units with the least start number  
3.  Free x Release the memory block which includes unit x  
4.  Get x Return the start number of the xth memory block(Note that we count the memory blocks allocated from left to right)  
Where 1<=x<=N.You are request to find out the output for M operations.  

有1-N个连续内存单元格。有4种操作  
1.Reset,清空所有的内存  
2.New x,找到连续x个单元格形成一个内存块，输出最小的下标。  
3.Free x, 释放第x个单元格所在内存块的开始和截止位置。  
4.Get x,输出第x个内存块从哪个单元格开始的。  

Input

Input contains multiple cases.  
Each test case starts with two integer N,M(1<=N,M<=50000) ,indicating that there are N units of memory and M operations.  
Follow by M lines,each line contains one operation as describe above.  
多组输入数据  
第一行两个整数n和m (n,m<= 50000)  
接下里m个询问，如题目描述。

Output

For each “Reset” operation, output “Reset Now”.  
对于Reset操作，输出Reset Now。  
  
For each “New” operation, if it’s possible to allocate a memory block,  
  
output “New at A”,where Ais the least start number,otherwise output “Reject New”.  
对于New操作，如果可以申请到内存，输出New at A，A表示最小的满足条件的下标。 否则输出“Reject New”。  
  
For each “Free” operation, if it’s possible to find a memory block occupy unit x,  
output “Free from A to B”,where A and B refer to the start and end number of the memory block,otherwise output “Reject Free”.  
对于Free如果第x个单元格被使用了，输出Free from A to B，A和B表示使用x单元格的内存块的 其实和终止位置。如果没有被使用，输出Reject Free  
  
For each “Get” operation, if it’s possible to find the xth memory blocks,  
output “Get at A”,where A is its start number,otherwise output “Reject Get”.  
对于Get操作，输出第X个内存块，输出Get at A，找不到输出“Reject Get”  
Output one blank line after each test case.  
每组测试数据后面输出一个空行。  

Sample Input

6 10
New 2
New 5
New 2
New 2
Free 3
Get 1
Get 2
Get 3
Free 3
Reset

Sample Output

New at 1
Reject New
New at 3
New at 5 
Free from 3 to 4
Get at 1
Get at 5
Reject Get
Reject Free
Reset Now

## 题解
我们这一题要求我们维护一个区间上连续 0 的个数，并且要查询我们最早的满足连续 0 的个数为 x 的区域，我们这个时候就需要运用到我们的**线段树合并**，我们维护每一个端点的左端和我们的右端。

当我门找到一个内存的地址后，我们用一个 **vector 来保存申请的内存块的左右端点**，在**vector 中的大小就表示内存块的编号**，当申请一个内存块时，二分查找这个内存块在 vector 中的位置，然后插入。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define lson rt<<1
#define rson rt<<1|1
const int N = 500010;
struct node
{
    int l,r,c;
    int lsum,rsum,sum;
}s[N<<2];
struct block
{
    int l,r;
    bool operator < (const block &cmp) const{
        return l < cmp.l;
    }
};
void pushdown(int rt, int m)
{
    if(s[rt].c != -1){
        s[lson].lsum = s[lson].rsum = s[lson].sum = s[rt].c?0:m-(m>>1);
        s[rson].lsum = s[rson].rsum = s[rson].sum = s[rt].c?0:m>>1;
        s[lson].c = s[rson].c = s[rt].c;
        s[rt].c = -1;
    }
}
void pushup(int rt, int m)
{
    s[rt].lsum = s[lson].lsum;
    s[rt].rsum = s[rson].rsum;
    s[rt].sum = max(s[lson].sum, s[rson].sum);
    if(s[lson].lsum == m-(m>>1))
        s[rt].lsum += s[rson].lsum;
    if(s[rson].rsum == m>>1)
        s[rt].rsum += s[lson].rsum;
    s[rt].sum = max(s[rt].sum, s[lson].rsum + s[rson].lsum);
}
void build(int l, int r, int rt)
{
    s[rt].l = l;  s[rt].r = r;
    s[rt].lsum = s[rt].rsum = s[rt].sum = r-l+1;
    s[rt].c = -1;
    if(l == r) return;
    int mid = (l+r) >> 1;
    build(l, mid, lson);
    build(mid+1, r, rson);
}
void updata(int c, int l, int r, int rt)
{
    if(l <= s[rt].l && s[rt].r <= r){
        s[rt].c = c;
        s[rt].lsum = s[rt].rsum = s[rt].sum = c?0:s[rt].r-s[rt].l+1;
        return;
    }
    pushdown(rt, s[rt].r-s[rt].l+1);
    int mid = (s[rt].l+s[rt].r)>>1;
    if(l <= mid)
        updata(c, l, r, lson);
    if(mid < r)
        updata(c, l, r, rson);
    pushup(rt, s[rt].r-s[rt].l+1);
}
int query(int num, int rt)
{
    if(s[rt].l == s[rt].r) return s[rt].l;
    int mid = (s[rt].l + s[rt].r) >> 1;
    pushdown(rt, s[rt].r-s[rt].l+1);
    if(s[lson].sum >= num)
        return query(num, lson);
    if(s[lson].rsum + s[rson].lsum >= num)
        return mid-s[lson].rsum + 1;
    //if(s[rson].sum >= num)
        return query(num, rson);
}
vector <block> v;
int main()
{
    int n,m,x;
    char a[10];
    while(~scanf("%d%d",&n,&m))
    {
        build(1, n, 1);
        v.clear();
        while(m--){
            scanf("%s",a);
            if(a[0] == 'N'){//申请内存块
                scanf("%d",&x);
                if(s[1].sum < x) puts("Reject New");
                else{
                    int pos = query(x, 1);//找到最左端的那个内存单元的编号
                    printf("New at %d\n",pos);
                    updata(1, pos, pos+x-1, 1);//更新
                    block tmp;
                    tmp.l = pos;  tmp.r = pos+x-1;
                    vector<block>::iterator iter;//索引
                    iter = upper_bound(v.begin(), v.end(), tmp);//二分查找我们的左端点。
                    v.insert(iter, tmp);//存储我们每一块的编号
                }
            }
            if(a[0] == 'F'){//释放内存块
                scanf("%d",&x);
                block tmp;
                tmp.l = tmp.r = x;//假设第x个内存单元是一个内存块
                vector<block>::iterator iter;
                iter = upper_bound(v.begin(), v.end(), tmp);
                int pos = iter - v.begin() - 1;//upper_bound()返回的是大于tmp的第一个值
                if(pos == -1 || v[pos].r < x)
                    puts("Reject Free");
                else{
                    printf("Free from %d to %d\n", v[pos].l, v[pos].r);
                    updata(0, v[pos].l, v[pos].r, 1);
                    v.erase(v.begin()+pos);//删除
                }
            }
            if(a[0] == 'G'){
                scanf("%d",&x);
                if(x > v.size())
                    puts("Reject Get");
                else
                    printf("Get at %d\n",v[x-1].l);//vector是从0开始的
            }
            if(a[0] == 'R'){
                updata(0, 1, n, 1);
                v.clear();
                puts("Reset Now");
            }
        }
        printf("\n");
    }
    return 0;
}
```