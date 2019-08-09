/* Huffman code
*  哈夫曼编码
*      未来要编写的是“范式哈夫曼编码”，与普通哈夫曼编码不同的是，范式哈夫曼编码
严格要求编码时使用的二叉树是一棵左浅右深的二叉树，见
https://blog.csdn.net/jison_r_wang/article/details/52074278
*      因为是第一次编写哈夫曼编码，所以这里不完全套用范式哈夫曼编码的所有性质，
这里只在保证哈夫曼编码基本性质的情况下让整个哈夫曼树呈现左浅右深的形状。
*      从树根往下看，是深度；从叶子节点往上看，是高度；
*      因为哈夫曼树是一棵满二叉树（即，除叶子节点外，每个节点都保证有两个子节点），所以
有该性质：  哈夫曼树的所有节点个数 = 2 * 叶子节点数 - 1
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

typedef struct huffman_node
{
    char ch;
    int freq;
    int high; // 从当前节点开始，到以当前节点为根节点的子树底部的高度(以右边高度为准，因为要求左低右高)
    int left;
    int right;
}huffman_node_s;

typedef unsigned int u32;

static int g_mem_index;
static huffman_node_s* g_memory;

static int* g_heap;

// 因为哈夫曼树是一棵满二叉树，每个内部节点都有两个子节点，所以不用担心两个子节点之一不存在的情况
void encoding(int mem_node_idx, u32 code, u32 code_len)
{
    int i;

    // 递归基，找到叶子节点
    if (0 == g_memory[mem_node_idx].high) {
        printf("%c: ", g_memory[mem_node_idx].ch);
        for (i = 0; i < code_len; i++) {
            printf("%d", (code & (1 << i)) >> i);
        }
        printf("\n");
        return;
    }

    // code不能超过32位（即哈夫曼树深度不能超过32层），否则无法表示
    // 编码时，root往下那一位在code最低位，叶子结点上面那一位在code最高位（方便生成code与输出code）
    encoding(g_memory[mem_node_idx].left, code|(0<<code_len), code_len + 1);
    encoding(g_memory[mem_node_idx].right, code|(1<<code_len), code_len + 1);

    return;
}

void heap_swap(int heap_dad_index, int heap_child_index)
{
    int tmp_mem_idx;

    tmp_mem_idx = g_heap[heap_child_index];
    g_heap[heap_child_index] = g_heap[heap_dad_index];
    g_heap[heap_dad_index] = tmp_mem_idx;

    return;
}

void insert_heap(int mem_node_index)
{
    int i;
    int dad, heap_size;

    // TODO 检查堆是否已满

    heap_size = g_heap[0];
    g_heap[++heap_size] = mem_node_index;
    g_heap[0] = heap_size;

    // 上滤(tips: 小根堆)
    for (i = heap_size; (i >> 1) >= 1; i = dad) {
        dad = i >> 1;
        if (g_memory[g_heap[i]].freq >= g_memory[g_heap[dad]].freq) {
            break;
        }
        heap_swap(dad, i);
    }

    return;
}

// 返回peak位置携带的g_memory索引
int delete_heap_peak()
{
    int i, child, heap_size;
    int mem_index_in_peak = -1;

    // 校验
    heap_size = g_heap[0];
    if (heap_size <= 0) {
        goto label_ret;
    }

    mem_index_in_peak = g_heap[1];
    g_heap[1] = g_heap[heap_size];
    g_heap[0] = --heap_size;
    if (heap_size <= 0) {
        goto label_ret;
    }

    // 下滤(tips: 小根堆)
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_memory[g_heap[child]].freq >= g_memory[g_heap[child+1]].freq) {
            child++;
        }

        if (g_memory[g_heap[i]].freq <= g_memory[g_heap[child]].freq) {
            break;
        }
        heap_swap(i, child);
    }

label_ret:
    return mem_index_in_peak;
}

// 返回哈夫曼树根节点的g_memory索引
int build_huffman_tree()
{
    int new_node_idx = -1;
    int tmp_mem_idx1, tmp_mem_idx2;

    // 堆中没有节点
    if (0 == g_heap[0]) {
        goto label_ret;
    }
    // 处理堆中只有一个节点的情况
    if (1 == g_heap[0]) {
        new_node_idx = delete_heap_peak();
        goto label_ret;
    }

    while (g_heap[0] > 1) {
        tmp_mem_idx1 = delete_heap_peak();
        tmp_mem_idx2 = delete_heap_peak();

        // 分配节点
        new_node_idx = g_mem_index++;
        g_memory[new_node_idx].freq = g_memory[tmp_mem_idx1].freq + g_memory[tmp_mem_idx2].freq;

        // 深度大的作为右子节点
        g_memory[new_node_idx].left = tmp_mem_idx1;
        g_memory[new_node_idx].right = tmp_mem_idx2;
        if (g_memory[tmp_mem_idx2].high < g_memory[tmp_mem_idx1].high) {
            g_memory[new_node_idx].left = tmp_mem_idx2;
            g_memory[new_node_idx].right = tmp_mem_idx1;
        }

        // 更新新节点的深度
        g_memory[new_node_idx].high = g_memory[g_memory[new_node_idx].right].high + 1;

        // 该判断成立，说明新节点就是哈弗曼树的根节点，该节点不用再插入堆中
        if (0 == g_heap[0]) {
            break;
        }

        insert_heap(new_node_idx);
    }

label_ret:
    return new_node_idx;
}

// 按照哈夫曼编码，这里建的是小根堆
void create_heap()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_memory[g_heap[child]].freq >= g_memory[g_heap[child+1]].freq) {
                child++;
            }

            if (g_memory[g_heap[j]].freq <= g_memory[g_heap[child]].freq) {
                break;
            }
            heap_swap(j, child);
        }
    }

    return;
}

static void init(int n)
{
    int i, cnt;

    // 统计未来要生成的哈夫曼树的所有节点个数
    cnt = 2 * n - 1;

    g_mem_index = 0;
    g_memory = new huffman_node_s[cnt];
    for (i = 0; i < cnt; i++) {
        g_memory[i].ch = '\0';
        g_memory[i].freq = 0;
        g_memory[i].high = 0;   // 叶子节点的高度都是0
        g_memory[i].left = -1;
        g_memory[i].right = -1;
    }

    // 第0个元素统计堆中节点的数量；进行哈夫曼编码时，堆中的元素个数是减少的，所以开n+1个空间就够
    // g_heap中每个元素记录的是g_memory的索引
    g_heap = new int[n + 1];

    return;
}

static void end()
{
    delete[] g_memory;
    delete[] g_heap;

    return;
}

void huffman_code()
{
    int i, n;
    int mem_root_idx;

    // 输入叶子节点个数，即要参与编码的字符及其出现频率
    scanf("%d", &n);
    if (n < 1) {
        cout << "Wrong input: n = " << n << endl;
        return;
    }

    init(n);

    // 读取输入缓冲区的\n字符
    getchar();
    for (i = 1; i <= n; i++) {
        scanf("%c %d", &g_memory[g_mem_index].ch, &g_memory[g_mem_index].freq);
        getchar();
        g_heap[i] = g_mem_index;
        g_mem_index++;
    }
    g_heap[0] = n;

    printf("--------------------------------\n");

    create_heap();
    mem_root_idx = build_huffman_tree();
    encoding(mem_root_idx, 0, 0);

    end();
    return;
}