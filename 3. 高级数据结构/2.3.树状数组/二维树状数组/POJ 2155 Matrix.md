题目

在某天夜里，krk 来到了一个长宽都是 n 的大草地上躺下思考人生（睡觉）。每块小草地中间有一盏灯，一开始灯都是暗着的。发现 krk 在睡觉，lh 决定操控所有灯的电路的开关来打扰他。每次她可以对一个矩形区间内的灯将其置反（灯开着则关掉，灯关着则开起来）。由于操作次数过多她也忘了某个位置 (x,y) 的位置的灯是亮着还是灭着的。现在你需要帮她确认一下指定位置的灯的开关情况。

输入

第一行输入 T 表示样例个数。

每个样例的第一行输入 n，q 表示草地长宽和询问个数。

每个样例接下来的 q 行每一行表示输入下面其中一个操作：

1. `C x1 y1 x2 y2`(1<=x1<=x2<=n,1<=y1<=y2<=n) 将左上角为 (�1,�1)(x1,y1), 右下角为(x2,y2) 的矩形内灯按上述操作执行。
2. `Q x y` (1<=x,y<=n) 查询指定位置 (x,y) 处的灯的情况。

输出

灯开着则输出 1，灯灭了则输出 0。**（任意两个样例输出之间有一空行）**

数据范围

1<=T<=10,2<=n<=1000,1<=q<=50000

样例输入

1  
2 10  
C 2 1 2 2  
Q 2 2  
C 2 1 2 1  
Q 1 1  
C 1 1 2 1  
C 1 2 1 2  
C 1 1 2 2  
Q 1 1  
C 1 1 2 1  
Q 2 1

样例输出

1  
0  
0  
1

## 题解
对于这种二维点修改+区间查询，我们还是用我们的二维树状数组吧，这样还是要简单一点。**将区间个更新转换为了点更新，主要是0和1之间的转换是循环的，可以通过记录转换的次数，对2取余之后就是结果，有一点互斥的思想，在进行区块相减的时候。总得来说很神奇。先从一维来理解会比较简单。**

方法：
我们对于每一个输入，在我们的**对应左上角++，右下角--**，就当成是二位区间上的差分数组，然后我们每一次求和的时候，再去求在这个位置上的和就可以了。也就相当于我们的单点修改，和我们的区间求和了。随后我们的**求和记得要模 2 才是我们的最后结果**
```cpp
1 // Cease to struggle and you cease to live
 2 #include <iostream>
 3 #include <cmath>
 4 #include <cstdio>
 5 #include <cstring>
 6 #include <algorithm>
 7 #include <queue>
 8 #include <vector>
 9 #include <set>
10 #include <map>
11 #include <stack>
12 using namespace std;
13 typedef long long ll;
14 const int N=1000+8;
15 int n;
16 int tr[N][N];
17 char s[3];
18 void add(int x,int y){
19     for(int tx=x;tx<=n;tx+=tx&-tx){
20         for(int ty=y;ty<=n;ty+=ty&-ty){
21             ++tr[tx][ty];
22 }
23 }
24 }
25 int sum(int x,int y){
26     int res=0;
27     for(int tx=x;tx;tx-=tx&-tx){
28         for(int ty=y;ty;ty-=ty&-ty){
29             res+=tr[tx][ty];
30 }
31 }
32     return res;
33 }
34 int main() {
35     int T;scanf("%d",&T);
36     for(int t=1;t<=T;++t){
37         memset(tr,0,sizeof(tr));
38         scanf("%d",&n);
39         int qn;scanf("%d",&qn);
40         for(int i=1;i<=qn;++i){
41             scanf("%s",s);
42             int x1,x2,y1,y2;
43             scanf("%d%d",&x1,&y1);
44             if(s[0]=='C'){
45                 scanf("%d%d",&x2,&y2);
46                 add(x1,y1);add(x2+1,y2+1);add(x1,y2+1);add(x2+1,y1);
47 }
48             else{
49                 printf("%d\n",sum(x1,y1)%2);
50 }
51 }
52         cout<<endl;
53 }
54     return 0;
55 }
```