## 题目描述：
一句话：图上有 n 个点，每个点有一个字符串，如果这一个点和另一个点之间的公共字母之间存在连线，我们在这两个点之间连边，给定 q 个询问，问你 a 到 b 的最短距离

There are $n$ cities located on a straight line. The cities are numbered from $1$ to $n$.

Portals are used to move between cities. There are $4$ colors of portals: blue, green, red, and yellow. Each city has portals of two different colors. You can move from city $i$ to city $j$ if they have portals of the same color (for example, you can move between a "blue-red" city and a "blue-green" city). This movement costs $|i-j|$ coins.

Your task is to answer $q$ independent queries: calculate the minimum cost to move from city $x$ to city $y$.

**Input**

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

The first line of each test case contains two integers $n$ and $q$ ($1 \le n, q \le 2 \cdot 10^5$) — the number of cities and the number of queries, respectively.

The second line contains $n$ strings of the following types: BG, BR, BY, GR, GY, or RY; the $i$ \-th of them describes the portals located in the $i$ \-th city; the symbol B indicates that there is a blue portal in the city, G — green, R — red, and Y — yellow.

The $j$ \-th of the next $q$ lines contains two integers $x_j$ and $y_j$ ($1 \le x_j, y_j \le n$) — the description of the $j$ \-th query.

Additional constraints on the input:

-   the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$;
-   the sum of $q$ over all test cases does not exceed $2 \cdot 10^5$.

**Output**

For each query, print a single integer — the minimum cost to move from city $x$ to city $y$ (or $-1$ if it is impossible).

## 题解
本题我们可以通过简单的枚举来解决，我们发现我们的最终的**道路形态都可以分为下面的几类**：
1. 两者之间是直接连接的，我们的最短路就是两者之间的距离
2. 两者之间有一个其他颜色连接，我们的最短路就需要通过我们的一个中间的点来进行处理，这里如果我们的中间点在两者之间，那么我们和第一种情况一样，否则我们二分找到距离我们的左端点最近的点和距离右端点最近的点，两者里面去一个作为答案计算。

```
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
int INF = 0x3f3f3f3f3f3f3f3f;
using namespace std;
typedef pair<int, int> PII;

void init() {
    // 保留空的初始化函数
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<string> type_(n + 1);
    unordered_map<string, vector<int>> othertype;
    
    // 初始化map中的vector为空
    othertype["BG"] = vector<int>();
    othertype["RY"] = vector<int>();
    othertype["GR"] = vector<int>();
    othertype["BY"] = vector<int>();
    othertype["GY"] = vector<int>();
    othertype["BR"] = vector<int>();

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        type_[i] = s;

        if (s == "BG" || s == "RY") {
            for (auto& [u, v] : othertype) {
                if (u == "RY" || u == "BG") continue;
                v.push_back(i);
            }
        } else if (s == "GR" || s == "BY") {
            for (auto& [u, v] : othertype) {
                if (u == "GR" || u == "BY") continue;
                v.push_back(i);
            }
        } else if (s == "GY" || s == "BR") {
            for (auto& [u, v] : othertype) {
                if (u == "GY" || u == "BR") continue;
                v.push_back(i);
            }
        }
    }
    for(auto& [u,v]:othertype){
        sort(begin(v),end(v));
    }
    auto check = [&](int u, int v) {
        string typeu = type_[u];
        string typev = type_[v];
        if ((typeu == "BG" && typev == "RY") || 
            (typeu == "GR" && typev == "BY") || 
            (typeu == "GY" && typev == "BR")) {
            return false;
        }
        swap(typeu,typev);
        if ((typeu == "BG" && typev == "RY") || 
            (typeu == "GR" && typev == "BY") || 
            (typeu == "GY" && typev == "BR")) {
            return false;
        }
        return true;
    };

    while (q--) {
        int a, b;
        cin >> a >> b;

        if (check(a, b)) {
            cout << abs(b - a) << endl;
        } else {
            if(a>b){
                swap(a,b);
            }
            auto calc = [&](int a, int b) -> int {
                string typeu = type_[a];
                int res=INF;
                if (othertype[typeu].empty()) {
                    return -1ll;
                } else {
                    vector<int>& lst = othertype[typeu];
                    int ll=lower_bound(lst.begin(),lst.end(),a)-lst.begin();
                    if(ll<lst.size()&&ll>=0){
                        res=min(res,abs(lst[ll]-a)+abs(b-lst[ll]));
                    }
                    if(ll-1>=0&&ll-1<lst.size()){
                        res=min(res,abs(lst[ll-1]-a)+abs(b-lst[ll-1]));
                    }
                    if(ll+1<lst.size()){
                        res=min(res,abs(lst[ll+1]-a)+abs(b-lst[ll+1]));
                    }
                    int rr=lower_bound(lst.begin(),lst.end(),b)-lst.begin();
                    if(rr<lst.size()&&rr>=0){
                        res=min(res,abs(lst[rr]-a)+abs(lst[rr]-b));
                    }
                    if(rr+1<lst.size()&&rr+1>=0){
                        res=min(res,abs(lst[rr+1]-a)+abs(lst[rr+1]-b));
                    }
                    if(rr-1>=0&&rr-1<lst.size()){
//                        res=min(res,abs())
                        res=min(res,abs(lst[rr-1]-a)+abs(lst[rr-1]-b));
                    }
                    return res;
                }
            };
            int u = calc(a, b);
            cout << u << endl;
        }
    }
}

signed main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int t;
    t = 1;
    cin >> t;
    init();
    while (t--) {
        solve();
    }
}
```