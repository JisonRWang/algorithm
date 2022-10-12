/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
* 思路：使用“右中左”的中序遍历方法，可以得到一个从大
* 到小的有序数组，最小的差值就存在于临近的两个数，不可
* 能出现在相隔几个数的地方，而且这样做差得到的结果一定
* 是正的，可以不用计算“绝对值”了。本题降低了难度，所
* 有值都大于零，可以按照“左中右”的遍历顺序去计算，全
* 部都是负值，但我还是按照自己的方式来，这样就可以无论
* 正负了，更通用。
* 188 / 188 test cases passed
* Runtime: 24 ms
* Memory Usage: 13.9 MB
*/
#include <stdio.h>
#include <stdlib.h>

#define EMPTY_STACK -1

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int g_prev_val, g_diff;

void cal_diff(int val) 
{
    int tmp;

    // 初始化
    if (0x7fffffff == g_prev_val) {
        g_prev_val = val;
        // 从大到小，所以差值肯定是正数
        g_diff = -1;
        return;
    }
    if (-1 == g_diff) {
        g_diff = g_prev_val - val;
        g_prev_val = val;
        return;
    }

    tmp = g_prev_val - val;
    if (tmp < g_diff) {
        g_diff = tmp;
    }
    g_prev_val = val;

    return;
}

int getMinimumDifference(struct TreeNode* root){
    int stack_cnt = EMPTY_STACK;
    struct TreeNode **stack = NULL;
    struct TreeNode *ranger = NULL;

    // 按照题目要求，不会进这里，至少有两个节点
    if (NULL == root) {
        return 0;
    }

    stack = (struct TreeNode **)malloc(sizeof(struct TreeNode *) * 10010);

    ranger = root;
    g_prev_val = 0x7fffffff;
    while (1) {
        if (NULL == ranger && EMPTY_STACK == stack_cnt) {
            break;
        }

        if (NULL == ranger) {
            // 从栈里弹出来一个，处理
            ranger = stack[stack_cnt--];
            cal_diff(ranger->val);

            // 往左走
            ranger = ranger->left;
            continue;
        }
        
        // 往右走
        if (NULL != ranger->right) {
            stack[++stack_cnt] = ranger;
            ranger = ranger->right;
            continue;
        }

        // 中间
        cal_diff(ranger->val);

        // 往左走
        ranger = ranger->left;
    }

    return g_diff;
}
