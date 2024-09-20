#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct Fenwick2D {
    int n, m;
    vector<vector<T>> w;
    
    Fenwick2D(int n, int m) : n(n), m(m) {
        w.resize(n + 1, vector<T>(m + 1));
    }
    void add(int x, int y, T k) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                w[i][j] += k;
            }
        }
    }
    void add(int x, int y, int X, int Y, T k) { // 区块修改：二维差分
        X++, Y++;
        add(x, y, k), add(X, y, -k);
        add(X, Y, k), add(x, Y, -k);
    }
    T ask(int x, int y) { // 单点查询
        T ans = 0;
        for (int i = x; i; i -= i & -i) {
            for (int j = y; j; j -= j & -j) {
                ans += w[i][j];
            }
        }
        return ans;
    }
    T ask(int x, int y, int X, int Y) { // 区块查询：二维前缀和
        x--, y--;
        return ask(X, Y) - ask(x, Y) - ask(X, y) + ask(x, y);
    }
};

template<typename T>
struct Fenwick2D {
    int n, m;
    vector<vector<T>> b1, b2, b3, b4;
    
    Fenwick2D(int n, int m) : n(n), m(m) {
        b1.resize(n + 1, vector<T>(m + 1));
        b2.resize(n + 1, vector<T>(m + 1));
        b3.resize(n + 1, vector<T>(m + 1));
        b4.resize(n + 1, vector<T>(m + 1));
    }
    void add(auto &w, int x, int y, T k) { // 单点修改
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                w[i][j] += k;
            }
        }
    }
    void add(int x, int y, T k) { // 多了一步计算
        add(b1, x, y, k);
        add(b2, x, y, k * (x - 1));
        add(b3, x, y, k * (y - 1));
        add(b4, x, y, k * (x - 1) * (y - 1));
    }
    void add(int x, int y, int X, int Y, T k) { // 区块修改：二维差分
        X++, Y++;
        add(x, y, k), add(X, y, -k);
        add(X, Y, k), add(x, Y, -k);
    }
    T ask(auto &w, int x, int y) { // 单点查询
        T ans = 0;
        for (int i = x; i; i -= i & -i) {
            for (int j = y; j; j -= j & -j) {
                ans += w[i][j];
            }
        }
        return ans;
    }
    T ask(int x, int y) { // 多了一步计算
        T ans = 0;
        ans += x * y * ask(b1, x, y);
        ans -= y * ask(b2, x, y);
        ans -= x * ask(b3, x, y);
        ans += ask(b4, x, y);
        return ans;
    }
    T ask(int x, int y, int X, int Y) { // 区块查询：二维前缀和
        x--, y--;
        return ask(X, Y) - ask(x, Y) - ask(X, y) + ask(x, y);
    }
};
