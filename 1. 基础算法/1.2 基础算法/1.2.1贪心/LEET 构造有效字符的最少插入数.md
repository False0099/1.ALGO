# 知识点
  ## [[贪心]]
# 题目
 给你一个字符串 word ，你可以向其中任何位置插入 "a"、"b" 或 "c" 任意次，返回使 word 有效需要插入的最少字母数。

如果字符串可以由 "abc" 串联多次得到，则认为该字符串有效。
# 思路
·令 si 表示 word 里第 i 个字符，若 $s_{i+1}<s_{i}$, 说明 $s_{i}与s_{i+1}$ 属于两个不同的 abc。满足 $s_{i+1}<s_{i}$ 的下标一共有 k 个，那么插入后一定有 k+1 个 abc，再用总共的字母减去现有的字母，我们就能得到最后的要补充的个数
·
# AC 代码
```cpp
class Solution {
public:
    int addMinimum(string word) {
        int n = word.size();
        int ans = 1;
        for (int i = 1; i < n; i++) if (word[i] <= word[i - 1]) ans++;
        return ans * 3 - n;
    }
};

作者：tsreaper
链接：https://leetcode.cn/problems/minimum-additions-to-make-valid-string/solution/tan-xin-by-tsreaper-wf2e/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
# 备注
