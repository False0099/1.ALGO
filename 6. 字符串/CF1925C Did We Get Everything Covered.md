You are given two integers $n$ and $k$ along with a string $s$.

Your task is to check whether all possible strings of length $n$ that can be formed using the first $k$ lowercase English alphabets occur as a subsequence of $s$. If the answer is NO, you also need to print a string of length $n$ that can be formed using the first $k$ lowercase English alphabets which does not occur as a subsequence of $s$.

If there are multiple answers, you may print any of them.

**Note:** A string $a$ is called a subsequence of another string $b$ if $a$ can be obtained by deleting some (possibly zero) characters from $b$ without changing the order of the remaining characters.

**Input**

The first line of input contains a single integer $t \, (1 \le t \le 10^5)$, the number of test cases.

The first line of each test case contains $3$ integers $n \, (1 \le n \le 26), \: k \, (1 \le k \le 26), \: m \, (1 \le m \le 1000)$, where $n$ and $k$ are the same as described in the input and $m$ is the length of the string $s$.

The second line of each test case contains a single string $s$ of length $m$, comprising only of the first $k$ lowercase English alphabets.

It is guaranteed that the sum of $m$ and the sum of $n$ over all test cases does not exceed $10^6$.

**Output**

For each test case, print YES if all possible strings of length $n$ that can be formed using the first $k$ lowercase English alphabets occur as a subsequence of $s$, else print NO.

If your answer is NO, print a string of length $n$ that can be formed using the first $k$ lowercase English alphabets which does not occur as a subsequence of $s$ in the next line.

You may print each letter of YES or NO in any case (for example, YES, yES, YeS will all be recognized as a positive answer).

**Input
```
3
2 2 4
abba
2 2 3
abb
3 3 10
aabbccabab

```

**Output
```
YES
NO
aa
NO
ccc
```

## 题解
我们这一题关于我们判定我们的是否能够组成我们这里不再赘述，我们这里重点关注的是，怎么对于我们的 No 样例进行构造。

这个时候，我们需要做的就很简单，如果我们的元素是知道缺少哪一个的，那么我们就构造我们的对应元素即可。

如果我们正好之构成了一个三元组，那么我们记上一个三元组的最后一个元素为 c ，**我们让我们的上一个三元组的末尾元素作为我们的开头元素，剩下的随意构造即可**。

```cpp
#include <bits/stdc++.h>                   
using namespace std;

int main()
{
    std::ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
        int n, k, m;
        cin>>n>>k>>m;
        string s;
        cin>>s;
        string res="";
        bool found[k];
        memset(found, false, sizeof(found));
        int count=0;
        for(char c:s)
        {
            if(res.size()==n)
                break;
            count+=(!found[c-'a']);
            found[c-'a']=true;
            if(count==k)
            {
                memset(found, false, sizeof(found));
                count=0;
                res+=c;
            }
        }
        if(res.size()==n)
            cout<<"YES\n";
        else
        {
            cout<<"NO\n";
            for(int i=0;i<k;i++)
            {
                if(!found[i])
                {
                    while(res.size()<n)
                        res+=(char)('a'+i);
                }
            }
            cout<<res<<"\n";
        }
    }
}
```