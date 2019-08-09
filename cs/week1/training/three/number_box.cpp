/* ��Ŀ
*     ���ֺ���
*  ����
*     ����һ�����ӣ�����������������Ҳ���Դ�����ȡ������
*     ��ʼʱ�������ǿյģ���������� Q ��������������Ϊ���ࣺ
*         ���������ѯ�ʺ������Ƿ������ x���������������� x ���������
*         ɾ��������ѯ�ʺ������Ƿ������ x�����������ȡ�� x��
*     ����ÿ������������Ҫ����Ƿ�ɹ������ɾ����
*  ����
*     ��һ��һ�������� Q����ʾ����������
*     ������ Q ����������ÿ��������ÿ�� 2 ���ÿո�����ķǸ����� op,x 
*         op ��ʾ�������ͣ�op=1 ���ʾ����һ�����������op=2 ���ʾ����һ��ɾ������
*          x ����������������йأ��������Ŀ������
*  ���
*     ��˳������в������������ÿ���������һ�У�
*     ����ɹ��������Succeeded�����������ţ������ʧ���������Failed�����������ţ���
*  ��������
*     6
*     1 100
*     1 100
*     2 100
*     1 200
*     2 100
*     2 200
*  �������
*     Succeeded
*     Failed
*     Succeeded
*     Succeeded
*     Failed
*     Succeeded
*  ���ݷ�Χ
*     ���� 60% �����ݣ���֤ x<10^5��
*     ���� 100% �����ݣ���֤ x<10^18��Q��5*10^5��
*     �����������ݣ���֤ op��{1,2}��
*  ʱ�����ƣ�10 sec
*  �ռ����ƣ�256 MB
*  ��ʾ
*     [���� x ��С�����������ֻ��Ҫ�������¼ÿ�����Ƿ��ں����Ｔ�ɡ�]
*     [���� x �ϴ����������ǿɲ�������ʲô���������ǡ���С���أ����������ϣ��Ŷ��]
*  �ҵ�˼·
*     ��Ȼ�ù�ϣ���ܻ���ֳ�ͻ����������ǻ��ֱ���������ʡ�����ռ䣬��������»��������ʹ�õĿռ���ͬ
*     �������²�����ּ����������ô�ù�ϣ�Ǿ��Կ��Խ��ܵ�
*     �ؼ����������ƹ�ϣ����
*     Q�ķ�Χ������500000�����ÿ����������Ӧ��ͬ�����ݣ���ô���Ҳ��500000�����������ܿռ��ϣ��Ŀռ�
����500000���У���500000��Ԫ�ص�ָ������
*     ����hash������ https://blog.csdn.net/shiyongyang/article/details/78079109
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct operation
{
    u32 opt;
    u64 val;
}operation_s;

typedef struct chain_node
{
    u64 val;
    struct chain_node* next;
}chain_node_s;

// ѡ��һ����ʮ�����ҵ�������Ϊ��ϣ����
static u64 g_hash = 517619ULL;

static u32 g_opt_cnt;
static operation_s* g_opt_mem;
static chain_node_s** g_hash_table;

static void insert_opt(int opt_idx, u64 val) 
{
    int idx;
    bool output;
    chain_node_s *cur, *next;

    output = true;
    if (opt_idx == g_opt_cnt - 1) {
        output = false;
    }

    idx = val % g_hash;

    if (NULL == g_hash_table[idx]) {
        g_hash_table[idx] = new chain_node_s;
        g_hash_table[idx]->val = val;
        g_hash_table[idx]->next = NULL;

        printf("Succeeded");
        if (output) {
            printf("\n");
        }
        return;
    }

    cur = g_hash_table[idx];
    while (NULL != cur) {
        next = cur->next;

        if (val != cur->val) {
            cur = next;
            continue;
        }
        printf("Failed");
        if (output) {
            printf("\n");
        }

        return;
    }

    cur = new chain_node_s;
    cur->val = val;
    cur->next = g_hash_table[idx];
    g_hash_table[idx] = cur;
    printf("Succeeded");
    if (output) {
        printf("\n");
    }

    return;
}

static void delete_opt(int opt_idx, u64 val)
{
    int idx;
    bool output;
    chain_node_s* cur, * next, * prev;

    output = true;
    if (opt_idx == g_opt_cnt - 1) {
        output = false;
    }

    idx = val % g_hash;

    if (NULL == g_hash_table[idx]) {
        printf("Failed");
        if (output) {
            printf("\n");
        }

        return;
    }

    prev = g_hash_table[idx];
    cur = g_hash_table[idx];
    while (NULL != cur) {
        next = cur->next;

        if (val != cur->val) {
            prev = cur;
            cur = next;
            continue;
        }
        
        if (cur == g_hash_table[idx]) {
            g_hash_table[idx] = next;
        }
        else {
            prev->next = next;
        }
        cur->next = NULL;
        delete cur;
        printf("Succeeded");
        if (output) {
            printf("\n");
        }

        return;
    }

    printf("Failed");
    if (output) {
        printf("\n");
    }

    return;
}

static void process()
{
    int i;

    for (i = 0; i < g_opt_cnt; i++) {
        if (1 == g_opt_mem[i].opt) {
            insert_opt(i, g_opt_mem[i].val);
            continue;
        }
        delete_opt(i, g_opt_mem[i].val);
    }

    return;
}

static void init()
{
    int i;

    scanf("%u", &g_opt_cnt);
    getchar();

    g_opt_mem = new operation_s[g_opt_cnt];
    for (i = 0; i < g_opt_cnt; i++) {
        scanf("%u %llu", &g_opt_mem[i].opt, &g_opt_mem[i].val);
        getchar();
    }

    g_hash_table = new chain_node_s * [g_hash];
    for (i = 0; i < g_hash; i++) {
        g_hash_table[i] = NULL;
    }

    return;
}

static void free_chain_in_hash_table()
{
    int i;
    chain_node_s *next, *cur;

    for (i = 0; i < g_hash; i++) {
        cur = g_hash_table[i];
        while (NULL != cur) {
            next = cur->next;
            delete cur;
            cur = next;
        }
        g_hash_table[i] = NULL;
    }

    return;
}

static void end()
{
    delete[] g_opt_mem;

    free_chain_in_hash_table();

    delete[] g_hash_table;

    return;
}

void number_box()
{
    init();

    process();

    end();

    return;
}