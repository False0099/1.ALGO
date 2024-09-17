Education experts are going to rate $n$ contests due to whatever reasons. The experts have already decided on the rating of each contest, where the $i$ \-th contest is rated as a $s_i$ \-star contest.

It is said that each contest is rated according to $m$ properties, where the $j$ \-th property of the $i$ \-th contest is indicated as $p_{i, j}$, whose value ranges from $0$ to $k$ (both inclusive). The score of a contest is calculated as the sum of all its $m$ properties. That is, let $v_i$ be the score of the $i$ \-th contest, we have $v_i = \sum\limits_{j=1}^m p_{i, j}$.

It would be natural for a contest with more stars to have a higher score. The experts require that, for any two contests $1 \le i, j \le n$, if $s_i\gt s_j$, then there must be $v_i \gt v_j$. Unfortunately, the experts forgot to collect values for some (or even all) properties of some contests. As the assistant of the experts, you're required to fill in the missing values so that the constraint stated above holds for any two contests.

## 题解
我们本题可以通过我们的简单的贪心来考虑，我们首先按照我们的最终星际来从大到小的排序，对于每一个星际，我们**既要满足我们的要求，又要我们的值尽可能的大**，所以我们对于每一个位置，最后的答案就是 $min(last,r[i])$,其中我们的 $last$ 表示我们的上一个位置限制下我们可以取到的最大数值。

**对于星级相同的情况**，我们只需要保证我们的**last**是上一个星际而不是上一个位置，即可完成我们的目标。综上所述，我们可以写出我们的石山：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+10;
struct node{
	int l;
	int r;
	int id;
	int rank;
	int final_number;
}Line[N];
void solve(){
	int n,m,k;
	cin>>n>>m>>k;
	vector<vector<int>> grade(n,vector<int>(m));
	for(int i=0;i<n;i++){
		int si;
		cin>>si;
		int sured=0;
		int cnt=0;
		Line[i].l=0;
		Line[i].r=0;
		Line[i].final_number=0;
		for(int j=0;j<m;j++){
			int p;
			cin>>p;
			grade[i][j]=p;
			if(p==-1){
				Line[i].r+=k;
			}else{
				Line[i].l+=p;
				Line[i].r+=p;
			}
		}
		Line[i].id=i;
		Line[i].rank=si;
	}	
	sort(Line,Line+n,[&](node a,node b){
		return a.rank>b.rank;
	});
	int r_of_last_rank=0x3f3f3f3f3f3f3f3f;
	int r_of_rank=0x3f3f3f3f3f3f3f3f;
	for(int i=0;i<n;i++){
		if(i==0){
			Line[i].final_number=Line[i].r;
			r_of_rank=Line[i].final_number-1;
		}else{
			if(Line[i].rank==Line[i-1].rank){
				if(Line[i].l>r_of_last_rank){
					cout<<"No"<<endl;
					return;
				}else{
					Line[i].final_number=min(Line[i].r,r_of_last_rank);
					r_of_rank=min(r_of_rank,Line[i].final_number-1);
				}
			}else{
				r_of_last_rank=r_of_rank;
				if(Line[i].l>r_of_last_rank){
					cout<<"No"<<endl;
					return;
				}else{
					Line[i].final_number=min(Line[i].r,r_of_last_rank);
					r_of_rank=min(r_of_rank,Line[i].final_number-1);
				}
			}
		}
	}
	//puts("");
	//puts("");
	//puts(""); 
	for(int i=0;i<n;i++){
		int target_number=Line[i].final_number;
		int id=Line[i].id;
		int start_number=Line[i].l;
		for(int j=0;j<m;j++){
			if(grade[id][j]==-1&&target_number-start_number>=k){
				start_number+=k;
				grade[id][j]=k;
			}else if(grade[id][j]==-1&&target_number-start_number<k){
				grade[id][j]=target_number-start_number;
				start_number=target_number;
			}
		}
	}
	cout<<"Yes"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<grade[i][j]<<" ";
		}
		puts("");
	}
	puts("");
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```