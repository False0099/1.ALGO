Terrorists are around everywhere, they always make troubles by detonating bombs. The terrorist have some gunpowder to make bombs, different gunpowder has different damage, every kind of gunpowder can use any times, and the power of one bomb is the product of the gunpowder it consists of. Let’s see how they make a bomb.  
　　At the beginning they decide to use X parts of gunpowder to make a bomb, and then choose X parts of gunpowder, every time the damage of the gunpowder they choose can’t be smaller than the last time they choose excepting the first time. After choosing X parts gunpowder terrorists get gunpowder[1], gunpowder[2] ... gunpowder[X] ( gunpowder[1] <= gunpowder[2] <= ... <= gunpowder[X]), and then mix the X parts gunpowder to generate a bomb with power of the product of the damage of the gunpowder. Terrorists make bombs in some order, if they make bomb_A before bomb_B one of the following conditions should meet.  
**(1)**Terrorists use less parts gunpowder to make bomb_A than bomb_B.  
(2)**Terrorists both use X parts of gunpowders to make bomb_A and bomb_B. There exist an integer j（j <=X）,for all i < j,gunpowder_A[i] = gunpowder_B[i] and gunpowder_A[j] < gunpowder_B[j].  
　　Now, the police get the gunpowder by some way, police find that the gunpowder’s damage is in the range of A to B(A, B included), police want to know the K-th bomb with the power in the range of L to R(L, R included).

Input

　　There are multiple cases, the first line is an integer T denoting the number of the case, for each case has five integers A, B, L, R, K in a line. A, B denote the damage range of the gunpowder. L, R denote the power range of the bomb, K denotes the K-th bomb with the power in the range L to R that police want to know.  
2<=A <= B<=10^6  
1<=L<=R<=10^9  
1<=K<=10^6

Output

　　For each case output in the format in the first line “Case x: y” x is the case number start from 1, y is the power of the bomb, and the second line with the gunpowder in the order they choose. If there is no more than K bombs in the range of L to R just output one line “Case x: -1”.

Sample

|Inputcopy|Outputcopy|
|---|---|
|4<br>2 2 1 4 1<br>2 5 1 4 4<br>73 23642 12 20903 29401<br>2 50 1 1000000000 815180|Case #1: 2<br>2<br>Case #2: 4<br>2 2<br>Case #3: -1<br>Case #4: 59200<br>4 4 5 20 37|

Hint

  
In the second case we have 4 kinds of gunpowder with damage 2, 3, 4, 5.  
the first bomb is “2”with power of 2  
The second bomb is “3” with power of 3  
The third bomb is “4” with power of 4  
The fouth bomb is “5” with power of 5  
The fifth bomb is “2 2” with power of 2 * 2 = 4  
So the 4-th bomb with power in the range of 1 to 4 is “2 2”.

## 题解
给一个区间[A,B]，表示有 B - A + 1种火药，火药 i 的威力值为 i，现在要用这些火药做炸弹，每次先按原料个数再按原料的字典序做炸弹。每个炸弹的威力值是每种原料威力值的乘积。现在给一个区间[L,R]表示炸弹的威力值范围，求第 K 个炸弹的组成。

搜到 X 层原料的时候  
          假设剩下的全部用威力最大的B种原料  
                    我们可以得到，当前层使用原料的威力上界。  
                          (超过上界的原料最终配成的炸弹会超过威力上限）  
          同理，假设剩下的全部用威力最小的A种原料  
                    我们可以得到，当前层使用原料的威力下界。  
                          (超过上界的原料最终配成的炸弹会超过威力下限）  
          搜索的同时记录当前用了那种原料并比较有效节点数是否已达到K即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int LIM=1e9;
const int INF=0x3f3f3f3f;
int bob[40],ansdepth,k;
int pow(int a,int b){
    long long ans=1;
    for(int i=1;i<=b;i++){
        ans*=a;
        if(ans>=LIM||ans<0) return INF;
    }
    return ans;
}
void get_num(int tot,int depth,int a,int b,int l,int r){
    int down=ceil(((double)l)/pow(b,tot-depth));
    down=max(a,down);
    int up=r/pow(a,tot-depth);
    up=min(b,up);
    if(down>up) return;
    int cnt=up-down+1;
    if(depth==tot){
        if(k<=cnt){
            bob[depth]=down+k-1;
            ansdepth=depth;
            return ;
        }
        k-=cnt;
    }else{
        for(int i=down;i<=up&&ansdepth==-1;i++){
            bob[depth]=i;
            int newl=ceil(((double)l)/i);
            int newr=r/i;
            if(newl<=newr) get_num(tot,depth+1,i,b,newl,newr);
        }
    }
    return ;
}
void solve(){
    int a,b,l,r;
    scanf("%d%d%d%d%d",&a,&b,&l,&r,&k);
    ansdepth=-1;
    for(int tot=1;tot<=30;tot++){
        get_num(tot,1,a,b,l,r);
        if(ansdepth!=-1) break;
    }
    return ;
}
int main(){
    int T;
    scanf("%d",&T);
    for(int Case=1;Case<=T;Case++){
        solve();
        printf("Case #%d: ",Case);
        if(ansdepth==-1){puts("-1");continue;}
        int tot=1;
        for(int i=1;i<=ansdepth;i++)
            tot*=bob[i];
        printf("%d\n",tot);
        for(int i=1;i<=ansdepth;i++){
            printf("%d",bob[i]);
            if(i==ansdepth) puts("");
            else printf(" ");
        }
    }
    return 0;
}
```