/* ��Ŀ
*      �ر���-K
*   ����
*      С��ѧϰ�˹�������֮���Լ������̰���㷨�����������о͹����ˡ��ر��롷����⡣
*      С���룺�Ƕѵ��㷨��ʲô���أ�Ϊ�˽��С�յ��ɻ󣬵���ʦί��С�������������Ŀ����
*   ����
*      ��һƪ���£����°���n�ֵ��ʣ����ʵı�Ŵ�1��n����i�ֵ��ʵĳ��ִ���Ϊw[i]�����ڣ�
*����Ҫ��һ��k���ƴ�����ֻ����0,1,...,k�6�11�Ĵ���s[i]���滻��i�ֵ��ʣ�ʹ����������Ҫ��,
*          ���������1��i<j��n������s[i]����s[j]��ǰ׺�����Ҫ����Ϊ�˱�������ԣ���
*      ��������Ƕ�ÿ������ѡ����ʵ�s[j]��ʹ���滻��������ܳ��ȣ�����Ϊ���е��ʳ��ִ������滻����k
*���ƴ��ĳ��ȳ˻����ܺͣ���С���������С���ȡ�
*      �ַ���S[1]���������賤��Ϊn������Ϊ�ַ���S[2]��ǰ׺�����ҽ�����S[2]�ĳ��Ȳ�С�� 
*n����S[1]��S[2]ǰn���ַ�����ɵ��ַ�����ȫ��ͬ��
*   �����ʽ
*      ��һ����������n��k����2�е���n+1�У���i+1�а���һ��������w[i]����ʾ��i�ֵ��ʵĳ��ִ�����
*   �����ʽ
*      ��ʾ��ƪ�����ر�������̳���
*   ��������1
*      5 3
*      1
*      3
*      5
*      10
*      3
*   �������1
*      29
*   ����
*      ���� 100% �����ݣ�����1��n��(3*(10^5)), 2��k��10, 1��w[i]��(10^9)
*      ���� 40% �����ݣ�����n��3000
*      ���� 35% �����ݣ�����k=2
*   ��ʾ
*      ̰��˼·���ر�����Ŀ��ͬ����Ҫ˼�����ǣ��������󹹽��Ĺ�������Ϊ��k�����أ�
*   ����˼·
*      Ϊ����k������Ϊ��k���������벹����Ƶ��Ϊ0��Ҷ�ӽڵ㣬ʹ��������Ϊ��k������������Ҷ�ӽڵ㣬����
ÿ���ڵ㶼��k���ӽڵ㣩��
*      ��0������ʽ�� r = [k - n % (k - 1)] % (k - 1)
*   �ҵ�˼·
*      ����ĿҪ�󣬲����������ÿ���ַ��ı��룬ֻҪ�����ÿ���ַ���k�����ֵ���Ȳ����������Ƶ������ͼ���
*      ����Ŀ���ƣ���������£�k��������300000~600000���ڵ㣬����Ҫ300000����
*      ԭʼ�Ĺ��������Ƕ��������������ı��������Ƕ������롣����Ҫ��k�����룬������k������
*      ����������k�������������ǲ�Ҷ�ӽڵ��ǲ㲹����Ƶ��Ϊ0��Ҷ�ӽڵ㣬�������������㲹0�����磬��6������
Ƶ�ʷֱ�Ϊ123458�ĵ㣬���һ��������������0������£��������������̰��ԭ��������ӦΪ��
            23
             |         \
a            8         15
                    /   |   \  
b                  4    5    6                       
                           / | \
c                         1  2  3
*      ��a�㲹0�����˷�һ���ַ��ı��룬��������һ���ַ�����ֻ��һ�������ʾ������Ϊ�����λ�ò�0������ֻ��
������ַ��ŵ������㣬��������㲹0�ǲ�����ġ������ķ�ʽ������c�㲹0���������Գ������ÿһ��Ϊ��Ҫ�����
�ַ����б��롣
*      ÿ�κϲ�������(k-1)���㣬�������k�����������Ӧ��ֻʣ��һ����
*      �������Ĳ�0��ʽ�� r = [k - 1 - n%(k-1) + 1]%(k-1)
*      ��ʽ���ͣ�
*          (k-1)�� ÿ�κϲ�������ȡ����С��k����Ȼ��������1��������ÿ�κϲ���������(k-1)��
*        n%(k-1)�� ��ǰ�ܽڵ������(k-1)���������̱�ʾ���˶��ٴκϲ�������������ʾʣ�µĽڵ�����
*  k-1 - n%(k-1)�� ��Ҫ�����ٸ�0���ܴﵽ(k-1)���ڵ�
*k-1 - n%(k-1)+1�� ��k����Ҫ�󾭹�һ�������ĺϲ������Ҫǡ��ʣ��һ���ڵ㣬�����һ���ǲ�ʣ�µ�����ڵ�
*    [...]%(k-1)�� ����ֶ�(k-1)ȡ�࣬��Ϊ�˴���n%(k-1)ǡ��Ϊ0ʱ��ֻ�������ٵ�0�ĸ���
*   �ҵĲ�0����
*       [n%(k-1) + r]%(k-1) = 1
*       ���ͣ�
*          ��Ϊ��ÿ�κϲ�������(k-1)���㣬�������k�����������Ӧ��ֻʣ��һ���㡱������k������������n%(k-1) = 1
*          ���������ʽ��r��0��ʼ��μ�1������ֱ��ʹ�Ⱥ�����Ľ������1����˵�����r������С��0����
*          ˵���˾������n%(k-1)������1����ôn%(k-1)�ټӶ����ٶ�(k-1)ȡ�����1
*   �ҵĽڵ��������㹫ʽ
*       ��k������ӵ�е��ܽڵ����Ϊ M = (n*k-1) / (k-1)�����У�n���Ѿ�����0������n%(k-1)=1��ֵ
*       ����ԭʼ����������k=2����ô�ɸù�ʽ�Ƶ�������2������ʽ���� M=2*n-1
*       �Ƶ����̣�
*           ��k������������ÿ�κϲ�k���㲢����1���㣬���ʣ��1��������ʡ�
*           ��k�������е�=n+�����ɵĵ�
*           n-k+1-k+1-k+1-.....-k+1 = 1
*     n-(k-1)-(k-1)-(k-1)-...-(k-1) = 1
*                          n-t(k-1) = 1
*                                 t = (n-1)/(k-1)��t���������ɵ�ĸ���
*           M = n+t 
*           M = (n*k-1)/(k-1)
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

// 1��n��(3*(10^5)), 2��k��10, 1��w[i]��(10^9)
typedef struct tree_node
{
    u32 leaf; // ʵ�ʵ�Ҷ�ӽڵ㣬��1��ʼ����Ҷ�ӽڵ�����ڲ�0��Ҷ�ӽڵ������ֵΪ0
    u64 freq; // 1��w[i]��(10^9)��������Ҫ��Ƶ�����ۼӣ�Ϊ��ֹ��ת����������ʹ��u64
    //u32 high; // ÿ��������Լ�����������Ҷ�ӽڵ�ĸ߶ȣ�Ҷ�ӽڵ�ĸ߶�Ϊ0��������Ժ󲻺�Ū����ʱ������
    u32 child[10]; // ��¼�ӽڵ���ڴ����������60����ڵ㣬��ֻ����u32��child[0~9]Ϊ����Ĳ�
}tree_node_s;

static u32* g_heap;
static u32 g_mem_index;
static tree_node_s* g_memory;

// 1��n��(3*(10^5)), 2��k��10, 1��w[i]��(10^9)
static int g_N;
static int g_K;

// �������ʹ��u64����Ȼ���յĽ���ᷭת
static u64 g_len = 0;

static void swap_heap(int heap_dad, int heap_child)
{
    u32 tmp_mem_index;

    tmp_mem_index = g_heap[heap_child];
    g_heap[heap_child] = g_heap[heap_dad];
    g_heap[heap_dad] = tmp_mem_index;

    return;
}

// �з��գ����k��������̫�࣬ʹ�õݹ����ջ�������������ջ��
// �������������kҲ��������ܻ���Щ
static void calculate(u32 mem_node_index, u32 code_len)
{
    int i, k;

    // �ݹ������Ϊ����k����������ǰ׺��������Ҷ�ӽڵ�ֻ���ǲ�0�ڵ��ʵ�ʵ�Ҷ�ӽڵ㣩
    if (0 == g_memory[mem_node_index].freq) { // ���ڲ�0�Ľڵ�
        return;
    }
    if (0 != g_memory[mem_node_index].leaf) { // ʵ�ʵ�Ҷ�ӽڵ�
        g_len += g_memory[mem_node_index].freq * code_len;
        return;
    }

    // ��Ϊ����k���������Գ�Ҷ�ӽڵ������ÿ���ڵ㶼��k���ӽڵ�
    k = g_K;
    for (i = 0; i < k; i++) {
        calculate(g_memory[mem_node_index].child[i], code_len + 1);
    }

    return;
}

// tips: С����
static void insert_heap(u32 mem_node_index)
{
    int i, dad;
    u32 heap_size;

    //TODO ��ü��һ���Ƿ�Խ��
    heap_size = g_heap[0];
    g_heap[++heap_size] = mem_node_index;
    g_heap[0] = heap_size;

    // ����
    for (i = heap_size; (i >> 1) >= 1; i = dad) {
        dad = i >> 1;
        if (g_memory[g_heap[i]].freq >= g_memory[g_heap[dad]].freq) {
            break;
        }
        swap_heap(dad, i);
    }

    return;
}

// tips: С����
// ���ع��ڶ��еı������ڵ�������g_memory��������
static u32 delete_heap_peak()
{
    int i, child, heap_size;
    u32 mem_node_index;

    heap_size = g_heap[0];
    if (heap_size < 1) {
        printf("There is not any item in heap.\n");
        return 0xffffffff;
    }

    mem_node_index = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    // ����
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size && 
            g_memory[g_heap[child]].freq >= g_memory[g_heap[child+1]].freq) {
            child++;
        }
        if (g_memory[g_heap[i]].freq <= g_memory[g_heap[child]].freq) {
            break;
        }
        swap_heap(i, child);
    }

    return mem_node_index;
}

// ����k�������ڵ��g_memory����
static u32 build_k_tree()
{
    int i;
    int k;
    u32 tmp_mem_idx, new_node_idx = 0xffffffff; 

    k = g_K;
    if (g_heap[0] < k) {
        return new_node_idx;
    }

    // ��Ϊ�Ѿ���0�ˣ����������һ�κϲ�֮ǰ��һ���ܹ��Ӷ���ȡ��k����
    while (g_heap[0] >= k) {
        // �����½ڵ�
        new_node_idx = g_mem_index++;

        // �ϲ�
        for (i = 0; i < k; i++) {
            tmp_mem_idx = delete_heap_peak();
            g_memory[new_node_idx].freq += g_memory[tmp_mem_idx].freq;
            g_memory[new_node_idx].child[i] = tmp_mem_idx;
        }

        // �ϲ������ɵĽڵ㼴k�������ڵ�
        if (0 == g_heap[0]) {
            break;
        }
        insert_heap(new_node_idx);
    }

    return new_node_idx;
}

// tips: С����
static void create_heap()
{
    int i, j, child;
    u32 heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_memory[g_heap[child]].freq >= g_memory[g_heap[child + 1]].freq) {
                child++;
            }
            if (g_memory[g_heap[j]].freq <= g_memory[g_heap[child]].freq) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

static void init()
{
    int i, r, cnt;

    scanf("%d %d", &g_N, &g_K);
    getchar();

    // tips: ��0��ָ������Ƶ��Ϊ0�Ľڵ�
    // ���㲹0���� r = [k - n % (k - 1)] % (k - 1)
    r = (g_K - g_N % (g_K - 1)) % (g_K - 1);

    // M = (n*k-1)/(k-1)
    cnt = ((g_N + r) * g_K - 1) / (g_K - 1);

    //TODO �ڴ����ʧ�ܼ��
    g_mem_index = 0;
    g_memory = new tree_node_s[cnt];
    for (i = 0; i < cnt; i++) {
        g_memory[i].leaf = 0;
        g_memory[i].freq = 0;
    }

    g_heap = new u32[g_N + r + 1];
    g_heap[0] = g_N + r;
    
    // ����0�ڵ��������
    for (i = 1; i <= r; i++) {
        g_heap[i] = g_mem_index++;
    }

    // ����ڵ㲢��ʵ�ʵ�Ҷ�ӽڵ��������
    for (i = 1; i <= g_N; i++) {
        scanf("%llu", &g_memory[g_mem_index].freq);
        getchar();
        g_memory[g_mem_index].leaf = i;

        // ����ǰr+1���㣨��0����¼���нڵ������1~r��Ԫ���ǲ�0�ڵ㣩
        g_heap[r + i] = g_mem_index++;
    }

    return;
}

static void end()
{
    delete[] g_heap;
    delete[] g_memory;
    return;
}

void k_coding()
{
    int root_idx;

    init();

    create_heap();
    root_idx = build_k_tree();
    calculate(root_idx, 0);
    printf("%llu\n", g_len);

    end();
    return;
}