City F in the southern China is preparing lanterns festival celebration along the streets to celebrate the festival.  
Since frequent accidents had happened last year when the citizens went out to admire the colorful lanterns, City F is planning to develop a system to calculate the degree of congestion of the intersection of two streets.  
The map of City F is organized in an N×N grid (N north-south streets and N west-east street). For each intersection of streets, we define a density value for the crowd on the intersection.  
Initially, the density value of every intersection is zero. As time goes by, the density values may change frequently. A set of cameras with new graphical recognition technology can calculate the density value of the intersection easily in a short time.  
But the administrator of the police office is planning to develop a system to calculate the degree of congestion. For some consideration, they come up with a conception called "k-dimension congestion degree". The "k-dimension congestion degree" of intersection (x0,y0) is represented as "c(x0,y0,k)", and it can be calculated by the formula below:  

![](https://vj.csgrandeur.cn/6927c3c55a6e64ed5b56ad968cd6d195?v=1694810199)

  
Here, d(x,y) stands for the density value on intersection (x,y) and (x,y) must be in the N×N grid. The formula means that all the intersections in the range of manhattan distance k from (x0,y0) effect the k-dimension congestion degree of (x0,y0) equally, so we just simply sum them up to get the k-dimension congestion degree of (x0,y0).  
The figure below shows a 7×7 grid, and it shows that if you want to get the 2-dimension congestion degree of intersection (4,2),you should sum up the density values of all marked intersections.  

![](https://vj.csgrandeur.cn/253598e28f9fe033c4d79bfe6023a588?v=1694810199)

  

Input

These are multiple test cases.  
Each test case begins with a line with two integers N, M, meaning that the city is an N×N grid and there will be M queries or events as time goes by. (1 ≤ N ≤10 000, 1 ≤ M ≤ 80 000) Then M lines follow. Each line indicates a query or an event which is given in form of (p, x, y, z), here p = 1 or 2, 1 ≤ x ≤ N, 1 ≤ y ≤ N.  
The meaning of different p is shown below.  
1. p = 1 the value of d(x,y) is increased by z, here -100 ≤ z ≤ 100.  
2. p = 2 query the value of c(x,y,z), here 0 ≤ z ≤ 2N-1.  
Input is terminated by N=0.  

Output

For each query, output the value for c(x,y,z) in a line.

## 题解
我们这一题相当于我们的二维树状数组，把我们的单点修改，然后求我们内到某点曼哈顿距离得权值和。

我们把矩阵侧过来 45，发现询问的时候，有效的点构成的事实上是一个矩阵，然后我们就变成了单点修改，求矩阵和得问题


```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#define lowbit(x) (x&(-x))
using namespace std ;
struct Operation {
    int op , x , y , z ;
} p[88888] ;
int base = 100000 ;
const int N = 2222222 ;
vector<int> mp ;
int val[N] , tot , n , m ;
const int maxn = 22222 ;

inline int get ( int x , int y ) {
    x = x * base + y ;
    y = lower_bound(mp.begin(),mp.end(),x) - mp.begin() ;
    if ( y == tot || mp[y] != x ) return -1 ;
    return y ;
}

void update ( int x , int y , int z ) {
    while ( x < n*2+100 ) {
        int pos = y ;
        while ( pos < n*2+100 ) {
            int now = get (x,pos) ;
            val[now] += z ;
            pos += lowbit ( pos ) ;
        }
        x += lowbit ( x ) ;
    }
}

int sum ( int x , int y ) {
    int ret = 0 ;
    while ( x ) {
        int pos = y ;
        while ( pos ) {
            int now = get ( x , pos ) ;
            if (now != -1) ret += val[now] ;
            pos -= lowbit ( pos ) ;
        }
        x -= lowbit ( x ) ;
    }
    return ret ;
}

int query ( int x1 , int y1 , int x2 , int y2 ) {
    int ret1 = sum(x1-1,y1-1) , ret2 = sum(x2,y2) , ret3 = sum(x1-1,y2) , ret4 = sum(x2,y1-1) ;
//    printf ( "ret2 = %d\n" , ret2 ) ;
    return ret1+ret2-ret3-ret4 ;
}

int get_num () {
    int n = 0 , flag = 1 ;
    char c ;
    while ( (c = getchar ()) && c != '-' && (c<'0'||c>'9') ) ;
    if ( c == '-' ) flag = -1 ;
    else n = c - '0' ;
    while ( (c = getchar ()) && c >= '0' && c <= '9' ) n = n * 10 + c - '0' ;
    return n * flag ;
}

void add ( int t , int x , int y ) {
        while ( x < n*2+100 ) {
            int pos = y ;
            while ( pos < n*2+100 ) {
			//	if ( tot == N - 1 ) while (1) ;
                mp.push_back ( x * base + pos ) ;
                pos += lowbit ( pos ) ;
            }
            x += lowbit ( x ) ;
        }
}

void read ( int i ) {
    p[i].op = get_num () ;
    p[i].x = get_num () ;
    p[i].y = get_num () ;
    p[i].z = get_num () ;
    int x = p[i].x + p[i].y - 1 , y = n - p[i].x + p[i].y ;
    if ( p[i].op == 1 ) add ( 1 , x , y ) ;
}

int main () {
	while ( scanf ( "%d" , &n ) && n ) {
        scanf ( "%d" , &m ) ;
        mp.clear () ;
        memset ( val , 0 , sizeof ( val ) ) ;
        for ( int i = 1 ; i <= m ; i ++ )
            read ( i ) ;
        sort ( mp.begin() , mp.end() ) ;
        vector<int>::iterator it = unique(mp.begin() , mp.end()) ;
        mp.erase(it,mp.end()) ;
   //     tot = unique ( mp + 1 , mp + tot + 1 ) - mp - 1 ;
		tot = mp.size () ;
        for ( int i = 1 ; i <= m ; i ++ ) {
            int op , x , y , z ;
            op = p[i].op ;
            x = p[i].x ;
            y = p[i].y ;
            z = p[i].z ;
    //        printf ( "op = %d , x = %d , y = %d , z = %d\n" , op , x , y , p[i].z ) ;
            int xx = x + y - 1 , yy = n - x + y ;
            if ( op == 1 ) {
                update ( xx , yy , z ) ;
            } else {
                int x1 = std::max ( 1 , xx  - z ) ;
                int y1 = std::max ( 1 , yy  - z ) ;
                int x2 = std::min ( 2*n-1 , xx  + z ) ;
                int y2 = std::min ( 2*n-1 , yy  + z ) ;
                printf ( "%d\n" , query ( x1 , y1 , x2 , y2 ) ) ;
            }
        }
    }
    return 0 ;
}
```