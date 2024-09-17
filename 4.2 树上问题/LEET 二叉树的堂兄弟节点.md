# 知识点
  ## [[BFS]] [[2023秋主要学科/数据结构与算法/树]]
# 题目
 
``给你一棵二叉树的根 root ，请你将每个节点的值替换成该节点的所有堂兄弟节点值的和。

``如果两个节点在树中有相同的深度且它们的父节点不同，那么它们互为堂兄弟。

``请你返回修改值之后，树的根 root 。

``注意，一个节点的深度指的是从树根节点到这个节点经过的边数。
![[Pasted image 20230416131337.png]]
``解释上图展示了初始的二叉树和修改每个节点的值之后的二叉树。
``- 值为 5 的节点没有堂兄弟，所以值修改为 0 。
``- 值为 4 的节点没有堂兄弟，所以值修改为 0 。
``- 值为 9 的节点没有堂兄弟，所以值修改为 0 。
``- 值为 1 的节点有一个堂兄弟，值为 7 ，所以值修改为 7 。
``- 值为 10 的节点有一个堂兄弟，值为 7 ，所以值修改为 7 。
``- 值为 7 的节点有两个堂兄弟，值分别为 1 和 10 ，所以值修改为 11 。

# 思路
·我们先来思考堂兄弟节点的和要怎么算，我们可以先算出每一层里的总和，然和再用总和减去自己和与自己同父节点的节点的值，算出来的结果就是我们要的二叉树的堂兄弟节点。
·因此，我们需要做两次遍历，第一次算出来每一层的所有节点的值的和。第二次就减去自己和自己亲兄弟的节点的值。
·二叉树遍历怎么做到清晰的划分出每一层，我们就可以在遍历的时候，不是直接 push 到 q 里面而是 push 到一个暂存的容器里面，等到这一层的遍历完成后，再去把这个容器里的赋给q
# AC 代码
```cpp
/**

 * Definition for a binary tree node.

 * struct TreeNode {

 *     int val;

 *     TreeNode *left;

 *     TreeNode *right;

 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}

 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

 * };

 */

class Solution {

public:
	TreeNode *replaceValueInTree(TreeNode *root) {
        root->val = 0;
        vector<TreeNode *> q = {root};
        while (!q.empty()) {
            vector<TreeNode *> nxt;
            int next_level_sum = 0; // 下一层的节点值之和
            for (auto node: q) {//
                if (node->left) {
                    nxt.push_back(node->left);
                    next_level_sum += node->left->val;
                }
                if (node->right) {
                    nxt.push_back(node->right);
                    next_level_sum += node->right->val;
                }
            }

            // 再次遍历，更新下一层的节点值
            for (auto node: q) {
                int child_sum = (node->left ? node->left->val : 0) +
                                (node->right ? node->right->val : 0);
                if (node->left) node->left->val = next_level_sum - child_sum;
                if (node->right) node->right->val = next_level_sum - child_sum;
            }
            q = move(nxt);//一层一层的放进去
        }
        return root;
    }
};


};
```
# 备注
