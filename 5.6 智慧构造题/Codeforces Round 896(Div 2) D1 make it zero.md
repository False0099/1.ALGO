# 
## 题目描述
After Zhongkao examination, Daniel and his friends are going to have a party. Everyone will come with some candies.

There will be n people at the party. Initially, the i-th person has ai candies. During the party, they will swap their candies. To do this, they will line up in an arbitrary order and everyone will do the following exactly once:

- Choose an integer p (1≤p≤n) and a non-negative integer x, then give his 2x2 candies to the p-th person. Note that one cannot give more candies than currently he has (he might receive candies from someone else before) and he cannot give candies to himself.

Daniel likes fairness, so he will be happy if and only if everyone receives candies from exactly one person. Meanwhile, his friend Tom likes average, so he will be happy if and only if all the people have the same number of candies after all swaps.

Determine whether there exists a way to swap candies, so that both Daniel and Tom will be happy after the swaps.

## 输入格式
The first line of input contains a single integer t (1≤t≤1000) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer n (2≤n≤2⋅105) — the number of people at the party.

The second line of each test case contains n integers a1,a2,…,an (1≤ai≤109) — the number of candies each person has.

It is guaranteed that the sum of n over all test cases does not exceed 2⋅105.


## 输出格式

For each test case, print "Yes" (without quotes) if exists a way to swap candies to make both Daniel and Tom happy, and print "No" (without quotes) otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 样例输入 #1

```
6
3
2 4 3
5
1 2 3 4 5
6
1 4 7 1 5 4
2
20092043 20092043
12
9 9 8 2 4 4 3 5 1 1 1 1
6
2 12 7 16 11 12

```

### 样例输出 #1

```
Yes
Yes
No
Yes
No
No

```

## 题解
我们考虑先转化我们的题意，我们令 $sum$ 为我们数组的和，显然只有当 $sum\ mod \ n=0$ 时，我们才存在一种合法方案：
我们令 ave 为我们整个数组的平均数，对于某一个元素中的元素 x，我们设 $dif=ave-x$,那么根据题目描述我们指导，每一个元素 $x$ 一定会发生 $x=x+2^j-2^k$ 这样的变化。而为了让 x 变成 tag，我们必须要满足 $2^j-2^k=dif$。因为每一个人会收到恰好一个人的糖果，并且会给出恰好一个人的糖果，我们**假设对于一个人如果他收到 x 个糖果并且给出 y 个糖果来达到平均值，那么一定有另外某个人给出了 x 个，另外有一个人得到了 y 个**

因此，对于每一个元素 x，我们可以枚举求出 $(j,k)$ 使得 $2^j-2^k=dif$,并且最后统计所有元素中，是否每一个 $(j,k)$ **都是出现了偶数次**，如果是，那么我们就输出 yes，否则输出no
## 代码
```cpp
ll n,a[200005],cnt[65];
inline void qfl_zzz(){
    n=read();ll sum=0;
    for(ll i=1;i<=n;++i)a[i]=read(),sum+=a[i];
    if(sum%n){
        printf("No\n");
        return;
    }
    ll tag=sum/n,flag=1;
    for(ll i=1;i<=n;++i){
        ll vis=0;
        for(ll j=0;j<=60;++j)
            for(ll k=0;k<=60;++k)
                if(a[i]+(1ll<<j)-(1ll<<k)==tag)
                    cnt[j]^=1,cnt[k]^=1,vis=1;
        if(!vis)flag=0;
    }
    for(ll i=0;i<=60;++i){
        if(cnt[i]>0)flag=0;
        cnt[i]=0;
    }
    if(flag)printf("Yes\n");
    else printf("No\n");
}
```
```