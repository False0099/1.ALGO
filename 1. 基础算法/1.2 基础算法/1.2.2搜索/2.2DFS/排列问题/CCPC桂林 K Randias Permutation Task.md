For two permutations $A$ and $B$ of length $n$, Randias can generate a permutation $C$ of length $n$ as $C = A \circ B$ in this way: for each $1\le i \le n$, $C[i] = A[B[i]]$.

Now he is given $m$ permutations $A_{1},A_{2}, \dots, A_{m}$, each of them is of length $n$. He wants to choose a non-empty set of indices $i_{1},i_{2}, \dots, i_{k}$ ($1\le k \le m$, $1\le i_{1} &lt; i_{2} \dots &lt; i_{k} \le m$), and calculate $C = (((A_{i_{1}} \circ A_{i_{2}}) \circ A_{i_{3}}) \circ A_{i_{4}}) \dots \circ A_{i_{k}}$. Randias wants to know, how many possible permutations $C$ he can generate? Output the answer modulo $10^9 + 7$.

A permutation of length $n$ is an array consisting of $n$ distinct integers from $1$ to $n$ in arbitrary order. For example, $[2,3,1,5,4]$ is a permutation, but $[1,2,2]$ is not a permutation ($2$ appears twice in the array), and $[1,3,4]$ is also not a permutation ($n=3$ but there is $4$ in the array)

## 输入
**Input**

The first line contains two positive integers $n,m$ ($1\le n \cdot m \le 180$), denoting the length of the permutation and the number of permutations.

The following $m$ lines, each line contains $n$ distinct integers, denoting one permutation.

## 输出
**Output**

One single integer, denoting the number of possible permutations $C$ Randias can generate, modulo $10^9+7$.

## 样例
```cpp
5 4
1 2 3 4 5
5 1 3 4 2
3 4 1 5 2
5 2 4 1 3
```

```cpp
8
```

## 题解
我们这一题唯一的思路就是大暴力，暴力枚举我们从 N 个中任选任意个，能够得到哪些特殊的元素，然后我们就结束了。我们这里需要用一个 set 来存储我们哪些已经处理过。
```cpp
onst int mod = 1e9 + 7;
int n, m, q;
vector<vector<int> > a;
vector<int> ve;
set<vector<int>> st, st2;


void solve() { 
    scanf("%d%d", &n, &m);
    a.clear();
    a.resize(m);

    for (int i = 0; i < m; ++i) {
        a[i].resize(n);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    st.clear();
    st.insert(a[0]);
    vector<int> res(n);
    for (int i = 1; i < m; ++i) {
        st2 = st;
        st.insert(a[i]); // 1) 只选第i个数组 
        for (auto ve: st2) {
            // 2) 选择第i个数组 且和 之前的 数组ve结合 
            for (int j = 0; j < n; ++j) {
                res[j] = ve[a[i][j]-1];
            }
            st.insert(res);
        }
    }
    printf("%d\n", st.size() % mod);


}
```