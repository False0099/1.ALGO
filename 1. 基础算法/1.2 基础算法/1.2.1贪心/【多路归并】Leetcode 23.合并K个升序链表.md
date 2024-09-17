给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

**示例 1：**

**输入：**lists = [[1,4,5],[1,3,4],[2,6]]
**输出：**[1,1,2,3,4,4,5,6]
**解释：**链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

**示例 2：**

**输入：**lists = []
**输出：**[]

**示例 3：**

**输入：**lists = [[]]
**输出：**[]

**提示：**

- `k == lists.length`
- `0 <= k <= 10^4`
- `0 <= lists[i].length <= 500`
- `-10^4 <= lists[i][j] <= 10^4`
- `lists[i]` 按 **升序** 排列
- `lists[i].length` 的总和不超过 `10^4`

## 题解
我们这一题是我们多路归并问题的模板，什么是多路归并呢？就是给定我们 K 个有序的数组，要我们求出我们最后 K 个数组合并后我们的链表是什么。
这里，我们就可以用我们的优先队列，或者说我们的堆来解决，我们先维护当前每个链表没有被合并的元素的最前面放到一个小根堆中，然后我们自定义比较排序，每次取出堆顶的元素，把该链表的头节点链接到排序链表中，再把下一个结点 push 进去，如果有空姐点就跳过。
```cpp
class Solution {
public:
    struct Status {
        int val;
        ListNode *ptr;
        bool operator < (const Status &rhs) const {
            return val > rhs.val;
        }
    };

    priority_queue <Status> q;

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        for (auto node: lists) {
            if (node) q.push({node->val, node});
        }
        ListNode head, *tail = &head;
        while (!q.empty()) {
            auto f = q.top(); q.pop();
            tail->next = f.ptr; 
            tail = tail->next;
            if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
        }
        return head.next;
    }
};

作者：力扣官方题解
链接：https://leetcode.cn/problems/merge-k-sorted-lists/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```