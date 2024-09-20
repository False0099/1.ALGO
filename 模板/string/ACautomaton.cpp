#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct AhoCorasick
{
    static constexpr int ALPHABET = 26;
    struct Node
    {
        int len;
        int link;
        std::array<int, ALPHABET> next;
        Node() : link{}, next{} {}
    };

    std::vector<Node> t;

    AhoCorasick()
    {
        init();
    }

    void init()
    {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int add(const std::vector<int> &a)
    {
        int p = 1;
        for (auto x : a)
        {
            if (t[p].next[x] == 0)
            {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }

    int add(const std::string &a, char offset = 'a')
    {
        std::vector<int> b(a.size());
        for (int i = 0; i < a.size(); i++)
        {
            b[i] = a[i] - offset;
        }
        return add(b);
    }

    void work()
    {
        std::queue<int> q;
        q.push(1);

        while (!q.empty())
        {
            int x = q.front();
            q.pop();

            for (int i = 0; i < ALPHABET; i++)
            {
                if (t[x].next[i] == 0)
                {
                    t[x].next[i] = t[t[x].link].next[i];
                }
                else
                {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }

    int next(int p, int x)
    {
        return t[p].next[x];
    }

    int next(int p, char c, char offset = 'a')
    {
        return next(p, c - 'a');
    }

    int link(int p)
    {
        return t[p].link;
    }

    int len(int p)
    {
        return t[p].len;
    }

    int size()
    {
        return t.size();
    }
};


// Trie+Kmp，多模式串匹配
struct ACAutomaton {
    static constexpr int N = 1e6 + 10;
    int ch[N][26], fail[N], cntNodes;
    int cnt[N];
    ACAutomaton() {
        cntNodes = 1;
    }
    void insert(string s) {
        int u = 1;
        for (auto c : s) {
            int &v = ch[u][c - 'a'];
            if (!v) v = ++cntNodes;
            u = v;
        }
        cnt[u]++;
    }
    void build() {
        fill(ch[0], ch[0] + 26, 1);
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                int &v = ch[u][i];
                if (!v)
                    v = ch[fail[u]][i];
                else {
                    fail[v] = ch[fail[u]][i];
                    q.push(v);
                }
            }
        }
    }
    ll query(string t) {
        ll ans = 0;
        int u = 1;
        for (auto c : t) {
            u = ch[u][c - 'a'];
            for (int v = u; v && ~cnt[v]; v = fail[v]) {
                ans += cnt[v];
                cnt[v] = -1;
            }
        }
        return ans;
    }
};