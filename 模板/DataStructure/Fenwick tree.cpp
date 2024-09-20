//basic
template <typename T>
struct Fenwick {
    int n;
    vector<T> w;

    Fenwick(int n) {
        this->n = n;
        w.resize(n + 1);
    }
    void add(int x, T k) {
        for (; x <= n; x += x & -x) {
            w[x] += k;
        }
    }
    void add(int x, int y, T k) { // 区间修改
        add(x, k), add(y + 1, -k);
    }
    T ask(int x) {  //单点查询
        auto ans = T();
        for (; x; x -= x & -x) {
            ans += w[x];
        }
        return ans;
    }
    T ask(int x, int y) { // 区间查询(区间和)
        return ask(y) - ask(x - 1);
    }
    int kth(T k) { //查找第k大的值
        int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            int val = ans + (1 << i);
            if (val < n && w[val] < k) {
                k -= w[val];
                ans = val;
            }
        }
        return ans + 1;
    }
};

//逆序对封装
template <typename T>
struct Fenwick {
    int n;
    vector<T> w;

    Fenwick() {}
    void add(int x, T k) {
        for (; x <= n; x += x & -x) {
            w[x] += k;
        }
    }
    T ask(int x) {
        T ans = 0;
        for (; x; x -= x & -x) {
            ans += w[x];
        }
        return ans;
    }
    T ask(int x, int y) {
        return ask(y) - ask(x - 1);
    }
    T get(auto val) { // 获取逆序对数量
        this->n = val.size() - 1; // 注意 n 不能 +1
        w.resize(n + 1);

        vector<pair<int, int>> alls;
        for (int i = 1; i <= n; i++) {
            alls.emplace_back(val[i], i);
        }
        sort(alls.begin(), alls.end()); 

        T ans = 0;
        for (auto [val, idx] : alls) {
            ans += ask(idx + 1, n);
            add(idx, 1);
        }
        return ans;
    }
};


// 前驱后继扩展（常规+第 k 小值查询+元素排名查询+元素前驱后继查询）
// 注意，被查询的值都应该小于等于N，否则会越界；如果离散化不可使用，则需要使用平衡树替代
template<typename T>
struct Fenwick {
    int n;
    vector<T> w;
    Fenwick(int n) : n(n), w(n + 1) {}
    void add(int x, T v) {
        for (; x <= n; x += x & -x) {
            w[x] += v;
        }
    }
    int kth(T x) { // 查找第 k 小的值
        int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            int val = ans + (1 << i);
            if (val < n && w[val] < x) {
                x -= w[val];
                ans = val;
            }
        }
        return ans + 1;
    }
    T get(int x) { // 查找 x 的排名
        T ans = 1;
        for (x--; x; x -= x & -x) {
            ans += w[x];
        }
        return ans;
    }
    int pre(int x) { return kth(get(x) - 1); } // 查找 x 的前驱
    int suf(int x) { return kth(get(x + 1)); } // 查找 x 的后继
};
const int N = 10000000; 