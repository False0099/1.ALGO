# 反转链表
## 题目描述
给定单链表的头节点 `head` ，请反转链表，并返回反转后的链表的头节点。


## 样例 #1

### 样例输入 #1

```
head = [1,2,3,4,5]
```

### 样例输出 #1

```
[5,4,3,2,1]
```

## 提示




## 题解
思路一：递归的方法，通过改变我们的指针来让我们能够快速修改
思路二：先把数据用栈存储下来，然后再反向构建我们的新链表
## 代码
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr)
            return nullptr;
        ListNode* curr = head;
        stack<ListNode*> store;
        // 所有节点入栈
        while (curr != nullptr) {
            store.push(curr);
            curr = curr->next;
        }
        curr = store.top();
        store.pop();
        ListNode* newHead = curr; // 反转链表的头节点
        while (!store.empty()) {
            curr->next = store.top();
            store.pop();
            curr = curr->next;
        }
        curr->next = nullptr;   // 原头节点变成尾节点，指针域置空
        return newHead;
    }
};
```