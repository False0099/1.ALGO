问题 2：有 $P$ 只北极熊，$B$ 只棕熊，$G$ 只灰熊。现在每次不断随机挑选两只熊代价，输的焦被消除，直到最后剩下一只熊。最后第 $i$ 只熊的排名为自己被消除的时候场上还剩下多少只熊 (最后幸存的熊为第一名)。并且灰熊实力强于北极熊，而北极熊则强于棕熊。如果选择的两只熊种族不同，则实力较强的获胜，否则则每只熊都有五成的概率获胜。Limak 是一只北极熊，问最后 Limak 的排名的期望。这里 $1\leq P,B,G\leq2000$。

题解：
本题首先我们需要知道下面的几种方法：
我们一个棕熊的排名的期望可以通过我们枚举他的排名以及在这个排名的概率来计算得到：


然后，我们又有下面的等式，就可以推导出我们的 E_P 是多少。
$$\begin{gathered}
E[\sum_{i=1}^Pp_i+\sum_{i=1}^Bb_i+\sum_{i=1}^Gg_i]=\frac{(n+1)n}2 \\
\Rightarrow PE_P+BE_B+GE_G=\frac{(n+1)n}2 \\
\Rightarrow E_P=(\frac{(n+1)n}2-BE_B-GE_G)/P 
\end{gathered}$$


```cpp
int strong_ev(int STRONG, int WEAK) {
    int[] inv_pairs = new int[STRONG + WEAK + 1];
    for(int i = 0; i <= STRONG + WEAK; ++i) {
        inv_pairs[i] = my_inv(i * (i - 1) / 2); // inverse modulo 1e9+7
    }
    long[][] dp = new long[STRONG+1][WEAK+1];
    dp[STRONG][WEAK] = 1;
    int answer = STRONG + WEAK + 1; // default place
    for(int strong = STRONG; strong >= 0; --strong) {
        int p_strong_lives = mul(strong, my_inv(STRONG)); // division by 0 is ok
        for(int weak = WEAK; weak >= 0; --weak) {
            int here = (int)(dp[strong][weak] % MOD);
            answer = (answer - mul(here, p_strong_lives)) % MOD;
            final int c = mul(here, inv_pairs[strong + weak]);
            if(strong >= 2) {
                dp[strong-1][weak] += mul(c,strong * (strong - 1) / 2);
            }
            if(weak >= 2) {
                dp[strong][weak-1] += mul(c, weak * (weak - 1) / 2);
            }
            if(strong >= 1 && weak >= 1) {
                dp[strong][weak-1] += mul(c, strong * weak);
            }
        }
    }
    return (answer + MOD) % MOD;
}
public int findEV(int P, int B, int G) {
    // grizzly > polar > brown
    int g = strong_ev(G, P + B);//计算我们强者的期望
    int pg = strong_ev(P + G, B);//计算我们弱者的期望
    // g * G + p * P = pg * (P + G)
    // p = (pg * (P + G) - g * G) / P
    int tmp = mul(pg, P + G) - mul(g, G);
    tmp = (tmp + MOD) % MOD;
    return mul(tmp, my_inv(P));
}
```
