
# [NEERC2013] Hack Protection
## 题意翻译
给定一个序列$a_i$，求有多少个区间满足区间内的数的异或和等于与的和的值。
## 题目描述


Pavel is sending to his friend Egor some array of non-negative integers. He wants to be sure, that nobody hacks the array before his friend gets it. To solve this problem Pavel need to compute some kind of a checksum or a digest for his array. Pavel has an innovative mind, so he invents the following algorithm to compute the digest for his array: count the number of subarrays in which the bitwise xor of the numbers in the subarray is equal to the bitwise and of the same numbers.

For example, consider an array of four binary numbers `01`, `10`, `11`, and `11`. The table below to the left lists the results of the bitwise xor of numbers for each subarray of this array, and the table below to the right list the results of the bitwise and of numbers for each subarray of this array. The rows of the table correspond to the starting elements of the subarray from the $1st$ element of the array to the $4th$ one, while columns correspond to the ending elements of the subarray. Matching values are highlighted with gray background.

![](/upload/images2/hp.png)

Your task is to help Pavel compute this kind of a digest of the given array.


## 输入输出格式
#### 输入格式



The first line contains one integer $n (1 \le n \le 100 000)$ . The second line contains $n$ non-negative integers $a_{i} (0 \le a_{i} \le 2^{31}-1)$ that are written in decimal notation.


#### 输出格式



On the first line of the output print Pavel's digest of the given array.


## 输入输出样例
#### 输入样例 #1
4
1 2 3 3

#### 输出样例 #1
6

## 说明
Time limit: 1 s, Memory limit: 128 MB. 


## 题解
我们注意到我们的**与运算**的性质，我们每一次与运算，我们的二进制下 1 的个数不会增加。
那么，我们在**固定一个端点的情况下**，我们的区间与运算取值不会超过 $\log$ 个。

也就是说，我们可以考虑下面的着一种方法：我们每一次找到**第一个从这个断电开始让我们的 1 个数发生改变的位置**。我们记这个位置位 $l_{1}$,之后，我们的问题就变为：找我们的 $start-l$ 位置上，我们去见异或为我们的定制的位置有多少个。我们显然可以通过我们的 map 来进行统计。

现在，我们的问题就变成了，怎么每一次找到第一个发生改变的位置。这里，我们采用的方法是，对于我们的原来的数组，我们进行**拆位**，拆分出 32 个数组，然后我们每一次对于我们当前位置位 1 的部分，找这个位置向后的第一个为 0 的部分。

于是，我们可以考虑维护我们每一次与我们的原来的数字一样的位置是那些。把他存储在我们的一个数组当中。

```
#include <bits/stdc++.h>

using namespace std;
using ll=long long;

constexpr int MAXN=1e5+10;

map<int,vector<int>> mp;
int n,a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<pair<int,int>> val;
	    cin>>n; int pre=0; ll ans=0; mp[0].emplace_back(0);
    for(int i=1;i<=n;++i) {
        cin>>a[i]; pre^=a[i]; mp[pre].emplace_back(i);
        for(auto &[r,v]:val) v&=a[i];//暴力更新我们的前缀和
        val.emplace_back(i,a[i]);
        vector<pair<int,int>> tmp; int p=0,cur=-1;
        for(auto &[r,v]:val) {
            if(cur!=v) {
                if(p) tmp.emplace_back(p,cur);
                cur=v;
            }
            p=r;
        }
        tmp.emplace_back(p,cur); swap(tmp,val);//暴力去重
        int lst=0;
        for(auto [r,v]:val) {
            int req=pre^v;
            if(mp.find(req)==mp.end()) {lst=r; continue;}
            auto &vec=mp[req];
            ans+=upper_bound(vec.begin(),vec.end(),r-1)-lower_bound(vec.begin(),vec.end(),lst);
            lst=r;
        }//对于每一段区间求答案
    }
    cout<<ans<<endl;
    return 0;
}
```