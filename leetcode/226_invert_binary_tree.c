/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 思路：仍然使用自底向上的方案。
* 77 / 77 test cases passed
* Runtime: 0 ms
* Memory Usage: 6 MB
*/
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* invertTree(struct TreeNode* root){
    struct TreeNode *tmp;

    // 递归基
    if (NULL == root) {
        return root;
    }
    if (NULL == root->left && NULL == root->right) {
        // 叶子节点
        return root;
    }
    
    // 普通节点
    tmp = root->right;
    root->right = invertTree(root->left);
    root->left  = invertTree(tmp);

    return root;
}
