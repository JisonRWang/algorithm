/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 * 二叉树中序遍历，迭代法
 * 70 / 70 test cases passed
 * Runtime: 2 ms
 * Memory Usage: 5.9 MB
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
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
        // 退出循环的条件，这样写可读性强些。
        if (ranger == NULL && stack_cnt == EMPTY_STACK) {
            break;
        }

        if (ranger == NULL) {
            // 进入该判断只有一种情况就是当前节点是其父节点的右子节点，
            // 但是该节点是个空节点，所以需要弹栈获得一个有效节点。
            // 注意，每次弹栈之后，都只能往右走！！！
            ranger = stack[stack_cnt--];
            result[++result_cnt] = ranger->val;
            ranger = ranger->right;
            continue;
        }

        // 往左走
        if (ranger->left != NULL) {
            // 将ranger压栈，
            // 注意，只有左子树不为空的时候才需要压栈！
            stack[++stack_cnt] = ranger;
            ranger = ranger->left;
            continue;
        }

        // 左边走到头儿，输出当前节点的数据，
        // 注意此时的ranger用不着再次入栈，因为其
        // 数据已经输出，该节点已经没用了。
        result[++result_cnt] = ranger->val;

        // 往右走
        ranger = ranger->right;
    }

    // result_cnt 从0开始，所以要加一。
    *returnSize = result_cnt + 1;
    free(stack);

    return result;
}
