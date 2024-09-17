一群人在播种，每个种子占据一个单位（别太在意是什么单位）的正方形块。

但是有时候会有人将几个种子播种在一起，当两个种子在同一个正方形块里面的时候，他们就会相互争夺养分，价格高的植物会活下来。如果他们的价格相同，也得死得只剩一个。

现在给了你m种种子，求你可以得到多少钱。

Input

第一行是 T (T <= 10), 表示有多少组测试。  
每组测试第一行是 n, m (1 <= n <= 30000, 1 <= m <= 3).  
第二行有 m 个整数 p i (1 <= p i <= 100), 表示种子的价格。  
接下来 n 行，每行有  x1, y1, x2, y2, s, 表示第s种种子播种在一个左下角为 ( x1, y1), 右上角为( x2, y2) 的矩阵里

All of x1, y1, x2, y2 will be no larger than 10 6 in their absolute values.

Output

每组测试，输出最后的总收入

Sample Input

		2
1 1
25
0 0 10 10 1
2 2
5 2
0 0 2 1 1
1 0 3 2 2 

Sample Output

Case 1: 2500
Case 2: 16

## 题解
我们把我们的价格转化成我们的长方体的高，然后我们再利用长方形体积并来计算即可。（看似不是立体几何的问题，我们现在还是用计算几何的方法来计算出来了）

本质上，我们的三维体积交还是在求我们的二维平面正方形交，但与之不同的时，我们每一次的更新是有操作顺序的，具体来说就是把我们的**操作按照 z 轴排序，然后按照 z 的顺序来进行我们的更新操作，这样我们得到的才是我们的正确答案。**

~~~cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <map>
#define ll long long 
#define maxn 30000*2+10
#define lson l, m, rt<<1
#define rson m, r, rt<<1|1
Using namespace std;
Struct Seg{
    Int l, r, h, c;
    Seg (){}
    Seg (int a, int b, int c, int d): l (a), r (b), h (c), c (d){}
    Bool operator<(const Seg & a) const{
        return h<a.h;
    }
}segs[maxn];
Struct cube{
    Int x 1, y 1, z 1, x 2, y 2, z 2;
    Cube (){}
    Cube (int a, int b, int c, int d, int e, int f): x 1 (a), y 1 (b), z 1 (c), x 2 (d), y 2 (e), z 2 (f){}
}cubes[maxn];
Int seeds[4], n, m;
Int y[maxn<<2], toty, tot;
Int z[maxn], totz;
map<int,int>mp;
Ll cnt[maxn<<2], len[maxn<<2];
Void init (){
    Tot=toty=totz=0;
    Mp.Clear ();
    Memset (cnt, 0, sizeof cnt);
    Memset (len, 0, sizeof len);
}

Inline void pushup (int rt, int l, int r){
    If (cnt[rt]){
        Len[rt]=y[r]-y[l];    
    }
    Else if (l+1==r) len[rt]=0;
    Else len[rt]=len[rt<<1]+len[rt<<1|1];
}
Void update (int L, int R, int c, int l, int r, int rt){
    if (L<=l && R>=r){
        Cnt[rt]+=c;
        Pushup (rt, l, r);
        Return;
    }
    Int m=l+r>>1;
    If (L<m) update (L, R, c, lson);
    If (R>m) update (L, R, c, rson);
    Pushup (rt, l, r);
}
Int main (){
    Int T, a, b, c, d, e;
    Cin >> T;
    For (int tt=1; tt<=T; tt++){
        Init ();
        Cin >> n >> m;
        For (int i=1; i<=m; i++) scanf ("%d",&seeds[i]);
        Z[tot++]=0;//把地平线加上！
        For (int i=1; i<=n; i++){
            Scanf ("%d%d%d%d%d",&a,&b,&c,&d,&e);
            Cubes[i]=cube (a, b, 0, c, d, seeds[e]);
            Z[totz++]=seeds[e];
            Y[toty++]=b; y[toty++]=d;
        }
        Z[totz++]=0;
        Sort (z, z+totz); totz=unique (z, z+totz)-z;//离散化 z 轴
        Sort (y, y+toty); toty=unique (y, y+toty)-y;//离散化 x 轴
        For (int i=0; i<toty; i++) mp[y[i]]=i;

        Ll res=0;
        For (int i=0; i<totz-1; i++){
            Tot=0;//初始化
            Memset (segs, 0, sizeof segs);  
            For (int j=1; j<=n; j++){//遍历所有 cubes，把符合条件的加进去
                if (cubes[j]. Z 1<=z[i] && cubes[j].z2>=z[i+1]){
                    Segs[tot++]=Seg (cubes[j]. Y 1, cubes[j]. Y 2, cubes[j]. X 1,1);
                    Segs[tot++]=Seg (cubes[j]. Y 1, cubes[j]. Y 2, cubes[j]. X 2,-1);
                }
            }
            Sort (segs, segs+tot);
            For (int j=0; j<tot; j++){
                If (j!=0)
                    Res+=(ll)(z[i+1]-z[i])*(segs[j]. H-segs[j-1]. H)*len[1];
                Update (mp[segs[j]. L], mp[segs[j]. R], segs[j]. C, 0, toty-1,1);
                
            }
        }
        Printf ("Case %d: %lld\n", tt, res);
    }
    Return 0;
}
```