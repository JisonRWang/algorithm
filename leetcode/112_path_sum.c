/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 
* 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。
* 如果存在，返回 true ；否则，返回 false 。
* 叶子节点 是指没有子节点的节点。
* 思路：用深度优先搜索，一口气尽可能干到底。
* 117 / 117 test cases passed
* Runtime: 7 ms
* Memory Usage: 8.2 MB
*/
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool hasPathSum(struct TreeNode* root, int targetSum){
    // 递归基
    if (root == NULL) {
        return false;
    }
    targetSum -= root->val;
    if (root->left == NULL && root->right == NULL) {
        // 叶子节点
        return targetSum == 0 ? true : false;    
    }
    
    // 非叶子节点
    if (root->left != NULL && hasPathSum(root->left, targetSum)) {
        return true;
    }
    if (root->right != NULL && hasPathSum(root->right, targetSum)) {
        return true;
    }
    
    return false;
}
