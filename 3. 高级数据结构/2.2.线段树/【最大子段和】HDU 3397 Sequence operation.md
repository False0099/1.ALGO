## 题目描述
lxhgww got a sequence contains n characters which are all '0's or '1's.  
We have five operations here:  
Change operations:  
0 a b change all characters into '0's in [a , b]  
1 a b change all characters into '1's in [a , b]  
2 a b change all '0's into '1's and change all '1's into '0's in [a, b]  
Output operations:  
3 a b output the number of '1's in [a, b]  
4 a b output the length of the longest continuous '1' string in [a , b]

省流：一个包含 n 个字符的序列 x, 其中字符都是 0 或 1，有以下五种操作
1. 把【a, b】区间内的数都变为 0
2. 把[A, B]都变成 1
3. 把[A, B]区间内的数都按位取反
4. 查询区间内 1 的个数
5. 找到最长的连续 1 串
## 输入格式
T(T<=10) in the first line is the case number.  
Each case has two integers in the first line: n and m (1 <= n , m <= 100000).  
The next line contains n characters, '0' or '1' separated by spaces.  
Then m lines are the operations:  
op a b: 0 <= op <= 4 , 0 <= a <= b < n.


## 输出格式
For each output operation , output the result.


## 样例 #1

### 样例输入 #1

```
1
10 10
0 0 0 1 1 0 1 0 1 1
1 0 2
3 0 5
2 2 2
4 0 4
0 3 6
2 3 7
4 2 8
1 0 5
0 5 6
3 3 9
```

### 样例输出 #1

```
5
2
6
5
```

## 题解
我们这一题中的难点在于区间的反转，因此我们不仅要维护区间中的最长 1 前后缀，也要维护最长 0 前后缀，以便于我们反转操作。
如果有反转，我们就把我们的原先最长 0 串后缀和我们的最长 1 串交换，把我们原先的最长 0 串前缀和我们的最长 1 串前缀交换。最后我们交换即可。

## 代码
```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
#define LL long long
using namespace std;
const int MAX = 1e5 + 50;
 
struct date
{
    int len; // 记录区间长度
    int ln, rn; // 记录区间左端和右端的数字
    int ls0, rs0, ms0; //记录区间从左开始的最长连续0，右端开始的最长连续0，以及区间的最长连续0
    int ls1, rs1, ms1; //同上
    int sum1; //记录1的个数
} tree[MAX << 2]; // 线段树
 
int a[MAX]; //原数组
int lazy[MAX << 2][3]; // 0代表操作0，类推
 
void PushUp(int rt){ 
    int li = rt << 1;
    int ri = rt << 1 | 1;
    tree[rt].ln = tree[li].ln;
    tree[rt].rn = tree[ri].rn;
    tree[rt].ls1 = tree[li].ls1;
    tree[rt].rs1 = tree[ri].rs1;
    tree[rt].ms1 = max(tree[li].ms1, tree[ri].ms1);
    tree[rt].ls0 = tree[li].ls0;
    tree[rt].rs0 = tree[ri].rs0;
    tree[rt].ms0 = max(tree[li].ms0, tree[ri].ms0);
    tree[rt].sum1 = tree[li].sum1 + tree[ri].sum1;
 
    if(tree[li].rn == tree[ri].ln){
        if(tree[li].rn == 0){
            if(tree[li].len == tree[li].ls0){
                tree[rt].ls0 = tree[li].ls0 + tree[ri].ls0;
            }
            if(tree[ri].len == tree[ri].rs0){
                tree[rt].rs0 = tree[ri].rs0 + tree[li].rs0;
            }
            tree[rt].ms0 = max(tree[rt].ms0, tree[li].rs0 + tree[ri].ls0);
        } else{
            if(tree[li].len == tree[li].ls1){
                tree[rt].ls1 = tree[li].ls1 + tree[ri].ls1;
            }
            if(tree[ri].len == tree[ri].rs1){
                tree[rt].rs1 = tree[ri].rs1 + tree[li].rs1;
            }
            tree[rt].ms1 = max(tree[rt].ms1, tree[li].rs1 + tree[ri].ls1);
        }
    }
}
 
void Build(int l, int r, int rt){
    tree[rt].len = r - l + 1;
    if(l == r){
        tree[rt].ln = tree[rt].rn = a[l];
        if(a[l] == 0){
            tree[rt].ls0 = tree[rt].rs0 = tree[rt].ms0 = 1;
            tree[rt].ls1 = tree[rt].rs1 = tree[rt].ms1 = 0;
            tree[rt].sum1 = 0;
        } else{
            tree[rt].ls0 = tree[rt].rs0 = tree[rt].ms0 = 0;
            tree[rt].ls1 = tree[rt].rs1 = tree[rt].ms1 = 1;
            tree[rt].sum1 = 1;
        }
        return ;
    }
 
    int m = (l + r) >> 1;
    Build(l, m, rt << 1);
    Build(m + 1, r, rt << 1 | 1);
    PushUp(rt);
}
 
void PushDown(int rt){
    if(tree[rt].len == 1){
        return ;
    }
    int li = rt << 1;
    int ri = rt << 1 | 1;
    if(lazy[rt][0]){
        lazy[rt][0] = 0;
        tree[ri].ls0 = tree[ri].rs0 = tree[ri].ms0 = tree[ri].len;
        tree[ri].ls1 = tree[ri].rs1 = tree[ri].ms1 = 0;
        tree[ri].ln = tree[ri].rn = 0;
        tree[ri].sum1 = 0;
        lazy[ri][0] = 1; // 要把除了操作0的其他lazy标记去除
        lazy[ri][1] = 0;
        lazy[ri][2] = 0;
        tree[li].ls0 = tree[li].rs0 = tree[li].ms0 = tree[li].len;
        tree[li].ls1 = tree[li].rs1 = tree[li].ms1 = 0;
        tree[li].ln = tree[li].rn = 0;
        tree[li].sum1 = 0;
        lazy[li][0] = 1;
        lazy[li][1] = 0;
        lazy[li][2] = 0;
    }
    If (lazy[rt][1]){
        lazy[rt][1] = 0;
        tree[ri].ls0 = tree[ri].rs0 = tree[ri].ms0 = 0;
        tree[ri].ls1 = tree[ri].rs1 = tree[ri].ms1 = tree[ri].len;
        tree[ri].ln = tree[ri].rn = 1;
        tree[ri].sum1 = tree[ri].len;
        lazy[ri][0] = 0;// 要把除了操作1的其他lazy标记去除
        lazy[ri][1] = 1;
        lazy[ri][2] = 0;
        tree[li].ls0 = tree[li].rs0 = tree[li].ms0 = 0;
        tree[li].ls1 = tree[li].rs1 = tree[li].ms1 = tree[li].len;
        tree[li].ln = tree[li].rn = 1;
        tree[li].sum1 = tree[li].len;
        lazy[li][0] = 0;
        lazy[li][1] = 1;
        lazy[li][2] = 0;
    }
 
    if(lazy[rt][2]){
        lazy[rt][2] = 0;
        swap(tree[li].ls0, tree[li].ls1);
        swap(tree[li].rs0, tree[li].rs1);
        swap(tree[li].ms0, tree[li].ms1);
        tree[li].sum1 = tree[li].len - tree[li].sum1;
        tree[li].ln ^= 1;
        tree[li].rn ^= 1;
        lazy[li][2] ^= 1; // 这里也对1异或，理由就像之前讲的
        swap(tree[ri].ls0, tree[ri].ls1);
        swap(tree[ri].rs0, tree[ri].rs1);
        swap(tree[ri].ms0, tree[ri].ms1);
        tree[ri].sum1 = tree[ri].len - tree[ri].sum1;
        tree[ri].ln ^= 1;
        tree[ri].rn ^= 1;
        lazy[ri][2] ^= 1;
    }
}
 
int L, R;
void Update0(int l, int r, int rt){
    if(L <= l && r <= R){
        tree[rt].ls0 = tree[rt].rs0 = tree[rt].ms0 = tree[rt].len;
        tree[rt].ls1 = tree[rt].rs1 = tree[rt].ms1 = 0;
        tree[rt].ln = tree[rt].rn = 0;
        tree[rt].sum1 = 0;
        lazy[rt][0] = 1;
        lazy[rt][1] = 0;
        lazy[rt][2] = 0;
        return ;
    }
 
    PushDown(rt);
    int m = (l + r) >> 1;
    if(L <= m){
        Update0(l, m, rt << 1);
    }
    if(R > m){
 
        Update0(m + 1, r, rt << 1 | 1);
    }
    PushUp(rt);
}
 
void Update1(int l, int r, int rt){
    if(L <= l && r <= R){
        tree[rt].ls0 = tree[rt].rs0 = tree[rt].ms0 = 0;
        tree[rt].ls1 = tree[rt].rs1 = tree[rt].ms1 = tree[rt].len;
        tree[rt].ln = tree[rt].rn = 1;
        tree[rt].sum1 = tree[rt].len;
        lazy[rt][0] = 0;
        lazy[rt][1] = 1;
        lazy[rt][2] = 0;
        return ;
    }
 
    PushDown(rt);
    int m = (l + r) >> 1;
    if(L <= m){
        Update1(l, m, rt << 1);
    }
    if(R > m){
 
        Update1(m + 1, r, rt << 1 | 1);
    }
    PushUp(rt);
}
 
void Update2(int l, int r, int rt){
    if(L <= l && r <= R){
        swap(tree[rt].ls0, tree[rt].ls1);
        swap(tree[rt].rs0, tree[rt].rs1);
        swap(tree[rt].ms0, tree[rt].ms1);
        tree[rt].sum1 = tree[rt].len - tree[rt].sum1;
        tree[rt].ln ^= 1;
        tree[rt].rn ^= 1;
        lazy[rt][2] ^= 1; //这里对1异或，理由同上
        return ;
    }
 
    PushDown(rt);
    int m = (l + r) >> 1;
    if(L <= m){
        Update2(l, m, rt << 1);
    }
    if(R > m){
        Update2(m + 1, r, rt << 1 | 1);
    }
    PushUp(rt);
}
 
int Query3(int l, int r, int rt){
    if(L <= l && r <= R){
        return tree[rt].sum1;
    }
    int ans = 0;
    PushDown(rt);
    int m = (l + r) >> 1;
    if(L <= m){
        ans += Query3(l, m, rt << 1);
    }
    if(R > m){
        ans += Query3(m + 1, r, rt << 1 | 1);
    }
    return ans;
}
 
int Query4(int l, int r, int rt){
    if(L <= l && r <= R){
        return tree[rt].ms1;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if(R <= m){
        return Query4(l, m, rt << 1);
    }
    if(L > m){
        return Query4(m + 1, r, rt << 1 | 1);
    }
 
    int t1 = Query4(l, m, rt << 1);
    int t2 = Query4(m + 1, r, rt << 1 | 1);
    int t3 = 0;
    int li = rt << 1;
    int ri = rt << 1 | 1;
    if(tree[li].rn == tree[ri].ln && tree[li].rn){
        t3 = min(m - L + 1, tree[li].rs1) + min(R - m, tree[ri].ls1);
    }
    return max(max(t1, t2), t3);
}
 
int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while(t--){
        memset(lazy, 0, sizeof(lazy));
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        Build(1, n, 1);
 
        while(m--){
            int q;
            scanf("%d%d%d", &q, &L, &R);
            L++; //题目给的区间时从0开始的，为了方便我们从1开始，所以这里要++
            R++;
            if(q == 0){
                Update0(1, n, 1);
            } else if(q == 1){
                Update1(1, n, 1);
            } else if(q == 2){
                Update2(1, n, 1);
            } else if(q == 3){
                printf("%d\n", Query3(1, n, 1));
            } else{
                printf("%d\n", Query4(1, n, 1));
            }
        }
    }
    return 0;
}
```