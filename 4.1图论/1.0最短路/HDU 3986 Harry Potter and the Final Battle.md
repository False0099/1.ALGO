The final battle is coming. Now Harry Potter is located at city 1, and Voldemort is located at city n. To make the world peace as soon as possible, Of course, Harry Potter will choose the shortest road between city 1 and city n. But unfortunately, Voldemort is so powerful that he can choose to destroy any one of the existing roads as he wish, but he can only destroy one. Now given the roads between cities, you are to give the shortest time that Harry Potter can reach city n and begin the battle in the worst case.  

  
给一个无向图，问任意删除一条边，求点 1 到点 n 的最短路径的最长长度,如果能使1不能到达n，输出-1.

Input

First line, case number t (t<=20).  
Then for each case: an integer n (2<=n<=1000) means the number of city in the magical world, the cities are numbered from 1 to n. Then an integer m means the roads in the magical world, m (0< m <=50000). Following m lines, each line with three integer u, v, w (u != v,1 <=u, v<=n, 1<=w <1000), separated by a single space. It means there is a bidirectional road between u and v with the cost of time w. There may be multiple roads between two cities.  
  
第一行 t 表示数据组数  
对于每组测试数据  
n 表示点数，m 表示双向边数  
接下来 m 行，u，v，w 表示 u 到 v 有一条边权为 w 的边  
2<=n<=1000,2<m<=50000,1<=w<1000

Output

Each case per line: the shortest time to reach city n in the worst case. If it is impossible to reach city n in the worst case, output “-1”.  
  
对于每组测试数据输出最长长度，若无路径输出-1

Sample Input

3
4
4
1 2 5
2 4 10
1 3 3
3 4 8
3
2
1 2 5
2 3 10
2
2
1 2 1
1 2 2

Sample Output

15
-1
2

## 题解
我们本题的思路是，先求一次最短路，同时记录在最短路上的定点以及该顶点为狐尾的最短路上的边，然后枚举删除每一条边，分别求一次最短路，其中最大的就是答案，

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
 
#define REP( i , a , b ) for ( int i = ( a ) ; i < ( b ) ; ++ i )
#define FOR( i , a , b ) for ( int i = ( a ) ; i <= ( b ) ; ++ i )
#define REV( i , a , b ) for ( int i = ( a ) ; i >= ( b ) ; -- i )
#define CLR( a , x ) memset ( a , x , sizeof a )
 
const int MAXN = 1005 ;
const int MAXH = 100005 ;
const int MAXE = 100005 ;
const int INF = 0x3f3f3f3f ;
 
struct Edge {
	int v , c , n ;
	
	Edge () {}
	
	Edge ( int v , int c , int n ) : v ( v ) , c ( c ) , n ( n ) {}
} ;
 
struct Heap {
	int v , idx ;
	
	Heap () {}
	
	Heap ( int v , int idx ) : v ( v ) , idx ( idx ) {}
	
	bool operator < ( const Heap& a ) const {
		return v < a.v ;
	}
} ;
 
struct priority_queue {
	Heap heap[MAXH] ;
	int point ;
	
	priority_queue () : point ( 1 ) {}
	
	void clear () {
		point = 1 ;
	}
	
	bool empty () {
		return point == 1 ;
	}
	
	void maintain ( int o ) {
		int x = o ;
		while ( o > 1 && heap[o] < heap[o >> 1] ) {
			swap ( heap[o] , heap[o >> 1] ) ;
			o >>= 1 ;
		}
		o = x ;
		int p = o , l = o << 1 , r = o << 1 | 1 ;
		while ( o < point ) {
			if ( l < point && heap[l] < heap[p] ) p = l ;
			if ( r < point && heap[r] < heap[p] ) p = r ;
			if ( p == o ) break ;
			swap ( heap[o] , heap[p] ) ;
			o = p , l = o << 1 , r = o << 1 | 1 ;
		}
	}
	
	void push ( int v , int idx ) {
		heap[point] = Heap ( v , idx ) ;
		maintain ( point ++ ) ;
	}
	
	void pop () {
		heap[1] = heap[-- point] ;
		maintain ( 1 ) ;
	}
 
	int front () {
		return heap[1].idx ;
	}
	
	Heap top () {
		return heap[1] ;
	}
} ;
 
struct Shortest_Path_Algorithm {
	priority_queue q ;
	Edge E[MAXE] ;
	int H[MAXN] , cur ;
	int d[MAXN] ;
	bool vis[MAXN] ;
	int used[MAXN] ;
	int f[MAXN] ;
	int Q[MAXN] , head , tail ;
	
	void init () {
		cur = 0 ;
		CLR ( H , -1 ) ;
	}
	
	void addedge ( int u , int v , int c = 0 ) {
		E[cur] = Edge ( v , c , H[u] ) ;
		H[u] = cur ++ ;
	}
	
	void dijkstra ( int s , int t , int closed ) {
		q.clear () ;
		CLR ( d , INF ) ;
		CLR ( vis , 0 ) ;
		d[s] = 0 ;
		q.push ( d[s] , s ) ;
		while ( !q.empty () ) {
			int u = q.front () ;
			q.pop () ;
			if ( vis[u] ) continue ;
			vis[u] = 1 ;
			for ( int i = H[u] ; ~i ; i = E[i].n ) {
				int v = E[i].v , c = E[i].c ;
				if ( i != closed && d[v] > d[u] + c ) {
					d[v] = d[u] + c ;
					q.push ( d[v] , v ) ;
					if ( closed == -1 ) {
						f[v] = u ;
						used[v] = i ;
					}
				}
			}
		}
	}
	
	void spfa ( int s , int t , int closed ) {
		head = tail = 0 ;
		CLR ( d , INF ) ;
		CLR ( vis , 0 ) ;
		d[s] = 0 ;
		Q[tail ++] = s ;
		while ( head != tail ) {
			int u = Q[head ++] ;
			if ( head == MAXN ) head = 0 ;
			vis[u] = 0 ;
			for ( int i = H[u] ; ~i ; i = E[i].n ) {
				int v = E[i].v , c = E[i].c ;
				if ( i != closed && d[v] > d[u] + c ) {
					d[v] = d[u] + c ;
					if ( !vis[v] ) {
						vis[v] = 1 ;
						if ( d[v] < d[Q[head]] ) {
							if ( head == 0 ) head = MAXN ;
							Q[-- head] = v ;
						} else {
							Q[tail ++] = v ;
							if ( tail == MAXN ) tail = 0 ;
						}
					}
					if ( closed == -1 ) {
						f[v] = u ;
						used[v] = i ;
					}
				}
			}
		}
	}
} G ;
 
int n , m ;
 
void scanf ( int& x , char c = 0 ) {
	while ( ( c = getchar () ) < '0' || c > '9' ) ;
	x = c - '0' ;
	while ( ( c = getchar () ) >= '0' && c <= '9' ) x = x * 10 + c - '0' ;
}
 
void solve () {
	int u , v , c ;
	G.init () ;
	scanf ( n ) ;
	scanf ( m ) ;
	while ( m -- ) {
		scanf ( u ) , scanf ( v ) , scanf ( c ) ;
		G.addedge ( u , v , c ) ;
		G.addedge ( v , u , c ) ;
	}
	G.spfa ( 1 , n , -1 ) ;
	if ( G.d[n] == INF ) {
		printf ( "-1\n" ) ;
		return ;
	}
	int ans = G.d[n] ;
	for ( int i = n ; i != 1 ; i = G.f[i] ) {
		G.spfa ( 1 , n , G.used[i] ) ;
		if ( G.d[n] > ans ) ans = G.d[n] ;
		if ( ans == INF ) break ;
	}
	printf ( "%d\n" , ans == INF ? -1 : ans ) ;
}
 
int main () {
	int T ;
	scanf ( "%d" , &T ) ;
	while ( T -- ) solve () ;
	return 0 ;
}
```