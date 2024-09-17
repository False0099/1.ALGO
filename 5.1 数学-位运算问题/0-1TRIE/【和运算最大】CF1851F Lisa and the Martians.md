#位运算 
# Lisa and the Martians

## 题面翻译

给定长度为 $n$ 的序列 $a$ 和一个正整数 $k$，保证 $0\leq a_i< 2^k$。求满足 $0\leq x<2^k$ 且 $i\neq j$ 的三元组 $(i,j,x)$ 使得 $(a_i\oplus x)\operatorname{and}(a_j\oplus x)$ 最大。如果有多组符合要求的输出任意一组即可。

多组数据。

## 题目描述

Lisa was kidnapped by martians! It okay, because she has watched a lot of TV shows about aliens, so she knows what awaits her. Let's call integer martian if it is a non-negative integer and strictly less than $ 2^k $ , for example, when $ k = 12 $ , the numbers $ 51 $ , $ 1960 $ , $ 0 $ are martian, and the numbers $ \pi $ , $ -1 $ , $ \frac{21}{8} $ , $ 4096 $ are not.

The aliens will give Lisa $ n $ martian numbers $ a_1, a_2, \ldots, a_n $ . Then they will ask her to name any martian number $ x $ . After that, Lisa will select a pair of numbers $ a_i, a_j $ ( $ i \neq j $ ) in the given sequence and count $ (a_i \oplus x) \& (a_j \oplus x) $ . The operation $ \oplus $ means [Bitwise exclusive OR](http://tiny.cc/xor_wiki), the operation $ \& $ means [Bitwise And](<http://tiny.cc/and_wiki >). For example, $ (5 \oplus 17) \& (23 \oplus 17) = (00101_2 \oplus 10001_2) \& (10111_2 \oplus 10001_2) = 10100_2 \& 00110_2 = 00100_2 = 4 $ .

Lisa is sure that the higher the calculated value, the higher her chances of returning home. Help the girl choose such $ i, j, x $ that maximize the calculated value.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — number of testcases.

Each testcase is described by two lines.

The first line contains integers $ n, k $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le k \le 30 $ ) — the length of the sequence of martian numbers and the value of $ k $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i < 2^k $ ) — a sequence of martian numbers.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print three integers $ i, j, x $ ( $ 1 \le i, j \le n $ , $ i \neq j $ , $ 0 \le x < 2^k $ ). The value of $ (a_i \oplus x) \& (a_j \oplus x) $ should be the maximum possible.

If there are several solutions, you can print any one.

## 样例 #1

### 样例输入 #1

```
10
5 4
3 9 1 4 13
3 1
1 0 1
6 12
144 1580 1024 100 9 13
4 3
7 3 0 4
3 2
0 0 1
2 4
12 2
9 4
6 14 9 4 4 4 5 10 2
2 1
1 0
2 4
11 4
9 4
2 11 10 1 6 9 11 0 5
```

### 样例输出 #1

```
1 3 14
1 3 0
5 6 4082
2 3 7
1 2 3
1 2 15
4 5 11
1 2 0
1 2 0
2 7 4
```

## 提示

First testcase: $ (3 \oplus 14) \& (1 \oplus 14) = (0011_2 \oplus 1110_2) \& (0001_2 \oplus 1110_2) = 1101_2 = 1101_2 \& 1111_2 = 1101_2 = 13 $ .

Second testcase: $ (1 \oplus 0) \& (1 \oplus 0) = 1 $ .

Third testcase: $ (9 \oplus 4082) \& (13 \oplus 4082) = 4091 $ .

Fourth testcase: $ (3 \oplus 7) \& (0 \oplus 7) = 4 $ .

## 题解
本题类似于 [[【与运算】CF1721D Maximum AND]]，都是要求我们的和运算最大的条件下我们的结果是多少，在这里，我们显然需要从高到低的贪心，我们按照 $a[i],a[j]$ 在这一位的取值分类：
1. $a[i]=0,a[j]=0$,那么这一位的 x 我们显然应该取 1
2. $a[i]=1,a[j]=0$,那么我们这一位不管取什么都没有贡献
3. $a[i]=0,a[j]=1$,同 2
4. $a[i]=1,a[j]=1$,那么我们这一位的 $x$ 显然应该取 0.

因此，又根据我们的贪心，我们最好就是从高到底找，找到的第  $k$ 位如果存在两个相同的值，我们就记录这一位的贡献，如果不存在两个相同的值，我们就跳过这一位。

现在对于我们的问题是，我们有 $n$ 个数，不过没关系，面对这种问题，我们的 0-1 TRIE 会出手，我们每一次查询就去查询这一位上是否有查询的数字，如果左右都有，那么我们就左右都走然后取最大即可。
```cpp
int query(int u,int depth){
	int tmp=0;
	int ans=0;
	for(int i=0;i<1;i++){
		if(cnt[u][i]>=2){
			ans+=1<<depth;
			int tmp=max(tmp,query(trie[u][i],depth-1));	
		}
	}
	return ans+tmp;
}
```
我们发现，要想让我们的答案尽可能的大，我们就要**从高位尽可能的选择我们重合**，在这种情况下，我们的 x 只需要用我们的取值取反就能够构造出我们的答案，这个就是我们 0-1trie 的功能惹。 

总结：我们用 0-1Trie 来维护我们 max $a_{i}\land a_{j}$ 的值，我们的 x 就是我们每一位按位取反后得到的结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
struct Point{
    int son[2],cnt,id;
    inline void clear(){
        son[0]=son[1]=cnt=id=0;
        return ;
    }
}Trie[maxn*32];
int T,n,k,kk,a[maxn],ans,ansid[2],cnt;
struct Trie_Tree{
    inline void Modify(int x,int f,bool op){
        int id=1,t;
        for(int i=k-1;i>=0;i--){
            t=(a[x]>>i)&1;
            if(!Trie[id].son[t]&&op)
                Trie[id].son[t]=++cnt;
            id=Trie[id].son[t];
            Trie[id].cnt+=f;
        }
        if(op)
            Trie[id].id=x;
        return ;
    }
    inline int Find(int x){
        int id=1,t;
        for(int i=k-1;i>=0;i--){
            t=(x>>i)&1;
            if(Trie[Trie[id].son[t]].cnt)
                id=Trie[id].son[t];
            else
                id=Trie[id].son[t^1];
        }
        return Trie[id].id;
    }
}Sherry;
int main(){
    scanf("%d",&T);
    while(T--){
        for(int i=0;i<=cnt;i++)
            Trie[i].clear();
        scanf("%d%d",&n,&k);
        kk=(1<<k)-1;
        cnt=1;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            Sherry.Modify(i,1,1);
        }
        ans=-168;
        ansid[0]=ansid[1]=0;
        for(int i=1;i<=n;i++){
            Sherry.Modify(i,-1,0);//删除这一位
            int res=Sherry.Find(a[i]);//查找和这一位最相似的一个
            if(ans<(kk&(a[res]^a[i]^kk))){//更新答案
                ans=(kk&(a[res]^a[i]^kk));
                ansid[0]=i;
                ansid[1]=res;
            }
            Sherry.Modify(i,1,0);//恢复这一位
        }
        printf("%d %d %d\n",ansid[0],ansid[1],kk^a[ansid[0]]);
    }
    return 0;
}
```
```
