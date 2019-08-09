/* Huffman code
*  ����������
*      δ��Ҫ��д���ǡ���ʽ���������롱������ͨ���������벻ͬ���ǣ���ʽ����������
�ϸ�Ҫ�����ʱʹ�õĶ�������һ����ǳ����Ķ���������
https://blog.csdn.net/jison_r_wang/article/details/52074278
*      ��Ϊ�ǵ�һ�α�д���������룬�������ﲻ��ȫ���÷�ʽ������������������ʣ�
����ֻ�ڱ�֤����������������ʵ��������������������������ǳ�������״��
*      ���������¿�������ȣ���Ҷ�ӽڵ����Ͽ����Ǹ߶ȣ�
*      ��Ϊ����������һ������������������Ҷ�ӽڵ��⣬ÿ���ڵ㶼��֤�������ӽڵ㣩������
�и����ʣ�  �������������нڵ���� = 2 * Ҷ�ӽڵ��� - 1
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

typedef struct huffman_node
{
    char ch;
    int freq;
    int high; // �ӵ�ǰ�ڵ㿪ʼ�����Ե�ǰ�ڵ�Ϊ���ڵ�������ײ��ĸ߶�(���ұ߸߶�Ϊ׼����ΪҪ������Ҹ�)
    int left;
    int right;
}huffman_node_s;

typedef unsigned int u32;

static int g_mem_index;
static huffman_node_s* g_memory;

static int* g_heap;

// ��Ϊ����������һ������������ÿ���ڲ��ڵ㶼�������ӽڵ㣬���Բ��õ��������ӽڵ�֮һ�����ڵ����
void encoding(int mem_node_idx, u32 code, u32 code_len)
{
    int i;

    // �ݹ�����ҵ�Ҷ�ӽڵ�
    if (0 == g_memory[mem_node_idx].high) {
        printf("%c: ", g_memory[mem_node_idx].ch);
        for (i = 0; i < code_len; i++) {
            printf("%d", (code & (1 << i)) >> i);
        }
        printf("\n");
        return;
    }

    // code���ܳ���32λ��������������Ȳ��ܳ���32�㣩�������޷���ʾ
    // ����ʱ��root������һλ��code���λ��Ҷ�ӽ��������һλ��code���λ����������code�����code��
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

    // TODO �����Ƿ�����

    heap_size = g_heap[0];
    g_heap[++heap_size] = mem_node_index;
    g_heap[0] = heap_size;

    // ����(tips: С����)
    for (i = heap_size; (i >> 1) >= 1; i = dad) {
        dad = i >> 1;
        if (g_memory[g_heap[i]].freq >= g_memory[g_heap[dad]].freq) {
            break;
        }
        heap_swap(dad, i);
    }

    return;
}

// ����peakλ��Я����g_memory����
int delete_heap_peak()
{
    int i, child, heap_size;
    int mem_index_in_peak = -1;

    // У��
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

    // ����(tips: С����)
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

// ���ع����������ڵ��g_memory����
int build_huffman_tree()
{
    int new_node_idx = -1;
    int tmp_mem_idx1, tmp_mem_idx2;

    // ����û�нڵ�
    if (0 == g_heap[0]) {
        goto label_ret;
    }
    // �������ֻ��һ���ڵ�����
    if (1 == g_heap[0]) {
        new_node_idx = delete_heap_peak();
        goto label_ret;
    }

    while (g_heap[0] > 1) {
        tmp_mem_idx1 = delete_heap_peak();
        tmp_mem_idx2 = delete_heap_peak();

        // ����ڵ�
        new_node_idx = g_mem_index++;
        g_memory[new_node_idx].freq = g_memory[tmp_mem_idx1].freq + g_memory[tmp_mem_idx2].freq;

        // ��ȴ����Ϊ���ӽڵ�
        g_memory[new_node_idx].left = tmp_mem_idx1;
        g_memory[new_node_idx].right = tmp_mem_idx2;
        if (g_memory[tmp_mem_idx2].high < g_memory[tmp_mem_idx1].high) {
            g_memory[new_node_idx].left = tmp_mem_idx2;
            g_memory[new_node_idx].right = tmp_mem_idx1;
        }

        // �����½ڵ�����
        g_memory[new_node_idx].high = g_memory[g_memory[new_node_idx].right].high + 1;

        // ���жϳ�����˵���½ڵ���ǹ��������ĸ��ڵ㣬�ýڵ㲻���ٲ������
        if (0 == g_heap[0]) {
            break;
        }

        insert_heap(new_node_idx);
    }

label_ret:
    return new_node_idx;
}

// ���չ��������룬���ｨ����С����
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

    // ͳ��δ��Ҫ���ɵĹ������������нڵ����
    cnt = 2 * n - 1;

    g_mem_index = 0;
    g_memory = new huffman_node_s[cnt];
    for (i = 0; i < cnt; i++) {
        g_memory[i].ch = '\0';
        g_memory[i].freq = 0;
        g_memory[i].high = 0;   // Ҷ�ӽڵ�ĸ߶ȶ���0
        g_memory[i].left = -1;
        g_memory[i].right = -1;
    }

    // ��0��Ԫ��ͳ�ƶ��нڵ�����������й���������ʱ�����е�Ԫ�ظ����Ǽ��ٵģ����Կ�n+1���ռ�͹�
    // g_heap��ÿ��Ԫ�ؼ�¼����g_memory������
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

    // ����Ҷ�ӽڵ��������Ҫ���������ַ��������Ƶ��
    scanf("%d", &n);
    if (n < 1) {
        cout << "Wrong input: n = " << n << endl;
        return;
    }

    init(n);

    // ��ȡ���뻺������\n�ַ�
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