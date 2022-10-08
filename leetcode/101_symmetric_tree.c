/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 * 基本思路：有点类似判断两棵二叉树是否相同，只不过
 * 需要将root按照left和right劈成两棵树，并且这两棵树
 * 是对称的而不再是相同的，所谓“对称”就是一棵树的左边
 * 和另一棵树的右边是一样的。
 * 198 / 198 test cases passed.
 * Runtime: 3 ms
 * Memory Usage: 7 MB
 */

#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef int bool;
#define true  1
#define false 0

bool isSymmetricSame(struct TreeNode *p, struct TreeNode *q)
{
    // 递归基
    if (p == NULL && q == NULL) {
        return true;
    }
    if (p == NULL || q == NULL) {
        return false;
    }
    if (p->val != q->val) {
        return false;
    }

    return isSymmetricSame(p->left, q->right) && isSymmetricSame(p->right, q->left);
}

bool isSymmetric(struct TreeNode* root){
    return isSymmetricSame(root->left, root->right);
}
