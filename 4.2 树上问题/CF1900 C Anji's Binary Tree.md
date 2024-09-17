Keksic keeps getting left on seen by Anji. Through a mutual friend, he's figured out that Anji really likes binary trees and decided to solve her problem in order to get her attention.

Anji has given Keksic a binary tree with $n$ vertices. Vertex $1$ is the root and does not have a parent. All other vertices have exactly one parent. Each vertex can have up to $2$ children, a left child, and a right child. For each vertex, Anji tells Keksic index of both its left and its right child or tells him that they do not exist.

Additionally, each of the vertices has a letter $s_i$ on it, which is either 'U', 'L' or 'R'.

Keksic begins his journey on the root, and in each move he does the following:

-   If the letter on his current vertex is 'U', he moves to its parent. If it doesn't exist, he does nothing.
-   If the letter on his current vertex is 'L', he moves to its left child. If it doesn't exist, he does nothing.
-   If the letter on his current vertex is 'R', he moves to its right child. If it doesn't exist, he does nothing.

Before his journey, he can perform the following operations: choose any node, and replace the letter written on it with another one.

You are interested in the minimal number of operations he needs to do before his journey, such that when he starts his journey, he will reach a leaf at some point. A leaf is a vertex that has no children. It does not matter which leaf he reaches. Note that it does not matter whether he will stay in the leaf, he just needs to move to it. Additionally, note that it does not matter how many times he needs to move before reaching a leaf.

Help Keksic solve Anji's tree so that he can win her heart, and make her come to Čačak. 

## 题解
我们这一题起始能够想到就是通过我们的一遍走一遍改的想法，通过两次遍历我们的数组，来最后求得我们的答案，注意，如果我们的某个点是我们的 $p$,那么我们无论如何都要把这个点删除了

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<array>
using namespace std;
using LL = long long;

int main(){

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--){
        int n;
        string s;
        cin >> n >> s;
        s = " " + s;
        vector<array<int, 2> > tr(n + 1); 
        for(int i = 1; i <= n; i++){
            cin >> tr[i][0] >> tr[i][1];
        }

        int ans = 1e9;
        int cnt = 0;

        auto dfs = [&](auto &&dfs, int u) -> void {
            if (tr[u] == array{0, 0}){
                ans = min(ans, cnt);
                return;
            }
            if (tr[u][0]){
                cnt += (s[u] != 'L');
                dfs(dfs, tr[u][0]);
                cnt -= (s[u] != 'L');
            }
            if (tr[u][1]){
                cnt += (s[u] != 'R');
                dfs(dfs, tr[u][1]);
                cnt -= (s[u] != 'R');
            }
        };

        dfs(dfs, 1);

        cout << ans << '\n';
    }

}
```