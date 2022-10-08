/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 * 相同的二叉树，既要保证树的结构相同，也要保证树上每个节点的值相同。
 * 本题采用深度优先遍历的递归方式。
 * 60 / 60 test cases passed
 * Runtime: 3 ms
 * Memory Usage: 5.8 MB
 */

#include <stdlib.h>

typedef int bool;
#define true  1
#define false 0

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isSameTree(struct TreeNode* p, struct TreeNode* q){
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

    // 尾递归
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
