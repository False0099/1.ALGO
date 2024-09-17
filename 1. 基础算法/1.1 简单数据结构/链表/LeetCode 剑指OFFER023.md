# 两个链表的第一个重合节点
## 题目描述
给定两个单链表的头节点 `headA` 和 `headB` ，请找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 `null` 。


## 样例 #1

### 样例输入 #1

```
intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3

```

### 样例输出 #1

```
Intersected at '8'
```

## 提示




## 题解
方法一：用哈希表来判重，如果走到了一个相同的节点，那么就返回这个节点，否则就返回 0
方法二：双指针，一个快指针，一个慢指针，走完就回到开头，如果走到相同节点，就一定会再一个周期内相遇，否则就没有共同节点
方法三：我们可以考虑用求 LCA 的方法来求这一题，但多少有点大病。
## 代码
```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *> visited;
        ListNode *temp = headA;
        while (temp != nullptr) {
            visited.insert(temp);
            temp = temp->next;
        }
        temp = headB;
        while (temp != nullptr) {
            if (visited.count(temp)) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode *pA = headA, *pB = headB;
        while (pA != pB) {
            pA = pA == nullptr ? headB : pA->next;
            pB = pB == nullptr ? headA : pB->next;
        }
        return pA;
    }
};

```