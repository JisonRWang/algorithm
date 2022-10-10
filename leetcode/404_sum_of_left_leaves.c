/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 100 / 100 test cases passed
* Runtime: 3 ms
* Memory Usage: 6.5 MB
* 本题最重要的地方在于，第一次让我意识到用递归的方式
* 解决二叉树问题时，不一定非得递归到叶子节点，可以递
* 归到其父节点就结束任务。
*/
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int sumOfLeftLeaves(struct TreeNode* root){
    int sum = 0;

    // 递归到叶子结点的父节点就行，这次不递归到底（叶子节点）了
    if (NULL == root) {
        return sum;
    }
    
    if (NULL != root->left) {
        // 判断左子节点是否为叶子节点
        if (NULL == root->left->left && NULL == root->left->right) {
            sum += root->left->val;
        }
        else {
            sum += sumOfLeftLeaves(root->left);
        }
    }
    if (NULL != root->right) {
        // 如果右子节点是叶子结点，就不计数
        if (NULL != root->right->left || NULL != root->right->right) {
            sum += sumOfLeftLeaves(root->right);
        }
    }

    return sum;
}
