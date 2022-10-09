/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 思路：用迭代法将每条路径上的节点放到栈里，
* 通过扫描栈获得路径描述。一条完整路径是要
* 走到叶子节点的，而不是中间节点！！！
* 为了能够在向上回溯的时候区分左右子树是否已经处理完，
* 将struct TreeNode 包进另一个结构体里。
* 100个节点的二叉树，最多64条路径。
* 208 / 208 test cases passed
* Runtime: 0 ms
* Memory Usage: 6.7 MB
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct ShellTreeNode {
    struct TreeNode *node;
    unsigned short left;
    unsigned short right;
};

#define EMPTY_STACK -1

char* create_path(struct ShellTreeNode *stack, int stack_cnt) 
{
    int len;

    // path like "1->2->5"
    char *path = (char *)malloc(stack_cnt * 6);
    *path = '\0';

    // sprintf(char *str, const char *format, ...)
    for (int i = 0; i < stack_cnt; i++) {
        len = strlen(path);

        if (i == stack_cnt - 1) {
            sprintf(path + len, "%d", stack[i].node->val);
            break;
        }
        sprintf(path + len, "%d->", stack[i].node->val);
    }

    return path;
}

/**
* Note: The returned array must be malloced, assume caller calls free().
*/
char ** binaryTreePaths(struct TreeNode* root, int* returnSize){
    char **paths = NULL;
    int stack_cnt = EMPTY_STACK;
    struct TreeNode *ranger = NULL;
    struct ShellTreeNode *stack = NULL;
    
    *returnSize = 0;
    paths  = (char **)malloc(sizeof(char *) * 64);
    stack = (struct ShellTreeNode *)malloc(sizeof(struct ShellTreeNode) * 101);
    
    // 按照题目要求，root不会为NULL，至少有一个节点
    ranger = root;
    while (1) {
        if (NULL != ranger) {
            // 将当前节点压栈
            stack[++stack_cnt].node = ranger;
            stack[stack_cnt].left   = 0;
            stack[stack_cnt].right  = 0;

            // 往左走
            stack[stack_cnt].left = 1;
            if (NULL != ranger->left) {
                ranger = ranger->left;
                continue;
            }

            // 往右走
            stack[stack_cnt].right = 1;
            if (NULL != ranger->right) {
                ranger = ranger->right;
                continue;
            }

            // 当前节点为叶子节点，扫描整个栈获取路径数据，只有到了叶子节点才说明这条路走到头。
            // 注意stack_cnt是从0开始的。
            paths[*returnSize] = create_path(stack, stack_cnt + 1);
            *returnSize += 1;

            // 这条路径结束，通过弹栈的方式向上回溯，这里是弹出该叶子节点
            stack_cnt--;
        }
        
        // 如果上面的判断成立，则这里说明到了该叶子节点的父节点；
        // 如果上面的判断不成立，说明进来的是个空节点，而且也没压栈。
        // 由于都是先从左边走，所以stack[stack_cnt].left肯定是1，这里只要判断右边就好
        while (EMPTY_STACK != stack_cnt && 1 == stack[stack_cnt].right) {
            // 弹栈
            stack_cnt--;
            if (EMPTY_STACK == stack_cnt) {
                break;
            }
        }
        if (EMPTY_STACK == stack_cnt) {
            break;
        }

        // 走到这里，说明回溯到了之前只往左面走而没有往右边走的节点，要接着往右走
        stack[stack_cnt].right = 1;
        ranger = stack[stack_cnt].node->right;
    }

    free(stack);
    
    return paths;
}

int main()
{
    int returnSize;
    struct TreeNode root;
    struct TreeNode son_left;
    struct TreeNode son_right;
    struct TreeNode grand_son;
    char **paths;

    root.val = 1;
    root.left = &son_left;
    root.right = &son_right;

    son_left.val = 2;
    son_left.left = NULL;
    son_left.right = &grand_son;

    son_right.val = 3;
    son_right.left = NULL;
    son_right.right = NULL;

    grand_son.val = 5;
    grand_son.left = NULL;
    grand_son.right = NULL;

    paths = binaryTreePaths(&root, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", paths[i]);
    }
    
    return 0;
}
