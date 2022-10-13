/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 104 / 104 test cases passed
* Runtime: 6 ms
* Memory Usage: 8.2 MB
*/
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int g_max_diameter;

int cal_depth(struct TreeNode *root)
{
    int diameter;
    int depth, left_depth, right_depth;

    // 递归基
    if (NULL == root) {
        return 0;
    }
    if (NULL == root->left && NULL == root->right) {
        return 1;
    }

    // 计算最大深度
    left_depth = cal_depth(root->left);
    right_depth = cal_depth(root->right);
    depth = (left_depth > right_depth) ? left_depth + 1 : right_depth + 1;

    // 当前直径 = 左边节点数 + 当前节点 + 右边节点数 - 1 
    diameter = left_depth + 1 + right_depth - 1;
    if (g_max_diameter < diameter) {
        g_max_diameter = diameter;
    }

    return depth;
}

int diameterOfBinaryTree(struct TreeNode* root){
    g_max_diameter = 0;

    cal_depth(root);
    
    return g_max_diameter;
}
