/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 * 二叉树前序遍历，迭代法
 * 69 / 69 test cases passed.
 * Runtime: 0 ms
 * Memory Usage: 5.8 MB
 */

#include <stdio.h>
#include <stdlib.h>

#define EMPTY_STACK -1

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 *  Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *result = NULL;
    int stack_cnt = EMPTY_STACK, result_cnt = -1;
    struct TreeNode *ranger = NULL, **stack = NULL;

    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    result = (int*)malloc(sizeof(int) * 101);
    stack = (struct TreeNode **)malloc(sizeof(struct TreeNode*) * 101);

    ranger = root;
    while (1) {
        if (ranger == NULL && stack_cnt == EMPTY_STACK) {
            break;
        }

        if (ranger == NULL) {
            // 能进入该判断的只有一种可能，就是当前节点是其父节点的右子节点，
            // 但是当前节点为空，需要弹栈获取一个可用的节点。弹出来的节点的
            // 数据已经输出了，所以只要往右走即可。
            ranger = stack[stack_cnt--];
            ranger = ranger->right;
            continue;
        }

        result[++result_cnt] = ranger->val;

        // 往左走
        if (ranger->left != NULL) {
            stack[++stack_cnt] = ranger;
            ranger = ranger->left;
            continue;
        }

        // 往右走
        ranger = ranger->right;
    }

    // result_cnt 从0开始，所以要加一。
    *returnSize = result_cnt + 1;
    free(stack);

    return result;
}

