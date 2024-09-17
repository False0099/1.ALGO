小猫接管了一个新公园的管理。在公园的中心有一个大的圆形雕像，周围有 N 盆花。每盆花都会被分配到一个整数（可能是负数），表示它的吸引力有多大。请看下图作为一个例子。  
![enter image description here](https://vj.csgrandeur.cn/0c58435e608fa52dfba86010a3b16a56?v=1651066261)

(盆花的位置被分配到1 ……N范围内的索引号。对于任何给定的i(1<=i<N)，第i盆和第(i+1)盆是连续的，此外，第1盆紧挨着第N盆。）

董事会主席通知小猫为游客建造 "一个弧形的手杖椅"，手杖椅旁边的花的吸引力值之和要尽可能大。你应该注意到，藤椅不可能是一个完整的圆，所以藤椅旁边的花的数量可以是1，2，…，N-1，但不能是N。在上面的例子中，如果我们在那个红色虚线的位置建造一个藤椅，我们将得到3+(-2)+1+2=4的总和，这是所有可能的建造中最大的。

不幸的是，一些有脚的猫总是给小猫制造麻烦，把一些盆花换成别的。小猫的情报机构已经掌握了所有有蹄猫行动的M种工具。每个工具都是以 "A B "的形式出现的，这意味着用一个新的吸引值等于B的盆花来改变第A盆盆花，你必须在每个指令后报告新的 "最大和"。

Input

在输入中会有一个单一的测试数据。在第一行输入中给你一个整数N（4 <= N <= 100000）。

第二行包含N个整数，它们是每个盆花的初始吸引力值。第i个数字是指第i个位置上的盆花。

第三行输入一个整数M（4 <= M <= 100000），后面的M行各包含一条指令 "A B"，其形式如上所述。

限制条件。所有有吸引力的数值都在[-1000, 1000]之内。我们保证最大的和总是一个正整数。

Output

对于每条指令，输出一条单行，列出最佳藤椅的最大吸引力值之和。

Sample

|Inputcopy|Outputcopy|
|---|---|
|5<br>3 -2 1 2 -5<br>4<br>2 -2<br>5 -5<br>2 -4<br>5 -1|4<br>4<br>3<br>5|


## 题解
这一题相当于我们求解我们**环形区间上的最大连续和**，我们理论上可以，可以把这个环形给破环为链，之后再在我们的链上用我们的线段树合并来完成，但是这么写要考虑区间的长度问题，比较麻烦。所以我们有一个巧妙地方法，我们的连续和可以分为两类, **一类是不通过 1-n 连接的，另一类是通过 1-n 链接的**，那么考虑两个数组拼接的时候，**如果最优解只在左半边或右半边，那么结果就是维护的最大子段和**（***第一类链接***），如果有交叉，就是区**间和-区间最小子段和**（***第二类链接***）

```cpp
const int maxn = 1e6+10;
struct Tree {
    int l, r, lmax, rmax, lmin, rmin, sum, smax, smin;
} tree[maxn<<2];
int n, arr[maxn<<1];
inline void push_down(int rt) {
    tree[rt].sum = tree[rt<<1].sum+tree[rt<<1|1].sum;
    tree[rt].lmax = max(tree[rt<<1].lmax, tree[rt<<1].sum+tree[rt<<1|1].lmax);
    tree[rt].rmax = max(tree[rt<<1|1].rmax, tree[rt<<1|1].sum+tree[rt<<1].rmax);
    tree[rt].smax = max(max(tree[rt<<1].smax, tree[rt<<1|1].smax), tree[rt<<1].rmax+tree[rt<<1|1].lmax);
    tree[rt].lmin = min(tree[rt<<1].lmin, tree[rt<<1].sum+tree[rt<<1|1].lmin);
    tree[rt].rmin = min(tree[rt<<1|1].rmin, tree[rt<<1|1].sum+tree[rt<<1].rmin);
    tree[rt].smin = min(min(tree[rt<<1].smin, tree[rt<<1|1].smin), tree[rt<<1].rmin+tree[rt<<1|1].lmin);
}
void build(int rt, int l, int r) {
    tree[rt].l = l, tree[rt].r = r;
    if (l==r) {
        tree[rt].smin = tree[rt].lmin = tree[rt].rmin = tree[rt].smax = tree[rt].lmax = tree[rt].rmax = tree[rt].sum = arr[l];
        return;
    }
    int mid = (l+r)>>1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    push_down(rt);
}
void update(int rt, int pos, int val) {
    if (tree[rt].l==tree[rt].r) {
        tree[rt].smin = tree[rt].lmin = tree[rt].rmin = tree[rt].smax = tree[rt].lmax = tree[rt].rmax = tree[rt].sum = val;
        return;
    }
    int mid = (tree[rt].l+tree[rt].r)>>1;
    if (pos<=mid) update(rt<<1, pos, val);
    else update(rt<<1|1, pos, val);
    push_down(rt);
}
int main() {
    while(cin >> n) {
        for (int i = 1; i<=n; ++i) scanf("%d", &arr[i]), arr[i+n] = arr[i];
        build(1, 1, n);
        int m; cin >> m;
        while(m--) {
            int a, b; scanf("%d%d", &a, &b);
            update(1, a, b); 
            if (tree[1].smax==tree[1].sum) printf("%d\n", tree[1].sum-tree[1].smin);
            else printf("%d\n", max(tree[1].smax, tree[1].sum-tree[1].smin));
        }
    }
    return 0;
}
```