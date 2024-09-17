My birthday is coming up and traditionally I'm serving pie. Not just one pie, no, I have a number N of them, of various tastes and of various sizes. F of my friends are coming to my party and each of them gets a piece of pie. This should be one piece of one pie, not several small pieces since that looks messy. This piece can be one whole pie though.  
  
  
  
My friends are very annoying and if one of them gets a bigger piece than the others, they start complaining. Therefore all of them should get equally sized (but not necessarily equally shaped) pieces, even if this leads to some pie getting spoiled (which is better than spoiling the party). Of course, I want a piece of pie for myself too, and that piece should also be of the same size.  
  
  
  
What is the largest possible piece size all of us can get? All the pies are cylindrical in shape and they all have the same height 1, but the radii of the pies can be different.

有 N 个圆形蛋糕 F 个朋友和你自己都要吃蛋糕。每个人分到的蛋糕的面积必须是一样的，并且每个人分到的蛋糕必须是一整块（不能是几个碎块拼凑而成，即这一整块蛋糕是从一个圆形蛋糕中切下的完整一块）。求每个人分到的蛋糕的面积最大为多少。

## Input

One line with a positive integer: the number of test cases. Then for each test case:

- One line with two integers N and F with 1 ≤ N, F ≤ 10 000: the number of pies and the number of friends.
- One line with N integers ri with 1 ≤ ri ≤ 10 000: the radii of the pies.

第一行包括一个整数，表示数据组数。对于每组数据：

- 第一行包括 N,F（1≤N,F≤10000） 两个整数，表示圆形蛋糕数量和朋友数量。
- 第二行包括 N 个整数 ri​（1≤ri​≤10000），表示 N 个圆形蛋糕的半径。

## Output

对于每组数据，输出一个浮点数，表示每人分到的蛋糕面积的最大值。你输出的答案与标准答案之差不能超过 10−3。



Sample

|Inputcopy|Outputcopy|
|---|---|
|3<br>3 3<br>4 3 3<br>1 24<br>5<br>10 5<br>1 4 2 3 4 5 6 5 4 2|25.1327<br>3.1416<br>50.2655|


## 题解
题目要求**每个人只能分到一种蛋糕**，
我们本题采用二分答案的方法，二分我们的体积
check 函数**比较当前状态下人数和 $f+1$ 的相对大小**，如果够分，我们就向右找，反之向左找。

```cpp

#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<algorithm>

#define ll long long
#define int ll
#define inf 0x3f3f3f3f
#define PI acos(-1.0)
using namespace std;
int ksm(int a, int b, int mod) { int s = 1; while(b) {if(b&1) s=s*a%mod;a=a*a%mod;b>>=1;}return s;}
const int N = 10010;
int n, f;//n表示买了n个不同半径的蛋糕，f表示朋友的数量，总人数是：f+1 
double R[N];//半径 
//求的是，每个人能得到的最大的蛋糕的体积，那么就二分蛋糕的体积
//每人分得的蛋糕的体积为x
bool check(double x) {
	int cnt = 0;//通过比较当前状态下的人数和f+1的相对大小。 
	for (int i = 1; i <= n; ++i)
        cnt += (int)(R[i] / x * R[i]);//人数要取整，舍弃小数 
    //f+1 总人数
	return cnt >= f + 1;//如果够分则返回true，不够分返回false;
}
signed main()
{
    int t;
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &n, &f);//f是朋友的人数
        for (int i = 1; i <= n; i++)
            scanf("%lf", &R[i]);//依次输入半径
        //因为我check判断的时候是半径*半径所以，上届要取1e4*1e4 
        double l = 0, r = 1e8 + 10;
        //二分模板
        //看结果要求保留多少位小数，判断条件：一般多两位
        while (r - l > 1e-6) {
            double mid = (l + r) / 2;
            //如果够分就往右找，此时的区间是[mid, r] 
            if (check(mid)) l = mid;
            //如果不够分就往左找，此时的区间是[l, mid] 
            else r = mid;
        }
        //保留4位有效数字 
		printf("%.4lf\n", l * PI);
	}
	return 0;
}
```
