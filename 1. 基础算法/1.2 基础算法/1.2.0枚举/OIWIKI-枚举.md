一个数组中的数互不相同，求其中和为 0 的数对的个数。

我们这一题的思路就是简单的枚举，因为我们要求 $a+b=0$,肯定要先固定其中一个，然后才能去计算我们的另外一个。这一点我们可以通过我们的桶来统计在某个数之前一共出现了多少个数。然后我们就可以固定一个点作为结尾，然后统计个数即可

```cpp
bool met[MAXN * 2];
memset(met, 0, sizeof(met));
for (int i = 0; i < n; ++i) { 
	if (met[MAXN - a[i]]) ++ans; 
	met[MAXN + a[i]] = true; 
}
```