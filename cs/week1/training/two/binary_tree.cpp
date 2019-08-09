/* 题目
*     二叉树
*  描述
*     给定一个1到n的排列，按顺序依次插入到一棵二叉排序树中，请你将这棵二叉树前序遍历和后序遍历输出。
*  输入
*     第一行一个整数n。
*     接下来一行表示为n个整数，代表1到n的一个排列。
*  输出
*     输出所建成的二叉树的前序遍历和后序遍历。
*  输入样例
*     10
*     2 6 9 3 5 7 10 8 4 1
*  输出样例
*     2 1 6 3 5 4 9 7 8 10
*     1 4 5 3 8 7 10 9 6 2
*   限制
*     对于50%的数据，1 ≤ n ≤ 100；
*     对于100%的数据，1 ≤ n ≤ 100000。
*     保证建成的树的高度不超过50。
*   时间：2 sec
*   空间：256 MB
*   提示
*      [二叉树的操作基本都是递归操作，只要想想如何在一个节点上判断是朝着左孩子走还是朝着右孩子走就行了。]
*   我的思路
*      所谓二叉排序树，即二叉查找树，如果直接生成，会非常不平衡；想要完美的做出这道题，必须考虑平衡的策略
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

typedef struct Node
{
    int val;
    int left;   // 记录数组索引即可
    int right;
}Node_s;

static int g_num; // 输入数据总数
static int* g_data_input = nullptr;
static Node_s* g_tree_nodes = nullptr;
static int g_index = 0;

// 先序遍历
void preorder_print(int index)
{
    // 递归基
    if (-1 == g_tree_nodes[index].left && -1 == g_tree_nodes[index].right) {
        cout << g_tree_nodes[index].val << " ";
        return;
    }

    cout << g_tree_nodes[index].val << " ";
    
    if (-1 != g_tree_nodes[index].left) {
        preorder_print(g_tree_nodes[index].left);
    }
    if (-1 != g_tree_nodes[index].right) {
        preorder_print(g_tree_nodes[index].right);
    }

    return;
}

// 后序遍历
void posteriori_print(int index)
{
    // 递归基
    if (-1 == g_tree_nodes[index].left && -1 == g_tree_nodes[index].right) {
        cout << g_tree_nodes[index].val << " ";
        return;
    }

    if (-1 != g_tree_nodes[index].left) {
        posteriori_print(g_tree_nodes[index].left);
    }
    if (-1 != g_tree_nodes[index].right) {
        posteriori_print(g_tree_nodes[index].right);
    }

    cout << g_tree_nodes[index].val << " ";

    return;
}

// 无法保证树的高度不超过50，极端情况下很可能退化成类似链表（虽然这里用索引而不是指针，但是和链表原理一样）
// 虽然用了索引，但依然无法弥补退化成链表时的本质缺陷，还是应该考虑平衡二叉树
void insert_node(int val)
{
    int i;

    if (0 == g_tree_nodes[0].val) {
        // 初始化根节点
        g_tree_nodes[g_index].val = val; //相当于分配一块内存作为根节点
        g_index++; 
        return;
    }

    i = 0;
    while (1) {
        if (val < g_tree_nodes[i].val) {
            if (-1 == g_tree_nodes[i].left) {
                g_tree_nodes[g_index].val = val; // 相当于取一块内存作为节点
                g_tree_nodes[i].left = g_index; // 相当于把节点挂到树上
                g_index++;
                break;
            }
            i = g_tree_nodes[i].left;
            continue;
        }
        // 大于等于都走右子树
        if (-1 == g_tree_nodes[i].right) {
            g_tree_nodes[g_index].val = val; 
            g_tree_nodes[i].right = g_index; 
            g_index++;
            break;
        }
        i = g_tree_nodes[i].right;
        continue;
    }

    return;
}

void create_binary_tree()
{
    int i;

    for (i = 0; i < g_num; i++) {
        // 逐个读取输入数据并构造二叉树
        insert_node(g_data_input[i]);
    }

    return;
}

static void init()
{
    int i;

    g_data_input = new int[g_num];
    g_tree_nodes = new Node_s[g_num];
    for (i = 0; i < g_num; i++) {
        // 输入数据不小于1
        g_tree_nodes[i].val = 0;
        g_tree_nodes[i].left = -1;
        g_tree_nodes[i].right = -1;
    }

    return;
}

static void end()
{
    delete[] g_data_input;
    delete[] g_tree_nodes;
    return;
}

void binary_tree()
{
    int i;

    scanf("%d", &g_num);
    if (0 == g_num) {
        cout << "Wrong input." << endl;
        return;
    }

    init();
    for (i = 0; i < g_num; i++) {
        scanf("%d", &g_data_input[i]);
    }

    create_binary_tree();

    preorder_print(0);
    cout << endl;
    posteriori_print(0);

    end();

    return;
}