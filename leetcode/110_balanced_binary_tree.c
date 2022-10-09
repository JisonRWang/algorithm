/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 给定一个二叉树，判断它是否是高度平衡的二叉树。
* 一棵高度平衡二叉树定义为：
* 一个二叉树每个节点的左右两个子树的高度差的绝对值不超过 1 。
* 思路：自底向上，先一口气扎到左边最底下，然后往上逐级判断是否
* 平衡，当找到一个不平衡的子树，就返回到根，不看其他子树了，从而节省时间。
* 228 / 228 test cases passed
* Runtime: 16 ms
* Memory Usage: 9.9 MB
*/

#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool balanced_depth(struct TreeNode *root, int *depth)
{
    int depth_left, depth_right;
    bool left_balanced, right_balanced;

    // 递归基
    if (root == NULL) {
        *depth = 0;

        // 空节点肯定是“平衡的”
        return true;
    }
    
    left_balanced  = balanced_depth(root->left,  &depth_left);
    if (!left_balanced) {
        // 发现不平衡就直接返回，不用看右子树了，节省时间
        return false;
    }
    right_balanced = balanced_depth(root->right, &depth_right);
    if (!right_balanced) {
        // 发现不平衡就直接返回，不往下走了，节省时间
        return false;
    }

    // 左右子树都平衡，则根据左右子树各自的深度来判断当前节点是否平衡
    *depth = depth_left - depth_right;
    if (*depth < -1 || *depth > 1) {
        // 不平衡，直接返回，*depth这里仅仅作为一个中间变量，laze to create a new variable
        return false;
    }

    // “加一”表示加上当前节点的深度.
    *depth = (depth_left > depth_right) ? depth_left + 1 : depth_right + 1;
    return true;
}

bool isBalanced(struct TreeNode* root){
    int depth;
    return balanced_depth(root, &depth);
}
