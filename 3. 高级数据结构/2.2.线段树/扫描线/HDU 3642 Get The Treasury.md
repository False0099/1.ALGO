Jack knows that there is a great underground treasury in a secret region. And he has a special device that can be used to detect treasury under the surface of the earth. One day he got outside with the device to ascertain the treasury. He chose many different locations on the surface of the earth near the secret region. And at each spot he used the device to detect treasury and got some data from it representing a region, which may contain treasury below the surface. The data from the device at each spot is six integers x1, y1, z1, x2, y2 and z2 (x1<x2, y1<y2, z1<z2). According to the instruction of the device they represent the range of x, y and z coordinates of the region. That is to say, the x coordinate of the region, which may contain treasury, ranges from x1 to x2. So do y and z coordinates. The origin of the coordinates is a fixed point under the ground.  
Jack can’t get the total volume of the treasury because these regions don’t always contain treasury. Through years of experience, he discovers that if a region is detected that may have treasury at more than two different spots, the region really exist treasure. And now Jack only wants to know the minimum volume of the treasury.  
Now Jack entrusts the problem to you.  
  

Input

The first line of the input file contains a single integer t, the number of test cases, followed by the input data for each test case.  
Each test case is given in some lines. In the first line there is an integer n (1 ≤ n ≤ 1000), the number of spots on the surface of the earth that he had detected. Then n lines follow, every line contains six integers x1, y1, z1, x2, y2 and z2, separated by a space. The absolute value of x and y coordinates of the vertices is no more than 106, and that of z coordinate is no more than 500.  
  

Output

For each test case, you should output “Case a: b” in a single line. a is the case number, and b is the minimum volume of treasury. The case number is counted from one.  

Sample

|Inputcopy|Outputcopy|
|---|---|
|2<br>1<br>0 0 0 5 6 4<br>3<br>0 0 0 5 5 5<br>3 3 3 9 10 11<br>3 3 3 13 20 45|Case 1: 0<br>Case 2: 8|

## 题解
本题是我们的立方体体积交，即给定若干个立方体，要我们求我们体积的交。这个我们其实也可以采用我们扫描线的思路。**即我们动态给定若干个长方形，每一次更新，我们都要求出我们图形上的面积并，并乘以一个数值，问我们最后我们的面积和为多少**。我们用一根扫描线扫描 z 轴，每一次我们每一个矩形被经过的次数，然后统计出所有中经过次数超过三次的部分。

```cpp
#include <bits/stdc++.h>
 
#define lson x<<1
#define rson x<<1|1
using namespace std;
typedef long long LL;
const int maxn = 2e3+223;
const int maxz = 505;
int T,n,x,y,z,xx,yy,zz,len,X[maxn],Z[maxn],tr[maxn<<2][4],tag[maxn<<2];
struct node{
    int l,r,w,h1,h2,op;
};
vector<node> ve,we;
void init(){
    len = 0;
    ve.clear();
}
bool cmp(node a,node b){
    return a.w < b.w;
}
void pushup(int x,int l,int r){
    if(tag[x] >= 3){
        tr[x][3] = X[r+1]-X[l];
        tr[x][2] = tr[x][1] = 0;
    }
    else if(tag[x] == 2){
        tr[x][1] = 0;
        tr[x][3] = tr[lson][1]+tr[rson][1]+tr[lson][2]+tr[rson][2]+tr[lson][3]+tr[rson][3];
        tr[x][2] = X[r+1]-X[l]-tr[x][3];
    }
    else if(tag[x] == 1){
        tr[x][3] = tr[lson][2]+tr[rson][2]+tr[lson][3]+tr[rson][3];
        tr[x][2] = tr[lson][1]+tr[rson][1];
        tr[x][1] = X[r+1]-X[l]-tr[x][3]-tr[x][2];
    }
    else{
        tr[x][1] = tr[lson][1] + tr[rson][1];
        tr[x][2] = tr[lson][2] + tr[rson][2];
        tr[x][3] = tr[lson][3] + tr[rson][3];
    }
}
void updata(int l,int r,int L,int R,int x,int op){
    if(l > R || r < L) return ;
    if(l >= L && r <= R){
        tag[x] += op;
        pushup(x,l,r);
        return ;
    }
    int mid = (l+r)>>1;
    updata(l,mid,L,R,lson,op);
    updata(mid+1,r,L,R,rson,op);
    pushup(x,l,r);
}
LL cal(){                                    //计算扫描线
    sort(we.begin(),we.end(),cmp);
    LL res = 0;
    for(int i = 0;i < (int)we.size(); ++i){
        int L = lower_bound(X,X+len,we[i].l)-X;
        int R = lower_bound(X,X+len,we[i].r)-X-1;
        updata(0,len,L,R,1,we[i].op);
        if(i<(int)we.size()-1) res += 1LL*tr[1][3]*(we[i+1].w-we[i].w);
    }
    return res;
}
LL solve(){                                  
    sort(X,X+len);sort(Z,Z+len);
    int lenz = unique(Z,Z+len) - Z;         //离散X,Z坐标
    len = unique(X,X+len) - X;
    LL res = 0;
    for(int i = 0;i < lenz-1; ++i){         //计算扫描面
        we.clear();                      
        for(int j = 0;j < (int)ve.size(); ++j){
            if(ve[j].h1 <= Z[i] && ve[j].h2 >= Z[i+1]) we.push_back(ve[j]);
        }
        res += cal()*(Z[i+1]-Z[i]);
    }
    return res;
}
int main(){
    cin >> T;
    for(int Case = 1;Case <= T; ++Case){
        cin >> n; init();
        while(n--){
            cin>>x>>y>>z>>xx>>yy>>zz;
            X[len] = x,X[len+1] = xx;
            Z[len] = z,Z[len+1] = zz;
            len += 2; 
            ve.push_back(node{x,xx,y,z,zz,1});
            ve.push_back(node{x,xx,yy,z,zz,-1});
        }
        printf("Case %d: %lld\n",Case,solve());
    }
    return 0;
}
```