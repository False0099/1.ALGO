# 从头到尾打印链表

## 题目描述
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

## 样例 #1

### 样例输入 #1

```
head = [1,3,2]
```

### 样例输出 #1

```
[2,3,1]
```

## 题解
法一：我们把所有的值都拿出来放到一个数组中，再反转数组
法二：我们用递归的方法，先进入再打印即可

## 代码
```cpp
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> ans;

        while (head != NULL) {
            ans.push_back(head->val);
            head = head->next;
        }
        
        reverse(ans.begin(), ans.end());

        return ans;
    }
};
```