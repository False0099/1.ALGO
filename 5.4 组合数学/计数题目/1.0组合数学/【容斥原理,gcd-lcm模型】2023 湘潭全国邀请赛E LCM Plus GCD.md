You are given two integers, $x$ and $k$. Your task is to determine the total number of sets that contain exactly $k$ distinct positive integers $a_1, a_2, ..., a_k$ such that the sum of their Least Common Multiple (LCM) and Greatest Common Divisor (GCD) equals $x$, i.e. $\operatorname{LCM}(a_1,a_2,\ldots, a_k)+\operatorname{GCD}(a_1,a_2,\ldots, a_k)=x$.

The LCM of a set of numbers is the smallest positive integer that each number in the set can divide, while the GCD is the largest positive integer that can divide each number in the set. For instance, $\operatorname{LCM}(4,6,8)=24$ and $\operatorname{GCD}(4,6,8)=2$.

As the result could potentially be a very large number, you should provide the output modulo $10^9 + 7$.

## 输入：
**Input**

One line contains two integers $x$ and $k$ ($1\le x, k \le 10^9$).

## 输出：
**Output**

Output an integer denoting the answer modulo $10^9 + 7$.

## 样例：
```
14 2
```

```
3
```

```
14 3
```

```
4
```

## 题解
假设现在我们有：$GCD(a_{1},\dots a_{k})=G,LCM(a_{1},\dots a_{k})=L=A\times G$
根据题意，需要求解 LCM $( a_1, a_2, \ldots , a_k)$ + $GCD$ $( a_1, a_2, \ldots , a_k) = x$ 即 $G+A\times G=(1+A)\times G=x$,枚举 $\mathcal{G}$,

枚举 G 之后之后，我们让所有的元素都除以 G，记我们的结果 $ai'=\dfrac{a_{i}}{G}$，也就是说，我们需要找到 k 个数，满足：

$$\mathrm{GCD}\big(a_1',a_2',\ldots,a_k'\big)=1,\mathrm{LCM}\big(a_1',a_2',\ldots,a_k'\big)=A,$$

同时，我们让我们的 $x$ 也也除以 G，我们就有：$x'=\frac{x}{G}$

于是我们的问题就变成了：
$$\begin{array}{l}1+A=x'\\A=x'-1\end{array}$$

$$\mathrm{GCD}\big(a'_1,a'_2,\ldots,a'_k\big)=1,\mathrm{LCM}\big(a'_1,a'_2,\ldots,a'_k\big)=A=n,$$

其中我们的 $n=\frac{x}{x_{a}}-1$,（$x_{a}$ 是我们是我们原式的某一个因子）

考虑对我们的 $n$ 进行进行质因数分解，也就是**计算我们每一个 n 对应的对应的方案是多少**。
$$
\begin{array}{c}\boldsymbol{\cdot}\operatorname{LCM}(a_1^{\prime},a_2^{\prime},\ldots,a_k^{\prime})=A=\prod_{j=1}^mp_j^{b_j}\\\boldsymbol{\cdot}\operatorname{GCD}(a_1^{\prime},a_2^{\prime},\ldots,a_k^{\prime})=1=\prod_{j=1}^mp_j^0\end{array}
$$
 $\bullet\:a_{i}^{\prime}=\prod_{j=1}^{m}p_{j}^{c_{ij}}$,
 ·根据 GCD 和 LCM 的定义，考虑每个质因子，GCD 每次都是取最小的指数，而 LCM 每次都
 是取最大的指数所以有$\cdot\operatorname*{min}\left\{c_{ij}\right\}=0$Max $\{c_{ij}\}=b_j$ · $m$ 个质因数，共 $2m$ 个约束要满足。

对于这类求全局中满足约束条件的问题，我们的做法一般来说都是采用我们的容斥原理。有：

对于单个 $n$,我们抽象一下容斥模型 . 
1. 全集 $U$: 满足 $a_i^{\prime}=\prod_{j=1}^mp_j^{c_{ij}}$ 且 $0\leq c_{ij}\leq b_j$ 的，任意的集合 $(a_1^{\prime},a_2^{\prime},\ldots,a_k^{\prime})$ 的集合，也就是一个集族 (集合的集合)
 2. 元素；一个集合 $\begin{pmatrix}a_1^{\prime},a_2^{\prime},\ldots,a_k^{\prime}\end{pmatrix}$
 3. 属性 $P_i\colon\left(a_1^{\prime},a_2^{\prime},\ldots,a_k^{\prime}\right)$ 的属性即 $\left(a_1^{\prime},a_2^{\prime},\ldots,a_k^{\prime}\right)$ 满足的条件，有两类：
 1. 一种是 GCD 的约束，$\min\left\{c_{ij}\right\}=0$,记为 $P_i$
 2. 一种是 LCM 的约束，$\max\left\{c_{ij}\right\}=b_j$,记为 $P_{m+i}$

4. 集合 $S_i$: 只有一条约束时，这些向量所构成的集合为 $S_i$ 1. 把对 GCD 的约束，定义为 $S_1,S_2,\cdots,S_m$
 2. 把对 LCM 的约束，定义为 $S_{m+1},S_{m+2},\cdots,S_{2m}$

接下来，我们再考虑一个问题，这 $2m$ 个约束是相互独立的吗？ 对于某一个质因数 $p_j$
 ·而一个方案 $\left(a_1^{\prime},a_2^{\prime},\ldots,a_k^{\prime}\right)$, $P_j$ 和 $\overline{P_j}$ 必然一真一假，也就是要么违反，要么不违反
 ·对于 $P_{m+j}$ 和 $\overline{P_{m+j}}$ 同理，也必然一真一假
 · 所以对 GCD 的约束和对 LCM 的约束并不是严格独立的，但各自内部之间的约束是独立的
 ·所以容斥时，不是一个 for 循环 $2^{2m}$ 这样枚举
 · 而是同时枚举对 GCD 的约束和对 LCM 的约束，两个 for 嵌套 $2^{2m}$ 枚举，或者可以理解一个方案在 $p_j$ 上的指数 min 和 max 是确定的。

接下来，我们还需要一个背景知识，$y_{j}\leq c_{ij}\leq z_{j}$ 的前提下，我们有 m 个数字，问这 m 个数字的取值应该是多少？

我们现在对于每一个质因子的指数，我们有 $(z_{j}-y_{j}+1)$ 种方案数，然后对于 m 个质因数，一共有：$B=\prod_{j=1}^{m}\:(z_{j}-y_{j}+1).$ 种可能的方案。然后我们再从中选择 k 个，也就是：${\dbinom{B}{k}}$ 种。这个也是我们的一个总集。

接下来我们就可以对做容斥了，约定 $s$ 是对 GCD 约束的二泄制枚举，$t$ 是对 LCM 约束的二进制枚举
 ·计算若干个“违反约束”的交集，即有若干个“违反约束”的自由选择的方案数

 ·上文说过，容斥原理的“奇加偶减”不过式子中 $\left|\bigcap_{i=1}^{2m}S_i\right|=\left|U\right|-\left|\bigcup_{i=1}^{2m}\overline{S_i}\right|$,前面有个负号，所以我们变成“奇减偶加”
 ·特别的，当 $s=t=0$ 时，也就是没有任何的“违反约束”的自由选择，即 $y_j=0,z_j=b_j$,
 相当于无约束，故全 0 对应的集合就是全集 $U$ (刚好是 0 个 1，对应的是“偶加”)
 ·所以我们容斥二进制枚举的时候，可以直接把右部都“加”上

$$
\text{而我们需要求解的就是}\left|\bigcap_{i=1}^{2m}S_i\right|=|U|-\left|\bigcup_{i=1}^{2m}\overline{S_i}\right|
$$



```cpp
```cpp
int x, k;
Z ans = 0;

pair<vector<int>, vector<int>> decompose(int x)
{//质因数分解
    vector<int> p, e; //质因数p，指数e
    for(int i = 2 ; i * i <= x; i ++)
        if(x % i == 0)
        {
            e.push_back(0);
            while(x % i == 0)
            {
                x /= i;
                ++ e.back();
            }
            p.push_back(i);
        }
    if(x > 1)
    {
        p.push_back(x);
        e.push_back(1);
    }
    return make_pair(p, e); //质因数p，指数e
}

void f(int d)
{
    int n = x / d - 1;
    if(n == 0)
        return;
    auto [p, e] = decompose(n); //质因数分解，质因数p，指数e
    int m = p.size(); //质因数个数
    for(int s = 0; s < (1 << m); s ++)
        for(int t = 0; t < (1 << m); t ++)
        {
            int B = 1;
            for(int i = 0; i < m; i ++)//对于每一个位置，我们去检查对应是否有限制，以及我们的对应限制是
            {
                int v = e[i] + 1;
                if(s >> i & 1) // 质因数pi的指数，是否违反min约束（1是0否）
                    v --; // max{c_{ij}} != 0，删除0这个选项
                if(t >> i & 1) // 质因数pi的指数，是否违反max约束（1是0否）
                    v --; // max{c_{ij}} != ei，删除ei这个选项
                B *= v;
            }
            int coef = __builtin_popcount(s) + __builtin_popcount(t); //popcount返回的是1的个数
            coef = coef & 1 ? -1 : 1;//容斥原理
            ans += comb.binom(B, k) * coef; // 组合数B选k
        }
    return ;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> x >> k; 
    for(int d = 1; d * d <= x; d ++)
        if(x % d == 0) //枚举约数，对每个约数都容斥计算
        {
            f(d);
            if(d * d != x)
                f(x / d);
        }
    cout << ans << '\n';
}
```


```