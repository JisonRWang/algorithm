/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡 二叉搜索树。
* 高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树
* 31 / 31 test cases passed
* Runtime: 20 ms
* Memory Usage: 16.2 MB
*/
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    int mid;
    struct TreeNode *ranger = NULL;

    if (numsSize == 0) {
        return NULL;
    }

    ranger = (struct TreeNode *)malloc(sizeof(struct TreeNode));

    mid = numsSize / 2;
    ranger->val = nums[mid];
    ranger->left = NULL;
    ranger->right = NULL;

    // 特殊情况处理
    if (numsSize == 1) {
        return ranger;
    }

    // 一般情况
    ranger->left = sortedArrayToBST(nums, mid);
    ranger->right = sortedArrayToBST(nums + mid + 1, numsSize - mid - 1);

    return ranger;
}
