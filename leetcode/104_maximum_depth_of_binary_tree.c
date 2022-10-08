/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 使用深度优先。
* 39 / 39 test cases passed
* Runtime: 13 ms
* Memory Usage: 8.1 MB
*/

#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxDepth(struct TreeNode* root){
    int depth_left, depth_right;

    // 递归基
    if (root == NULL) {
        return 0;
    }
    
    // “加一”表示加上当前节点的深度.
    depth_left = maxDepth(root->left);
    depth_right = maxDepth(root->right);
    return (depth_left > depth_right) ? (depth_left + 1) : (depth_right + 1);
}
