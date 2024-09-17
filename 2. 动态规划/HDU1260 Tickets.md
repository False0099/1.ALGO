现在有 n 个人要买电影票，如果知道每个人单独买票花费的时间，还有和前一个人一起买花费的时间，问最少花多长时间可以全部买完票。  

Input

给出 N(1<=N<=10)，表示有N组样例  
给出K (1<=K<=2000)，表示有K个人买票..  
给出K个数表示这个人单独买票会花的时间..保证每个数 (0s<=Si<=25s)  
给出K-1个数，表示这个人和前面那个人一起买票会花的时间..保证每个数 (0s<=Si<=50s)  

Output

对于每一组数据，你需要给出电影院售票结束的时间，售票开始的时间为 08:00:00 am. 时间格式为： HH:MM:SS am|pm.  
时分秒都是两位，如果只有1位补齐前导0，HH<12输出am，大于等于12输出pm.  
eg: 12:03:00 pm 13:04:12 pm 11:09:09 am  
具体看样例输出  

Sample Input

2
2
20 25
40
1
8

Sample Output

08:00:40 am
08:00:08 am

## 题解
我们这一题因为，我们只有根前一个人捆绑两种方式，所以本题理论上是具有后效性的，但是因为我们的后效性是有限的，我们就可以通过我们设置一个状态来消除我们的“后效性”，我们以 $dp[i][0]$ 表示我们给前 i 个人买票，并且给第 i 个人单独买票，我们已 $dp[i][1]$ 表示我们给前 i 个人买票，并且给第 i 个人和后面的人一起买票的最低价格，于是我们的转移就可以有类似于状态机的转移方式：$dp[i]=dp[i-1]+a[i],dp[i-1]+d[i]$

```cpp
/*
皮卡丘冲鸭！
へ　　　　　／|
　　/＼7　　　 ∠＿/
　 /　│　　 ／　／
　│　Z ＿,＜　／　　 /`ヽ
　│　　　　　ヽ　　 /　　〉
　 Y　　　　　`　 /　　/
　ｲ●　､　●　　⊂⊃〈　　/
　()　 へ　　　　|　＼〈
　　>ｰ ､_　 ィ　 │ ／／
　 / へ　　 /　ﾉ＜| ＼＼
　 ヽ_ﾉ　　(_／　 │／／
　　7　　　　　　　|／
　　＞―r￣￣`ｰ―＿
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <cmath>
#define For(i,x,y) for(int i=(x); i<=(y); i++)
#define fori(i,x,y) for(int i=(x); i<(y); i++)
#define rep(i,y,x) for(int i=(y); i>=(x); i--)
#define mst(x,a) memset(x,a,sizeof(x))
#define pb push_back
#define sz(a) (int)a.size()
#define ALL(x) x.begin(),x.end()
#define mp make_pair
#define fi first
#define se second
#define db double
#define debug(a) cout << #a << ": " << a << endl
using namespace std;
typedef long long LL;
typedef long long ll;
typedef unsigned long long ULL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
typedef pair<int,int>pa;
typedef pair<ll,ll>pai;
typedef pair<db,db> pdd;

const int N = 2e5+10;
const int M = 1e5;
const int maxn=1e6+10;
const db eps = 1e-8;
const db pi = acos(-1.0);

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }
const char ty[2][4]={"am", "pm"};
struct Time{
    int h, m ,s;
    char cur[5];
    Time(){}
    /*
    Time(int h, int m, int s){
        this->h = h;
        this->m = m;
        this->s = s;
    }
    */
    Time(int _h, int _m, int _s):h(_h), m(_m), s(_s){}
    Time(int h, int m, int s, char type[]){
        new(this)Time(h,m,s);
        direct();
        if(this->h >= 12) memcpy(this->cur,ty[1],sizeof(cur));
        else memcpy(this->cur, ty[0],sizeof(cur));//cur = "AM";
    }
    void print(){
        printf("%02d:%02d:%02d %s", h, m, s, cur);
    }
    Time operator +(const Time &b){
        /*
        Time c;
        int h = this->h + b.h;
        int m = this->m + b.m;
        int s = this->s + b.s;
        //direct();
        c = Time(h,m,s,"");
        */
        Time c  = Time(h + b.h, m + b.m, s + b.s, "");
        return c;
    }
    void direct(){
        if(s>60)m+=s/60, s = s%60;
        if(m>60)h+=m/60, m = m%60;
        if(h>=24)h%=24;
    }
} t8;
int dp[3000];
int s[3000], d[3000];
void sol(){
    int n;
    scanf("%d", &n);
    For(i,1,n)scanf("%d", s+i);
    For(i,2,n) scanf("%d", d+i);
    dp[1] = s[1];
    For(i,2,n){
        dp[i] = min(dp[i-1]+s[i],dp[i-2]+d[i]);
    }
    int h = 0, m =0  ,s = 0;
    s = dp[n]%60; m += dp[n]/60;
    h += m/60, m = m%60;
    Time add = Time(h,m,s,"");
    Time now = add+t8;
    now.print();
    puts("");
}
int main()
{
    t8 = Time(8,0,0,"");
    //ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
/*
    Time t1 = Time(8,0,0,"");
    Time t2 = Time(12,0,0,"");
    t2.print();
    puts("");
    Time t3 = t2 + t1;
   // debug(t1.h);
    t1.print();
    puts("");
    t2.print();
    t3.print();
*/
    int tt;
    scanf("%d", &tt);
    while(tt--){
        sol();
    }
    return 0;
}

```