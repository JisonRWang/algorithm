/* ��Ŀ
*     ������
*  ����
*     ����һ��1��n�����У���˳�����β��뵽һ�ö����������У����㽫��ö�����ǰ������ͺ�����������
*  ����
*     ��һ��һ������n��
*     ������һ�б�ʾΪn������������1��n��һ�����С�
*  ���
*     ��������ɵĶ�������ǰ������ͺ��������
*  ��������
*     10
*     2 6 9 3 5 7 10 8 4 1
*  �������
*     2 1 6 3 5 4 9 7 8 10
*     1 4 5 3 8 7 10 9 6 2
*   ����
*     ����50%�����ݣ�1 �� n �� 100��
*     ����100%�����ݣ�1 �� n �� 100000��
*     ��֤���ɵ����ĸ߶Ȳ�����50��
*   ʱ�䣺2 sec
*   �ռ䣺256 MB
*   ��ʾ
*      [�������Ĳ����������ǵݹ������ֻҪ���������һ���ڵ����ж��ǳ��������߻��ǳ����Һ����߾����ˡ�]
*   �ҵ�˼·
*      ��ν����������������������������ֱ�����ɣ���ǳ���ƽ�⣻��Ҫ��������������⣬���뿼��ƽ��Ĳ���
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

typedef struct Node
{
    int val;
    int left;   // ��¼������������
    int right;
}Node_s;

static int g_num; // ������������
static int* g_data_input = nullptr;
static Node_s* g_tree_nodes = nullptr;
static int g_index = 0;

// �������
void preorder_print(int index)
{
    // �ݹ��
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

// �������
void posteriori_print(int index)
{
    // �ݹ��
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

// �޷���֤���ĸ߶Ȳ�����50����������ºܿ����˻�������������Ȼ����������������ָ�룬���Ǻ�����ԭ��һ����
// ��Ȼ��������������Ȼ�޷��ֲ��˻�������ʱ�ı���ȱ�ݣ�����Ӧ�ÿ���ƽ�������
void insert_node(int val)
{
    int i;

    if (0 == g_tree_nodes[0].val) {
        // ��ʼ�����ڵ�
        g_tree_nodes[g_index].val = val; //�൱�ڷ���һ���ڴ���Ϊ���ڵ�
        g_index++; 
        return;
    }

    i = 0;
    while (1) {
        if (val < g_tree_nodes[i].val) {
            if (-1 == g_tree_nodes[i].left) {
                g_tree_nodes[g_index].val = val; // �൱��ȡһ���ڴ���Ϊ�ڵ�
                g_tree_nodes[i].left = g_index; // �൱�ڰѽڵ�ҵ�����
                g_index++;
                break;
            }
            i = g_tree_nodes[i].left;
            continue;
        }
        // ���ڵ��ڶ���������
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
        // �����ȡ�������ݲ����������
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
        // �������ݲ�С��1
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