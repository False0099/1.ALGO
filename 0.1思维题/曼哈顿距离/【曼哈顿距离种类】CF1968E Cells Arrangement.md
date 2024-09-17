# Cells Arrangement

## 题目描述

You are given an integer $ n $ . You choose $ n $ cells $ (x_1, y_1), (x_2, y_2),\dots, (x_n, y_n) $ in the grid $ n\times n $ where $ 1\le x_i\le n $ and $ 1\le y_i\le n $ .

Let $ \mathcal{H} $ be the set of distinct Manhattan distances between any pair of cells. Your task is to maximize the size of $ \mathcal{H} $ . Examples of sets and their construction are given in the notes.

If there exists more than one solution, you are allowed to output any.

Manhattan distance between cells $ (x_1, y_1) $ and $ (x_2, y_2) $ equals $ |x_1-x_2|+|y_1-y_2| $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1\le t\le 50 $ ) — the number of test cases.

Each of the following $ t $ lines contains a single integer $ n $ ( $ 2\le n\le 10^3 $ ).

## 输出格式

For each test case, output $ n $ points which maximize the size of $ \mathcal{H} $ . It is not necessary to output an empty line at the end of the answer for each test case.

## 样例 #1

### 样例输入 #1

```
5
2
3
4
5
6
```

### 样例输出 #1

```
1 1
1 2

2 1
2 3
3 1

1 1
1 3
4 3
4 4

1 1
1 3
1 4
2 1
5 5

1 4
1 5
1 6
5 2
5 5
6 1
```

## 提示

In the first testcase we have $ n=2 $ . One of the possible arrangements is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/75dc943a7c64415a7537c95e5a0a8ab6f7bb8c40.png) The arrangement with cells located in $ (1,1) $ and $ (1,2) $ .  In this case $ \mathcal{H}=\{|1-1|+|1-1|,|1-1|+|2-2|,|1-1|+|1-2|\}=\{0,0,1\}=\{0,1\} $ . Hence, the size of $ \mathcal{H} $ is $ 2 $ . It can be shown that it is the greatest possible answer. In the second testcase we have $ n=3 $ . The optimal arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c33264fb4d38aae733c98659eb0f28334deed2c9.png) The arrangement with cells located in $ (2,1) $ , $ (2,3) $ and $ (3,1) $ . $ \mathcal{H} $ = $ \{|2-2|+|1-1|,|2-2|+|3-3|,|3-3|+|1-1|,|2-2|+|1-3|,|2-3|+|1-1|,|2-3|+|3-1|\} $ = $ \{0,0,0,2,1,3\} $ = $ \{0,1,2,3\} $ .

For $ n=4 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c8c88e231569a366e81dbe59dfe40f3bca88662e.png)For $ n=5 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/3a3f9b43e6fc8c9643d27a1bfc597d0efe1c8425.png)For $ n=6 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/b0bf5b17a4bc6da02c3ed5a2113cf7373a9e3ccc.png)

## 题解
我们本题一眼看上去是没什么思路的，我们能发现的就是，我们的种类对于我们的 $n$ 来说，是 $2\times n+1$ 的，这个情况下，我们不妨打个表看看。

**但是，我们的打表也是存在一定的技巧的，我们不妨只看我们的第一个可行的结果，因为一般这种都是有一定规律的，**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int types=0;
const int N=20;
int g[N][N];
int n;
set<int> st;
bool check(){
	st.clear();
	vector<pair<int,int>> pairs;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(g[i][j]==1){
				pairs.push_back({i,j});
			}
		}
	}
	int m=pairs.size();
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++){
			st.insert(abs(pairs[i].first-pairs[j].first)+abs(pairs[i].second-pairs[j].second));
		}
	}
	if(st.size()==types){
		return true;
	}else{
		return false;
	}
}
void dfs(int depth,int number){
	//cout<<depth<<" "<<number<<endl;
	if(depth==(n*n)&&number!=n){
		return;
	}
	if(depth==(n*n)&&number==n){
		//cout<<1<<endl;
		if(check()){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					cout<<g[i][j]<<" ";
				}
				puts("");
			}
			exit(0);
			puts("");
			cout<<st.size()<<endl;
			puts("");
			
		}
		return;
	}
	if(number>n){
		return;
	}

		g[depth/n][depth%n]=1;
		dfs(depth+1,number+1);
		g[depth/n][depth%n]=0;
		dfs(depth+1,number);
	
}
void solve() {
	cin>>n;
	types=2*n-1;
	dfs(0,0);
}
signed main() {
	int t;
	cin>>t;
	while(t--) {
		solve();
	}
}
```

于是，我们就不难发现，我们只需要构造：
```
#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve() {

    int n;

    cin>>n;

    if(n==2){

        cout<<"1 1"<<endl;

        cout<<"1 2"<<endl;

        return;

    }

    if(n==3){

        cout<<"2 1"<<endl;

        cout<<"2 3"<<endl;

        cout<<"3 1"<<endl;

        return;

    }

    for(int i=1;i<=n-2;i++){

        cout<<1<<" "<<i<<endl;

    }

    cout<<n<<" "<<2<<endl;

    cout<<n<<" "<<n<<endl;

}

signed main() {

    int t;

    cin>>t;

    while(t--) {

        solve();

    }

}
```

即可通过本题。