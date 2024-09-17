# Distance Learning Courses in MAC

## 题目描述

The New Year has arrived in the Master's Assistance Center, which means it's time to introduce a new feature!

Now students are given distance learning courses, with a total of $ n $ courses available. For the $ i $ -th distance learning course, a student can receive a grade ranging from $ x_i $ to $ y_i $ .

However, not all courses may be available to each student. Specifically, the $ j $ -th student is only given courses with numbers from $ l_j $ to $ r_j $ , meaning the distance learning courses with numbers $ l_j, l_j + 1, \ldots, r_j $ .

The creators of the distance learning courses have decided to determine the final grade in a special way. Let the $ j $ -th student receive grades $ c_{l_j}, c_{l_j + 1}, \ldots, c_{r_j} $ for their distance learning courses. Then their final grade will be equal to $ c_{l_j} $ $ | $ $ c_{l_j + 1} $ $ | $ $ \ldots $ $ | $ $ c_{r_j} $ , where $ | $ denotes the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) operation.

Since the chatbot for solving distance learning courses is broken, the students have asked for your help. For each of the $ q $ students, tell them the maximum final grade they can achieve.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of distance learning courses.

Each of the following $ n $ lines contains two integers $ x_i $ and $ y_i $ ( $ 0 \le x_i \le y_i < 2^{30} $ ) — the minimum and maximum grade that can be received for the $ i $ -th course.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2\cdot 10^5 $ ) — the number of students.

Each of the following $ q $ lines contains two integers $ l_j $ and $ r_j $ ( $ 1 \le l_j \le r_j \le n $ ) — the minimum and maximum course numbers accessible to the $ j $ -th student.

It is guaranteed that the sum of $ n $ over all test cases and the sum of $ q $ over all test cases do not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output $ q $ integers, where the $ j $ -th integer is the maximum final grade that the $ j $ -th student can achieve.

## 样例 #1

### 样例输入 #1

```
3
2
0 1
3 4
3
1 1
1 2
2 2
4
1 7
1 7
3 10
2 2
5
1 3
3 4
2 3
1 4
1 2
6
1 2
2 2
0 1
1 1
3 3
0 0
4
3 4
5 5
2 5
1 2
```

### 样例输出 #1

```
1 5 4 
15 11 15 15 7 
1 3 3 3
```

## 提示

In the first test case:

1. The maximum grade for the first student is $ 1 $ : 
  - On the first distance learning course, he will receive a grade of $ 1 $ .
  
   Therefore, the final grade is $ 1 $ .
2. The maximum grade for the second student is $ 5 $ : 
  - On the first distance learning course, he will receive a grade of $ 1 $ .
  - On the second distance learning course, he will receive a grade of $ 4 $ .
  
   Therefore, the final grade is $ 1 $ $ | $ $ 4 $ $ = $ $ 5 $ .
3. The maximum grade for the third student is $ 4 $ : 
  - On the second distance learning course, he will receive a grade of $ 4 $ .
  
   Therefore, the final grade is $ 4 $ .

In the second test case:

1. The maximum grade for the first student is $ 15 $ : 
  - On the first distance learning course, he will receive a grade of $ 7 $ .
  - On the second distance learning course, he will receive a grade of $ 4 $ .
  - On the third distance learning course, he will receive a grade of $ 8 $ .
  
   Therefore, the final grade is $ 7 $ $ | $ $ 4 $ $ | $ $ 8 $ $ = $ $ 15 $ .
2. The maximum grade for the second student is $ 11 $ : 
  - On the third distance learning course, he will receive a grade of $ 9 $ .
  - On the fourth distance learning course, he will receive a grade of $ 2 $ .
  
   Therefore, the final grade is $ 9 $ $ | $ $ 2 $ $ = $ $ 11 $ .
## 题解
我们本题要求我们的或运算最大，而且给定了我们一个取值范围，要求我们在这一个范围内找到满足条件的个数。考虑到 [[【或运算】牛客寒假集训营1 H 01背包但是bit]]，当中的思想：把我们的一个数用 lowbit 处理后减 1 就能得到除了这位以外全是 1 的方案数。

如果没有我们的左端点限制，我们就很简单的处理就完事儿了，but，因为我们这一题有我们的左端点限制。所以我们还需要让我们建完之后的数在我们的左端点之后。

综上，我们可以先对每一个区间预处理出一个数组，数组中表示这个区间能够构成的所有最大区间有哪些。
```cpp
vector<int> deal(int l,int r){
	vector<int> tmp;
	tmp.clear();
	tmp.push_back(r);
	while(r-1<=l){
		int dividenum=lowbit(r);
		tmp.push_back(r-1);
		r-=dividenum;
	}
	return tmp;
}
```

之后，我们考虑求出一段区间内能够构成的区间，我们可以考虑用我们的线段树来模拟我们的合并操作。考虑知道了一个区间内的预处理值，怎么去计算合并后的值。

首先，因为我们本题中我们的数字都比较小，不会超过 $2^{32}$,所以我们每一个 tmp 数组中的值是不会超过 $23$ 的，因此，我们暴力合并两个集合的时间复杂度，大约在 $23*23$,而我们最多只会合并 $logn$ 次，因此我们完全可以考虑暴力合并。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 200010;

int n, p, m;
pair<int,int> w[N];
struct Node
{
    int l, r;
    vector<int> possible_count;
}tr[557654];

Node pushup(Node u,Node v){
	vector<int> left=u.possible_count;
	vector<int> right=v.possible_count;
	Node w;
	w.l=u.l;
	w.r=v.r;
	w.possible_count.clear();
	for(int i=0;i<left.size();i++){
		for(int j=0;j<right.size();j++){
			w.possible_count.push_back((left[i]|right[j]));
		}
	}
	sort(w.possible_count.begin(),w.possible_count.end());
	w.possible_count.erase(unique(w.possible_count.begin(),w.possible_count.end()),w.possible_count.end());
	
	return w;
}
int lowbit(int x){
	return x&(-x);
}
vector<int> deal(int l,int r){
	vector<int> tmp;
	tmp.clear();
	tmp.push_back(r);
//	cout<<"l="<<l<<"r="<<r<<endl;
	while(r-1>=l){
		int dividenum=lowbit(r);
		tmp.push_back(r-1);
		r-=dividenum;
	}
//	cout<<"debuging deal"<<endl;
	
//	for(auto u:tmp){
//		cout<<u<<endl;
//	}
//	cout<<"debuging deal"<<endl;
	return tmp;
}
void build(int u, int l, int r)
{
    if (l == r) tr[u] = {l, r, deal(w[l].first,w[l].second)};
    else
    {
        //tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        tr[u]=pushup(tr[u<<1],tr[u<<1|1]);
    }
}
Node query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];

    int mid = tr[u].l + tr[u].r >> 1;
    Node sum;
    sum.possible_count.clear();
    sum.possible_count.push_back(0);
    if (l <= mid) sum = query(u << 1, l, r);
    if (r > mid) sum =pushup(sum,query(u<<1|1,l,r));
    return sum;
}

void solve()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>w[i].first>>w[i].second;
	}
	build(1,1,n);
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		vector<int> tmo=query(1,l,r).possible_count;
		//puts("debugging wmo");
		int ans=-1;
		for(auto u:tmo){
			ans=max(ans,u);
		}	
		//puts("debugging wmo");
		
		cout<<ans<<" ";
	}
	puts("");
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```

结果自然是喜闻乐见的 MLE 了，考虑剪枝优化，

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 200010;

int n, p, m;
pair<int,int> w[N];
struct Node
{
    int l, r;
    vector<int> possible_count;
}tr[N>>2];

Node pushup(Node u,Node v){
	vector<int> left=u.possible_count;
	vector<int> right=v.possible_count;
	Node w;
	w.l=u.l;
	w.r=v.r;
	w.possible_count.clear();
	for(int i=0;i<left.size();i++){
		for(int j=0;j<right.size();j++){
			w.possible_count.push_back((left[i]|right[j]));
		}
	}
	sort(w.possible_count.begin(),w.possible_count.end());
	w.possible_count.erase(unique(w.possible_count.begin(),w.possible_count.end()),w.possible_count.end());
	
	return w;
}
int lowbit(int x){
	return x&(-x);
}
vector<int> deal(int l,int r){
	vector<int> tmp;
	tmp.clear();
	tmp.push_back(r);
//	cout<<"l="<<l<<"r="<<r<<endl;
	while(r-1>=l){
		int dividenum=lowbit(r);
		tmp.push_back(r-1);
		r-=dividenum;
	}
//	cout<<"debuging deal"<<endl;
	
//	for(auto u:tmp){
//		cout<<u<<endl;
//	}
//	cout<<"debuging deal"<<endl;
	return tmp;
}
void build(int u, int l, int r)
{
    if (l == r) tr[u] = {l, r, deal(w[l].first,w[l].second)};
    else
    {
        //tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        tr[u]=pushup(tr[u<<1],tr[u<<1|1]);
    }
}
Node query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];

    int mid = tr[u].l + tr[u].r >> 1;
    Node sum;
    sum.possible_count.clear();
    sum.possible_count.push_back(0);
    if (l <= mid) sum = query(u << 1, l, r);
    if (r > mid) sum =pushup(sum,query(u<<1|1,l,r));
    return sum;
}

void solve()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>w[i].first>>w[i].second;
	}
	build(1,1,n);
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		vector<int> tmo=query(1,l,r).possible_count;
		//puts("debugging wmo");
		int ans=-1;
		for(auto u:tmo){
			ans=max(ans,u);
		}	
		//puts("debugging wmo");
		
		cout<<ans<<" ";
	}
	puts("");
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
```