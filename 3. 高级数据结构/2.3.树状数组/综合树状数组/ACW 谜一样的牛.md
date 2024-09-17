# 知识点
  ## [[树状数组]] 
# 题目
 有 n头奶牛，已知它们的身高为 1∼n且各不相同，但不知道每头奶牛的具体身高。

现在这 n头奶牛站成一列，已知第 i头牛前面有 Ai头牛比它低，求每头奶牛的身高。

## 输入格式
第 1 行：输入整数 n。

第 $2\sim N$ 行：每行输入一个整数 Ai，第 i 行表示第 i 头牛前面有 Ai 头牛比它低（注意：因为第 1头牛前面没有牛，所以并没有将它列出）

## 输出格式
输出包含 n 行，每行输出一个整数表示牛的身高。

第 i 行输出第 i 头牛的身高。

## 数据范围
$1≤n≤10^5$
## 输入样例 ：
5
1
2
1
0
## 输出样例 ：
2
4
5
3
1

# 思路
我们先通过手动算法算一遍样例，发现求的过程就是先**从后往前求出每一个位置是剩下的数里面第 k 大的**，其中 k 时该位置处的置。

我们优化的关键就在于**求出来剩余数里第 k 大的数的**方法，找到这一个方法就能最后优化出结果。

我们这里的第 k 大就可以通过线段树，线段树的母数组是每一个数字剩下的还能出现的次数。求出最大值，那我们就能等价于求和为 k-1 的前缀和的位置。这里的查找我们就可以用二分法查找答案。



# AC 代码
```cpp
#include <iostream>
using namespace std;
int a[N];
int h[N];dev
int c[N];
void add(int a,int b){
	for(int i=a;i<=n;i+=lowbit(i)){
		t[i]+=b;
	}
}
int search(int a){
	int sum=0;
	for(int i=a;i>=0;i-=lowbit(i)){
		sum+=t[i];
	}
	return sum;
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i ++ ) scanf("%d", &h[i]);

    for (int i = 1; i <= n; i ++ ) tr[i] = lowbit(i);

    for (int i = n; i; i -- )
    {
        int k = h[i] + 1;
        int l = 1, r = n;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (sum(mid) >= k) r = mid;
            else l = mid + 1;
        }
        ans[i] = r;
        add(r, -1);
    }

    for (int i = 1; i <= n; i ++ ) printf("%d\n", ans[i]);

    return 0;
}
```
# 备注
