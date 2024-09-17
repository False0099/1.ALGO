给你一个下标从 **0** 开始的字符串数组 `words` 。

定义一个 **布尔** 函数 `isPrefixAndSuffix` ，它接受两个字符串参数 `str1` 和 `str2` ：

- 当 `str1` 同时是 `str2` 的前缀（prefix ）和后缀（ suffix  ）时，`isPrefixAndSuffix(str1, str2)` 返回 `true`，否则返回 `false`。

例如，`isPrefixAndSuffix("aba", "ababa")` 返回 `true`，因为 `"aba"` 既是 `"ababa"` 的前缀，也是 `"ababa"` 的后缀，但是 `isPrefixAndSuffix("abc", "abcd")` 返回 `false`。

以整数形式，返回满足 `i < j` 且 `isPrefixAndSuffix(words[i], words[j])` 为 `true` 的下标对 `(i, j)` 的 **数量** 。

## 样例：
**输入：**words = ["a","aba","ababa","aa"]
**输出：**4
**解释：**在本示例中，计数的下标对包括：
i = 0 且 j = 1 ，因为 isPrefixAndSuffix("a", "aba") 为 true 。
i = 0 且 j = 2 ，因为 isPrefixAndSuffix("a", "ababa") 为 true 。
i = 0 且 j = 3 ，因为 isPrefixAndSuffix("a", "aa") 为 true 。
i = 1 且 j = 2 ，因为 isPrefixAndSuffix("aba", "ababa") 为 true 。
因此，答案是 4 。

## 题解
我们本题的思路一是相对来说也可以想到，就是我们建两颗 TRIE 树，一颗我们顺序建树，另一颗我们考虑逆序建树。

但是这样，我们有一个问题，就是我们不能保证题目中要求的“同一个字符串”

于是，我们就需要考虑用我们的一个 trie 同时维护我们的前缀和后缀，也就是说，我们每一个节点，同时存储我们的前缀和后缀。

把每个字符串 $s$ 视作一个 pair 列表：

$$
[(s[0],s[n-1]),(s[1],s[n-2]),(s[2],s[n-3]),\cdots,(s[n-1],s[0])
$$
 只要这个 pair 列表是另一个字符串 $t$ 的 pair 列表的前缀，那么 $s$ 就是 $t$ 的前后缀。

```cpp
struct Node {

    unordered_map<int, Node*> son;

    int cnt = 0;

};

  

class Solution {

public:

    long long countPrefixSuffixPairs(vector<string> &words) {

        long long ans = 0;

        Node *root = new Node();

        for (string &s: words) {

            int n = s.length();

            auto cur = root;

            for (int i = 0; i < n; i++) {

                int p = (int) (s[i] - 'a') << 5 | (s[n - 1 - i] - 'a');

                if (cur->son[p] == nullptr) {

                    cur->son[p] = new Node();

                }

                cur = cur->son[p];

                ans += cur->cnt;

            }

            cur->cnt++;

        }

        return ans;

    }

};

  

作者：灵茶山艾府

链接：https://leetcode.cn/problems/count-prefix-and-suffix-pairs-ii/solutions/2644160/z-han-shu-zi-dian-shu-pythonjavacgo-by-e-5c2v/

来源：力扣（LeetCode）

著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```