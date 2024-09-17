给定两个串 $S$ 和 $T$，你可以对这两个串分别进行重排，定义匹配度为最大的非负整数 $x$ 使得能从 $S$ 中选出 $x$ 个不相交子串满足这几个子串都等于 $T$。请问重排后能获得的最大匹配度为多少。

本题多组数据。  
  
第一行一个数 $t(1\leq t\leq 5)$，表示数据组数。  
  
对于每组数据，一行为两个字符串 $S,T(1\leq |S|,|T|\leq 10^5)$，保证字符集为小写字母集。

$T$ 个数，表示答案。

输入
--

 2 abcadc ac bbbbbbb bd

```
2
abcadc
ac
bbbbbbb
bd```

输出
--

 2 0

```


## 题解
我们这一题只需要考虑我们每一个小写字母出现的次数，然后我们再去用我们的简单的除以判断去一个最小值即可。
```text
void solve()
{
    cin >> s + 1 >> t + 1;
    n = strlen(s + 1), m = strlen(t + 1);
    map<char, int> S, te;
    int res = 1e5 + 10;
    
    rep(i, 1, n)
    S[s[i]]++;
    
    rep(i, 1, m) te[t[i]]++;
    for(auto u : te)
    {
        res = min(res, S[u.x] / u.y);
    }
    
    pli(res);
}
```
