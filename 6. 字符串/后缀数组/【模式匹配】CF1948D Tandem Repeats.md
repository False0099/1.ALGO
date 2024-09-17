You are given a string $s$, consisting of lowercase Latin letters and/or question marks.

A tandem repeat is a string of an even length such that its first half is equal to its second half.

A string $a$ is a substring of a string $b$ if $a$ can be obtained from $b$ by the deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

Your goal is to replace each question mark with some lowercase Latin letter in such a way that the length of the longest substring that is a tandem repeat is maximum possible.

**Input**

The first line contains a single integer $t$ ($1 \le t \le 1000$) — the number of testcases.

The only line of each testcase contains a string $s$ ($1 \le |s| \le 5000$), consisting only of lowercase Latin letters and/or question marks.

The total length of the strings over all testcases doesn't exceed $5000$.

**Output**

For each testcase, print a single integer — the maximum length of the longest substring that is a tandem repeat after you replace each question mark in the string with some lowercase Latin letter.

If it's impossible to make any tandem repeat substrings in the string, print $0$.

## 题解
本题的思路类似于我们的网络赛某题，就是要在我们的原串中判断两个位置是否是完全相等的。例如，如果我们有 $(i,j)=(j+1,j+1+j-i)$ 那么我们的答案长度就是我们的 $2*(j-i+1)$。现在我们考虑能否快速的处理出我们的字符串相等。

因为本题要求我们的时限可以进行我们的 $o(n^2)$ 计算，所以我们可以考虑先 $o(n^2)$ 的枚举我们的区间，之后，我们考虑有无 $o(1)$ 检查的方法。

首先，如果我们题目中没有 `？` 字符 ,那么我们直接采用哈希就能完成我们的匹配，这也是我们网络赛那一题的思路。但可惜的是，由于我们的 `?` 字符，我们不能直接得到我们的结果。

于是，我们考虑其他的匹配方法，在这里，我们采用的是我们的后缀数组匹配法。如果$\left[i,i+len-1\right]\text{和}\left[i+len,i+2*len-1\right]$
相等，我们就可以转换为判断两个后缀的前缀是否相等。也就是说，如果我们满足 $lcp(suf(i),suf(i+len))\geq len$,那么我们就可以说，我们的这一段是相等的。

因此，我们考虑不同后缀的最长公共前缀，这个就是我们熟知的 $lcp$,而我们的 $lcp$ 可以通过我们的后缀数组 $height$ 得到。或者我们可以通过我们的 $dp$ 来得到：
$lcp[i][j]=lcp[i+1][j+1]+1,when\ s[i]\equiv s[j]$, $lcp[i][j]=0,when\ s[i]\neq s[j]$. $o(1)$ 判断字符串相等的有一个有力工具

```cpp
int lcp[5050][5050];
void solve()
{   
    string s;
    cin>>s;
    int n = s.length();
    for(int i = 0;i<=n;i++) lcp[i][n] = 0;
    for(int i = n-1;i>=0;i--)
    {
        for(int j = n-1;j>=i;j--)
        {
            if(s[i]==s[j]) lcp[i][j] = lcp[i+1][j+1] + 1;
            else if(s[i]=='?'||s[j]=='?') lcp[i][j] = lcp[i+1][j+1] + 1;
            else lcp[i][j] = 0;
        }
    }
    int ans = 0;
    for(int i = 0;i<n;i++)
    {
        for(int len = 1;i+len<n;len++)
        {
            int j = i+len;
            if(lcp[i][j]>=len) ans = max(ans,len);
        }
    }
    cout<<2*ans<<'\n';
}
```