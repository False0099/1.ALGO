Iris 有 $n$ 个喜欢玩鹅鸭杀的朋友，编号为 $1∼n$。假期的时候，大家经常会在群里问有没有人玩鹅鸭杀，并且报出现在已经参与的人数。但是每个人对于当前是否加入游戏都有自己的想法。具体的来说，对于第 i 个人，如果当前已经加入游戏的人数处于区间 $[li , ri ]$ 之间，那 ta 就会愿意加入游戏。你认为参与游戏的人越多，游戏将会越有趣，所以你决定给大家安排一个加入顺序，使得加入游戏的人数最多。

**Input** 
第一行，一个整数 n (1 ≤ n ≤ 106 )，表示总人数。接下来 i 行，每行为两个由空格分隔的整数 li , ri (0 ≤ li , ri ≤ 106 )，含义见题目描述。

**Output**
第一行一个非负整数 m，表示最多能有多少个人加入游戏。接下来一行 m 个整数，由空格分隔，第 i 个数为 pi，表示 i 个加入游戏的人。若有多种加入游戏的方案，你可以输出任意一种。

## 题解
本题我们可以按照我们的下面的丝路来进行贪心：
我们首先计算我们在当前人数下，有哪些人是满足我们的左端点条件的，并且把**不满足右端点条件的人删除掉**我们聚集到一个集合当中，然后，我们再在这一个集合当中，找到我们的**右端点最小的点**，选中这一个点，并且把这一个点的对应的元素添加到我们的备选人当中。**注意顺序，我们需要先添加，再去删除，否则也是 wa 的命**。

综上，我们可以写出我们的代码如下：
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
typedef pair<int,int> PII;
struct node{
	int l;
	int r;
	int id;
	bool operator <(node a){
		return r<a.r;
	} 
}Line[N];
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n;
	cin>>n;
	//priority_queue<node> heap;
	for(int i=0;i<n;i++){
		int l,r;
		cin>>l>>r;
		if(l>r){
			swap(l,r); 
		}
		Line[i].l=l;
		Line[i].r=r;
		Line[i].id=i;
	//	heap.push({l,r,i});
	}
	sort(Line,Line+n,[&](node a,node b){
		return a.l<b.l;
	});
	priority_queue<PII,vector<PII>,greater<PII>>heap;
	int cnt=0;
	vector<int> ans;
	int i=0;
	while(1){
		while(i<n&&Line[i].l<=cnt){
			heap.push({Line[i].r,Line[i].id});
			i++;
		}	
		while(heap.size()&&heap.top().first<cnt){
			heap.pop();
		}
		if(heap.size()==0){
			break;
		}else{
			ans.push_back(heap.top().second);
			heap.pop();
			cnt++;
		}
	}
	cout<<ans.size()<<endl;
	for(auto u:ans){
		cout<<u+1<<" ";
	}
	puts("");
} 
```

