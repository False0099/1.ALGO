# [POI 2005] SZA-Template

## 题目描述

你打算在纸上印一串字母。

为了完成这项工作，你决定刻一个印章。印章每使用一次，就会将印章上的**所有**字母印到纸上。

同一个位置的相同字符可以印多次。例如：用 `aba` 这个印章可以完成印制 `ababa` 的工作（中间的 `a` 被印了两次）。但是，因为印上去的东西不能被抹掉，在同一位置上印不同字符是不允许的。例如：用 `aba` 这个印章不可以完成印制 `abcba` 的工作。

因为刻印章是一个不太容易的工作，你希望印章的字符串长度尽可能小。

## 输入格式

输入一个长度不超过 $5 \times 10^5$ 的非空字符串（只包含小写字母），代表要在纸上印的字符。

## 输出格式

输出一个整数，代表印章上字符串长度的最小值。

## 样例 #1

### 样例输入 #1

```
ababbababbabababbabababbababbaba
```

### 样例输出 #1

```
8
```

## 提示

印章为 `ababbaba`。

印制过程如下：

```plain
ababbababbabababbabababbababbaba
ababbababbabababbaba
            ababbabababbababbaba
ababbababbabab
            ababbababbabab
ababbaba
     ababbaba
ababbaba
     ababbaba
            ababbaba
                   ababbaba
                        ababbaba
ababbababbaba

```

## 题解
我们阅读题意后能够发现，我们想要找的这一个字符串似乎和我们的 KMP 数组有一定的关系，因为我们 KMP 数组找到的最长 border，一定是满足前缀=后缀。

但我们发现，我们的**前缀=后缀只是一个充分条件**，我们还需要满足更多其他的条件才能说是复合我们的要求的。我们观察后能够发现，他似乎是我们 1-i 的**最大 border 的一个子border。**

这个时候，我们就需要再去找**什么样的子 border 可以满足我们的要求**。我们能够发现，一个子 border 如果满足我们的要求，那么一定会有：**我们的两个 border 的长度拼接起来一定是要大于等于我们的原先的字符串的**。
例如：我们的 `ababbaba` 相对于我们的 `ababbababbabab` 就是一个合法的 `border`，而我们的 `aba` 相对于我们的 `ababbaba` 就不是一个合法的 border。

**对应到 kmp 的 next 构成的树上**,就是i在n到根的那条链上，并且把他子树的点列出来，相邻差的max<=i。从根往n那边走，在删点的同时维护每个点的前驱后继，从而维护max，就可以了。

 ```cpp
#include<bits/stdc++.h>
using std::vector;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define pb push_back
void chmax(int &x,int y)
{
    if(x<y)x=y;
}
const int N=5e5+5;
char s[N];int n,next[N];
int to[N];
vector<int>son[N];

int pre[N],suf[N],mx;

void del(int x)
{
    if(x)
    {
        int p=pre[x],s=suf[x];
        chmax(mx,s-p);
        suf[p]=s;pre[s]=p;
    }
    for(vector<int>::iterator i=son[x].begin();i!=son[x].end();++i)
    if(*i!=to[x]) del(*i);
}

int main()
{
    freopen("1.in","r",stdin);
    scanf("%s",s+1);
    n=strlen(s+1);
    int j=0;
    rep(i,2,n)
    {
        while(j&&s[j+1]!=s[i])j=next[j];
        if(s[j+1]==s[i]) next[i]=++j;
    }
    
    rep(i,1,n)son[next[i]].pb(i);
    for(int i=n;i;i=next[i]) to[next[i]]=i;
    
    rep(i,1,n) {pre[i]=i-1;suf[i]=i+1;}
    del(0);
    int i=1;
    while(mx>i) { del(i);i=to[i]; }
    printf("%d\n",i);
}
```