You are given n closed, integer intervals $[ai, bi]$ and n integers c1, ..., cn.  
  
Write a program that:  
  
> reads the number of intervals, their endpoints and integers c1, ..., cn from the standard input,  
  
> computes the minimal size of a set Z of integers which has at least ci common elements with interval $[ai, bi]$, for each i = 1, 2, ..., n,  
  
> writes the answer to the standard output.

  
**Input**  
  
The first line of the input contains an integer n (1 <= n <= 50 000) - the number of intervals. The following n lines describe the intervals. The i+1-th line of the input contains three integers ai, bi and ci separated by single spaces and such that 0 <= ai <= bi <= 50 000 and 1 <= ci <= bi - ai + 1.

Process to the end of file.

  
**Output**  
  
The output contains exactly one integer equal to the minimal size of set Z sharing at least ci elements with interval $[ai, bi]$, for each i = 1, 2, ..., n.

  
**Sample Input**  
  
5  
3 7 3  
8 10 3  
6 8 1  
1 3 1  
10 11 1

  
**Sample Output**  
  
6

## 题解
我们这一题的难点在于建模，我们对每个数设一个变量 $x_{i}$,如果他出现了，那么我们有 $x_{i}=1$,否则 $x_{i}=0$,对于一个区间 $[l,r]:k$,我们有 $x_{l}+x_{l+1}+\dots+x_{r}\geq k$,但是我们不符合形式，我们用我们的 $S[x]$ 表示我们 $x[]$ 的前缀和，显然我们有 $0\leq S_{i}-S_{i-1}\leq 1$,区间 $[l,r]:k$ 的式子就变成了 $S_{r}-S_{l-1}\geq k$ 初始值为 $S_{-1}=0$，我们的答案就是我们的 $S_{n}$ 的最小值，我们求最长路即可。

```cpp
1 #include <cstdio>
 2 #include <cstring>
 3 #include <cstdlib>
 4 #include <cmath>
 5 #include <vector>
 6 #include <map>
 7 #include <set>
 8 #include <stack>
 9 #include <queue>
10 #include <iostream>
11 #include <algorithm>
12 using namespace std;
13 #define lp (p << 1)
14 #define rp (p << 1|1)
15 #define getmid(l,r) (l + (r - l) / 2)
16 #define MP(a,b) make_pair(a,b)
17 typedef long long ll;
18 typedef unsigned long long ull;
19 typedef pair<int,int> pii;
20 const int INF = (1 << 30) - 1;
21 const int maxn = 50010;
22 
23 int N,tmax,tmin;
24 int first[maxn],ecnt;
25 int inq[maxn],dis[maxn];
26 
27 struct edge{
28     int v,next,cost;
29 }e[3 * maxn];
30 
31 void Add_edge(int u,int v,int c){
32     e[++ecnt].next = first[u];
33     e[ecnt].v = v;
34     e[ecnt].cost = c;
35     first[u] = ecnt;
36 }
37 
38 void Spfa(int s){
39     queue<int> Q;
40     memset(inq,0,sizeof(inq));
41     for(int i = tmin; i <= tmax; ++i) dis[i] = -INF;
42     inq[s] = 1;
43     dis[s] = 0;
44 Q.push(s);
45     while(!Q.empty()){
46         int x = Q.front(); Q.pop();
47         inq[x] = 0;
48         for(int i = first[x]; i != -1; i = e[i].next){
49             int v = e[i].v;
50             if(dis[v] < dis[x] + e[i].cost){
51                 dis[v] = dis[x] + e[i].cost;
52                 if(inq[v] == 0){
53                     inq[v] = 1;
54 Q.push(v);
55 }
56 }
57 }
58 }
59 }
60 
61 int main(){
62     int a,b,c;
63     while(scanf("%d",&N) != EOF){
64         memset(first,-1,sizeof(first));
65         ecnt = tmax = 0;
66         tmin = INF;
67         for(int i = 1; i <= N; ++i){
68             scanf("%d%d%d",&a,&b,&c);
69             a++;
70             b++;
71             //S(b) - S(a-1) >= c
72             //S(b) >= S(a - 1) + c
73             Add_edge(a - 1,b,c);
74             tmax = max(tmax,b);
75             tmin = min(tmin,a - 1);
76 }
77         //S(i) - S(i - 1) >= 0
78         //S(i) - S(i - 1) <= 1 --> S(i - 1) - S(i) >= -1
79         for(int i = tmin + 1; i <= tmax; ++i){
80             Add_edge(i - 1,i,0);
81             Add_edge(i,i - 1,-1);
82 }
83 Spfa(tmin);
84         printf("%d\n",dis[tmax]);
85 }
86     return 0;
87 }
```