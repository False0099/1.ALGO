#include<bits/stdc++.h> 
using namespace std;
//1堆n个石子每次最多取m个、最少取1个
struct Bash{
    int n,k;
    Bash(int n,int k):n(n),k(k){}
    bool work(){
        return n%(k+1);//true 为先手赢
    }
};

//有两堆各若干个物品，两个人轮流从任一堆取至少一个或同时从两堆中取同样多的物品，规定每次至少取一个，多者不限，最后取光者得胜
struct Wythoff{
    int a,b,diff;
    double p=(sqrt((double)5)+1)/double(2);
    Wythoff(int a,int b):a(a),b(b),diff(abs(a-b)){}
    bool work(){
        int r=a<b?a:b;
        if(r==(int)(p*diff)){
            return false;
        }
        return true;
    }
};

//有n堆石子，每堆石子的数量是a1,a2,a3……，二个人依次从这些石子堆中的一个拿取任意的石子，至少一个，最后一个拿光石子的人胜利
struct Nim{
    #define MAXN 50010
    int cnt,s,n;
    int a[MAXN];
    int ans[MAXN][2];
    Nim(int n):n(n){}
    void input(){
        for(int i=0;i<n;i++){
            cin>>a[i];
            s^=a[i];
        }
    }
    bool work(){
        for(int i=0;i<n;i++){
            if(a[i] > (s^a[i])){
                ans[cnt][0] = a[i];
                ans[cnt][1] = s^a[i];
                cnt++;
            }
        }
        return cnt;//先手赢为true
    }
    //输出若先手为胜的走法
    void getWays(){
        for(int i=0;i<cnt;i++){
            cout<<ans[i][0]<<" "<<ans[i][1]<<"\n";
        }
    }
    //使先手为胜的方案的数目 
    int WinCount(){
        return cnt;
    }
    #undef MAXN
};