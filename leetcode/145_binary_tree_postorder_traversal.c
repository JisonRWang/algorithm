/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 * 二叉树后序遍历，迭代法
 * 由于结构体的缺陷，只能通过将先序遍历的“中左右”改为
 * “中右左”，再将结果数组反转，才能得到后序遍历的结果。
 * 68 / 68 test cases passed
 * Runtime: 7 ms
 * Memory Usage: 6.1 MB
 */

#include <stdio.h>
#include <stdlib.h>

#define EMPTY_STACK -1

// 这种结构体无法直接使用迭代法，因为成员太少，无法记录向左向右的路径信息，
// 导致无法分清什么时候该输出节点的数据。除非带上两个路径标记。
struct TreeNode {
    int val;
    int left_routine;
    int right_routine;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 *  Note: The returned array must be malloced, assume caller calls free().
 */
int* postorderTraversal(struct TreeNode* root, int* returnSize){
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
            ranger = stack[stack_cnt--];
            ranger = ranger->left;
            continue;
        }

        result[++result_cnt] = ranger->val;

        if (ranger->right != NULL) {
            stack[++stack_cnt] = ranger;
            ranger = ranger->right;
            continue;
        }

        ranger = ranger->left;
    }

    for (int i = 0, j = result_cnt; i < j; i++, j--) {
        int tmp = result[i];
        result[i] = result[j];
        result[j] = tmp;
    }

    // result_cnt 从0开始，所以要加一。
    *returnSize = result_cnt + 1;
    free(stack);

    return result;
}

