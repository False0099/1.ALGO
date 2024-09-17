# 
## 题目描述
给你几个短字符串，一个长字符串，看有几个短字符串是能在长字符串里找到的。
## 输入格式
第一行给一个整数，表示有几个案例。  
每个案例先给出1个整数，表示有几个短字符串。  
在每个案例的最后再给出长字符。


## 输出格式
每个案例输出一行整数，表示短字符串里有几个能在长字符里找到。


## 样例 #1

### 样例输入 #1

```
1  
5  
book  
kkee  
ok  
kept  
keep  
bookkeeper
```

### 样例输出 #1

```
4
```

## 题解
这是一道AC自动机的标准模版题，我们抄一下就行

## 代码
```cpp
```cpp
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
const int maxN = 5e5 + 1; // 模式串长度 * 模式串数量
const int maxM = 1e6 + 1; // 目标串长度
const int chSize = 26; // 字符集大小

class AcAutomaton {
public:
    int trie[maxN][chSize];
    int vis[maxN], fail[maxN];
    int tot;
    // 初始化
    void init()
    {
        memset(vis, 0, sizeof vis);
        memset(trie, 0, sizeof trie);
        tot = 0;
    }
    // 插入
    void insert(char* str)
    {
        int len = strlen(str);
        int pos = 0;
        for (int i = 0; i < len; i++) {
            int c = str[i] - 'a';
            if (!trie[pos][c])
                trie[pos][c] = ++tot;
            pos = trie[pos][c];
        }
        vis[pos]++;
    }
    // DFS获取Fail数组
    void build()
    {
        queue<int> q;
        // 根结点下的元素入队
        for (int i = 0; i < chSize; i++) {
            if (trie[0][i]) {
                fail[trie[0][i]] = 0;
                q.push(trie[0][i]);
            }
        }
        // DFS
        while (!q.empty()) {
            // 获取队首元素
            int pos = q.front();
            // 输出队首元素
            // cout << "front: " << pos << endl;
            // 队首出队
            q.pop();
            // 遍历队首元素的子节点
            for (int i = 0; i < chSize; i++) {
                // 若元素ch存在
                if (trie[pos][i]) {
                    // 将fail数组的值置为fail[队首元素]的下一个ch对应的值
                    fail[trie[pos][i]] = trie[fail[pos]][i];
                    // 输出构建fail数组的过程
                    // cout << "True char: " << (char)('a' + i) << " fail: " << trie[fail[pos]][i] << endl;
                    // 元素入队
                    q.push(trie[pos][i]);
                } else {
                    // 若不存在，将trie的值置为fail[队首元素]的下一个ch对应的值
                    // 方便下次计算
                    trie[pos][i] = trie[fail[pos]][i];
                }
            }
        }
    }
    // 查询
    int query(char* str)
    {
        int len = strlen(str);
        int pos = 0, ans = 0;
        for (int i = 0; i < len; i++) {
            int c = str[i] - 'a';
            pos = trie[pos][c];
            for (int j = pos; j && vis[j] != -1; j = fail[j]) {
                ans += vis[j];
                vis[j] = -1;
            }
        }
        return ans;
    }
};

AcAutomaton ac;

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        ac.init();
        char str[maxM];
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            ac.insert(str);
        }
        ac.build();
        scanf("%s", str);
        printf("%d\n", ac.query(str));
    }
}
```
```