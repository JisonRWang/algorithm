/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 用中序遍历法遍历二叉搜索树，会得到一个从小到大排列的有序
* 数列，而且如果里面有重复的数据的话，会在这个数列里紧挨着
* 出现，例如“1 2 2 2 4 5 7 7 8 9 9 9 9 ”。利用这个性质，
* 结合迭代法中序遍历二叉树，就可以解决此题。
* 23 / 23 test cases passed
* Runtime: 10 ms
* Memory Usage: 10.9 MB
*  faster than 97.67%
*/
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define EMPTY_STACK -1

int g_patrol, g_patrol_cnt, g_max_cnt;

int find(int val, int *result, int num)
{
    // 初始化
    if (0 == g_max_cnt) {
        g_patrol = val;
        g_patrol_cnt = 1;
        g_max_cnt = g_patrol_cnt;

        return num;
    }

    if (val == g_patrol) {
        g_patrol_cnt++;

        return num;
    }

    if (g_patrol_cnt < g_max_cnt) {
        // 丢弃原来的值，并更新为当前值
        g_patrol = val;
        g_patrol_cnt = 1;
    } else if (g_patrol_cnt == g_max_cnt) {
        result[num++] = g_patrol;
        g_patrol = val;
        g_patrol_cnt = 1;
    } else {
        // g_patrol_cnt > g_max_cnt
        num = 0;
        result[num++] = g_patrol;
        g_max_cnt = g_patrol_cnt;

        g_patrol = val;
        g_patrol_cnt = 1;
    }

    return num;
}

/**
 *  * Note: The returned array must be malloced, assume caller calls free().
 *   */
int* findMode(struct TreeNode* root, int* returnSize){
    int *result = NULL;
    int stack_cnt = EMPTY_STACK;
    struct TreeNode *ranger = NULL;
    struct TreeNode **stack = NULL;

    *returnSize = 0;
    if (NULL == root) {
        return NULL;
    }

    result = (int *)malloc(sizeof(int) * 10000);
    stack  = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * 10000);

    g_max_cnt    = 0;
    g_patrol_cnt = 0;
    ranger       = root;
    while (1) {
        // 退出迭代
        if (NULL == ranger && EMPTY_STACK == stack_cnt) {
            if (g_patrol_cnt == g_max_cnt) {
                result[(*returnSize)++] = g_patrol; 
                break;
            }
            if (g_patrol_cnt > g_max_cnt) {
                *returnSize = 0;
                result[(*returnSize)++] = g_patrol;
            }
            break;
        } 

        if (NULL == ranger) {
            // 该节点是其父节点的空的右子节点，且其父节点已经处理完，不在栈里
            ranger = stack[stack_cnt--];

            // 中间
            *returnSize = find(ranger->val, result, *returnSize);
            
            ranger = ranger->right;
            continue;
        }

        // 往左走
        if (NULL != ranger->left) {
            stack[++stack_cnt] = ranger;
            ranger = ranger->left;
            continue;
        }

        // 中间，即当前节点
        *returnSize = find(ranger->val, result, *returnSize);
        
        // 往右走，右子节点可能是空节点
        ranger = ranger->right;
    }

    free(stack);
    return result;
}
