/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 52 / 52 test cases passed
* Runtime: 341 ms
* Memory Usage: 75.8 MB
* 这道题要小心，不是简单将“最大深度”翻转就可以的，
* 主要注意不要将表示“空节点”的0深度也计入最小深度
* 的判断中。
*/
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int minDepth(struct TreeNode* root){
    int depth, depth_left, depth_right;

    depth = depth_left = depth_right = 0x7fffffff;

    // 递归基
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        // 当前节点是叶子节点
        return 1;
    }
    
    // 对于退化成链表的二叉树，其最小程度就是当前“链表”的长度，
    // 要区分出这种情况。深度为1表明这个方向只有当前节点，
    // depth_left 和 depth_right不可能同时为0。
    depth_left = minDepth(root->left);
    if (depth_left == 0) {
        // 左边叶子节点为空，不计入深度
        depth_left = 0x7fffffff;
    }
    depth_right = minDepth(root->right);
    if (depth_right == 0) {
        // 右边叶子节点为空，不计入深度
        depth_right = 0x7fffffff;
    }
    depth = (depth_left < depth_right) ? depth_left : depth_right;
    return depth + 1;
}
