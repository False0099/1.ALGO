可怜的 dd，因为没按时回校，导致他被困在家乡。  
郁闷的dd决定在家乡种树，他拥有N棵树苗(1≤N≤50,000)，编号从1到N，一天，dd决定带着一些树苗出去种。简单起见，他决定带一排编号连续的树苗出门种下。然而，为了方便携带，dd需要知道这排编号连续树苗最高与最矮树苗的高度差。  
由于dd有选择困难症，他列出了Q（1≤Q<=200,000）种编号连续树苗的取法，每种取法包括l,r两个数（1≤l≤r≤N），表示所取树苗的最小和最大编号，请你帮忙告诉他每种取法的最高与最矮树苗的高度差。

## Input

第一行：树苗数N和取法数Q  
第二行到第N+1行：第i+1行包含一个整数，表示第i棵树苗的高度  
第N+2行到第N+Q+1行：每行包含空格隔开的两个整数l，r(1≤l≤r≤N)，表示所取树苗的最小和最大编号。

## Output

每行包含一个整数，是对每组范围的回答，表示范围内最高和最矮树苗之间的高度差

## Sample

|Inputcopy|Outputcopy|
|---|---|
|6 3<br>1<br>7<br>3<br>4<br>2<br>5<br>1 5<br>4 6<br>2 2|6<br>3<br>0|

## 题解
这种题没有任何修改，我们理论上的最优是通过我们的 ST 表来实现，但我们也可以用我们的线段树来维护我们的最大值、最小值。
```CPP
1 #include <stdio.h>
 2 #include <string.h>
 3 #define maxn 500500
 4 
 5 int max(int x,int y) 6 {
 7     return x > y? x : y ; 8 }
 9 int min(int x,int y)
10 {
11     return x > y? y : x;
12 }
13 
14 struct note{
15 
16     int Min,Max;
17 
18 }segtree[ maxn * 2];
19 
20 int arra[ maxn ];
21 
22 
23 void build(int root , int arr[] , int instart , int iend)
24 {
25     if(instart == iend)
26 {
27       //  segtree[ root ].val = arr[ instart ];
28         segtree[ root ].Max = arr[ instart ];
29         segtree[ root ].Min = arr[ instart ];
30 }
31     else
32 {
33         int mid = (instart+iend)/2;
34         build( root * 2 , arr , instart , mid );
35         build( root * 2 + 1 , arr , mid + 1 , iend );
36         segtree[ root ].Max = max(segtree[ root * 2 ].Max,segtree[ root * 2 + 1 ].Max);
37         segtree[ root ].Min = min(segtree[ root * 2 ].Min,segtree[ root * 2 + 1 ].Min);
38 }
39 }
40 
41 int remin(int root ,int nstart , int nend , int qstart , int qend)
42 {
43     if(qstart > nend || qend < nstart)
44         return maxn*10;
45     if( qstart <= nstart && qend >= nend )
46         return segtree[ root ].Min;
47     int mid =( nstart + nend ) / 2;
48     return min(remin(root * 2,nstart,mid,qstart,qend),
49                remin(root * 2 + 1 , mid + 1 , nend , qstart , qend ));
50 }
51 int reMax(int root , int nstart , int nend , int qstart , int qend)
52 {
53     if(qstart > nend || qend < nstart)
54         return 0;
55     if(qstart <= nstart && qend >= nend )
56         return segtree [ root ].Max;
57     int mid = ( nstart + nend ) / 2;
58     return max(reMax(root * 2, nstart , mid , qstart , qend ),
59                reMax(root * 2 + 1 , mid + 1 , nend , qstart , qend ) );
60 }
61 
62 int main()
63 {
64   //  freopen("in.txt","r",stdin);
65     int m,n,a,b,ma,mi;
66     scanf("%d%d",&m,&n);
67     for( int i = 1 ; i <= m ; i++ )
68         scanf("%d",&arra[ i ]);
69     build(1,arra,1,m);
70     while(n--)
71 {
72         scanf("%d%d",&a,&b);
73         ma = reMax(1,1,m,a,b);
74         mi = remin(1,1,m,a,b);
75         printf("%d\n",ma-mi);
76 }
77     return 0;
78 }
```