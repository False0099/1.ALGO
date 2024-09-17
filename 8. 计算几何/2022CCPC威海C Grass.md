![](https://espresso.codeforces.com/df8ff72470f7cd5b934bcefb5e85d5572f3859ba.png)

Charles the Rabbit likes eating grass. As the saying goes, rabbits do not eat the grass by their burrows. Therefore, Charles has to go outside his burrow every day to look for grass to eat.

One day, Charles comes to a two-dimensional plane with many distinct points. He can choose a point $A$ and another four points $B, C, D, E$ to connect with $A$ to form four segments. We consider these four segments as a clump of grass if they meet the following condition:

-   Any two of the four segments have only a single point of intersection $A$ between them.

For example, in the picture below, $(1)$ is a clump of grass, but $(2)$ is not one as the intersection of segments $AC$ and $AE$ is not only a single point $A$.

![](https://espresso.codeforces.com/0d8ccec4b103556449f9f25e680f3bfa3899c380.png)

Given $n$ points on a plane, Charles wants to know whether there exists a clump of grass. If so, help him find a certain one.

**Input**

The first line contains an integer $T$ ($1 \le T \le 120$), indicating the number of test cases.

The first line of each test case contains an integer $n$ ($1 \le n \le 25000$), indicating the number of points.

Each of the following $n$ lines contains two integers $x,y$ ($-10^7 \le x,y \le 10^7$), indicating that the coordinates of the point are $(x,y)$. It is guaranteed that all points are distinct.

It is guaranteed that $\sum n \le 10^5$ over all test cases.

**Output**

For each test case, if there does not exist a clump of grass, output NO in a single line.

Otherwise, output YES in the first line. Then output two integers separated by a space in the second line, indicating the coordinates of point $A$. Then output two integers separated by a space in each of the third to sixth lines, indicating the coordinates of the other four points $B, C, D, E$.

If there is more than one clump of grass, output any.

## 题解
我们这一题，我们不难发现，我们可以通过先枚举我们的一个点，然后判断以这个点为中心，我们的不同的极角数是不是有大于 4 个，如果有，我们就可以以这个点为中心，否则，我们就认为这个点不行，我们就要换一个方案。
```cpp
#include <bits/stdc++.h>
#define ll int
#define ld long double
using namespace std;

const int maxn = 25000;
int n;
struct point
{
    int x,y;
}P[maxn];
void solve()
{
    
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x,y; 
		cin>>x>>y;
        P[i]={x,y};
    }
    for(int i=1;i<=n;i++)
    {
    	set<pair<int,int>> st;
    	int cnt=0;
    	vector<point> ans;
    	ans.push_back(P[i]);
    	bool negcol=false;
    	bool col=false;
    	bool negrow=false;
    	bool row=false;
        for(int j=1;j<=n;j++) 
	     	if(i!=j){
	     		int dx=P[j].x-P[i].x;
	     		int dy=P[j].y-P[i].y;
	     		if(dx==0){
	     			if(dy>0&&!row){
	     				row=true;
						 cnt++;
						 ans.push_back(P[j]); 
						 if(cnt>=4){
							cout<<"YES"<<endl;
							for(auto u:ans){
								cout<<u.x<<" "<<u.y<<endl;
							}
							return;
						}
					 }
					 if(dy<0&&!negrow){
					 	negrow=true;
					 	cnt++;
					 	ans.push_back(P[j]);
					 	if(cnt>=4){
							cout<<"YES"<<endl;
							for(auto u:ans){
								cout<<u.x<<" "<<u.y<<endl;
							}
							return;
						}
					 }
					 continue;
				}
				if(dy==0){
					if(dx>0&&!col){
						col=true;
						cnt++;
						ans.push_back(P[j]);
						if(cnt>=4){
							cout<<"YES"<<endl;
							for(auto u:ans){
								cout<<u.x<<" "<<u.y<<endl;
							}
							return;
						}
					}
					if(dx<0&&!negcol){
						negcol=true;
						cnt++;
						ans.push_back(P[j]);
						if(cnt>=4){
							cout<<"YES"<<endl;
							for(auto u:ans){
								cout<<u.x<<" "<<u.y<<endl;
							}
							return;
						}
					}
					continue;
				}
				int dd=__gcd(abs(dx),abs(dy));
	     		dx/=dd;
	     		dy/=dd;
	     		pair<int,int> tmp={dx,dy};
	     		if(st.count(tmp)){
	     			continue;
				}else{
					ans.push_back(P[j]);
					st.insert(tmp);
					cnt++;
					if(cnt>=4){
						cout<<"YES"<<endl;
						for(auto u:ans){
							cout<<u.x<<" "<<u.y<<endl;
						}
						return;
					}
				}    
				
     		
        }
    }
    printf("NO\n");

    return ;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```
但是上面的方式会超时，`TLE on 6`,所以我们考虑换一种方法。

我们考虑到有下面的结论：我们如果满足条件，那么我们要满足五点不全共线即可，于是我们就可以先枚举我们的四个点，然后看有没有和这四个点不共线的，最后我们就能得到我们的结论。
```text
#include<bits/stdc++.h>
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define pii pair<int,int>
#define x first
#define y second
using namespace std;
const int N = 1e5+10;
pii a[N];
int t,n;
int check(int x){
    set<pii>se;
    rep(i,1,4){
        int dx = a[i].x-a[x].x, dy = a[i].y-a[x].y;
        int dd = __gcd(dx, dy);
        dx /= dd;  dy /= dd;
        se.insert({dx, dy});
    }
    return se.size()>1; 
}
int find(){
    rep(i,1,5)
    {
        set<pii>se;
        rep(j,1,5){
            if(i==j)continue;
            int dx = a[i].x-a[j].x, dy = a[i].y-a[j].y;
            int dd = abs(__gcd(dx, dy));
            dx /= dd;  dy /= dd;
            se.insert({dx, dy});
        }
        if(se.size()==4)return i;
    }
}

main()
{
    cin.tie(0)->ios::sync_with_stdio(0);
    for(cin >> t;t--;)
    {
        cin>>n;
        rep(i,1,n) cin>>a[i].x>>a[i].y;
        int ok = 0;
        rep(i,5,n)
        {
            if(check(i)){
                swap(a[i], a[5]);
                int x = find();
                cout<<"YES\n";
                cout<<a[x].x<<" "<<a[x].y<<"\n";
                for(int i = 1; i <= 5; i++){
                    if(i!=x)cout<<a[i].x<<" "<<a[i].y<<"\n";
                }
                ok = 1;
                break;
            }
        }
        if(ok==0)cout<<"NO\n";
    }
}
```