**题目背景**

> 我会带你到月球去，我答应你。

**题意简述**

  
给出一棵以 1 为根的有根树，一开始每个节点都是白色的。David 和 Adam 在树上博弈，David 先手，每次每个人需要选择树上一个白色的点，并把这个点以及其到根路径上的所有点染成黑色。无法操作的人输。  
  
假定两人均绝顶聪明，你需要求出谁会获胜。

第一行输入一个整数 $n$ ，表示树的点数。  
  
接下来一行 $n-1$ 个数 $p_2,p_3,\cdots,p_n$，其中 $p_i$ 表示点 $i$ 在树上的父亲。

一行输出一个字符串 David 或 Adam，表示获胜的人。

## 题解
我们本题只需要做一个简单的证明：我们的只要是先选，我们一定是能赢的，这一点虽然我不知道怎么证，但结果一定是这样没错的。

```cpp
#include<string>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<stack>
#include<deque> 
#include<cstring>
#include<vector>
#include<map>
using namespace std;
#define ll long long
#define inf 2000000009
#define debugging 0
const int maxn = 300010;
const int mod = 1e9+7;

int n, x;
int a[maxn];

void solve() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d", &x);
    }
    printf("David\n");
} 
void debug() {

}
int main() {
    int t = 1, cas = 1;
//  scanf("%d", &t);
    while (t--) {
//      debug();
        if(debugging) printf("case :%d\n", cas++); // debug
        solve();
    }
}
/*

*/
```