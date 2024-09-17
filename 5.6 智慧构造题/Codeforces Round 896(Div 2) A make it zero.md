#位运算 #特殊方案 #操作数限制 
## 题目描述
During Zhongkao examination, Reycloer met an interesting problem, but he cannot come up with a solution immediately. Time is running out! Please help him.

Initially, you are given an array a consisting of n≥2 integers, and you want to change all elements in it to 00.

In one operation, you select two indices l and r (1≤l≤r≤n) and do the following:

- Let s=$al⊕al+1⊕…⊕ar$, where ⊕⊕ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR);
- Then, for all l≤i≤r, replace ai with s.

You can use the operation above in any order at most 88 times in total.

Find a sequence of operations, such that after performing the operations in order, all elements in a are equal to 00. It can be proven that the solution always exists.

## 输入格式


The first line of input contains a single integer t (1≤t≤500) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer n (2≤n≤100) — the length of the array a.

The second line of each test case contains n integers a1,a2,…,an (0≤ai≤100) — the elements of the array a.
## 输出格式
For each test case, in the first line output a single integer k (0≤k≤8) — the number of operations you use.

Then print k lines, in the i-th line output two integers li and ri (1≤li≤ri≤n) representing that you select li and ri in the i-th operation.

Note that you do not have to minimize k. If there are multiple solutions, you may output any of them.


## 样例 #1

### 样例输入 #1

```
6
4
1 2 3 0
8
3 1 4 1 5 9 2 6
6
1 5 4 1 4 7
5
0 0 0 0 0
7
1 1 9 9 0 1 8
3
100 100 0

```

### 样例输出 #1

```
1
1 4
2
4 7
1 8
6
1 2
3 4
5 6
1 3
4 6
1 6
0
4
1 2
6 7
3 4
6 7
1
1 2

```

## 提示
这一题我们只需要**分奇偶讨论**，如果一个数是偶数，我们只需要从第一个到最后一个同时选两次即可。如果一个数是奇数，那么我们只需要从第一个到倒数第二个连续选两次，倒数第二个和最后一个再分别选两次即可。
## 题解


## 代码
```cpp
```cpp
ll n,a[105];
inline void qfl_zzz(){
    n=read();
    for(ll i=1;i<=n;++i)a[i]=read();
    if(n%2==0){
        writen(2);
        writet(1),writen(n);
        writet(1),writen(n);
        return;
    }
    writen(4);
    writet(1),writen(n-1);
    writet(1),writen(n-1);
    writet(n-1),writen(n);
    writet(n-1),writen(n);
}
```
```