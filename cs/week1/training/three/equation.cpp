/* ��Ŀ
*     ��ʽ
*  ����
*     ��n��������m������ȡ��򡰲���ȡ���Լ�������������ж��Ƿ����һ�ָ�ֵ������������m��Լ��������
*  ����
*     ��һ��һ������T����ʾ����������
*     ����������T�����ݣ�����ÿ�����ݣ�
*         ��һ������������n,m����ʾ����������Լ�������ĸ�����
*         ������m�У�ÿ����������a,b,e����ʾ��a�������͵�b�������Ĺ�ϵ��
*             ��e=0���ʾ ��a������ ������ ��b������ ��
*             ��e=1���ʾ ��a������ ����   ��b������
*  ���
*     ���T�У���i�б�ʾ��i�����ݵĴ𰸡�����i�����ݴ���һ�ַ��������"Yes"���������"No"�����������ţ���
*  ��������1
*     2
*     5 5
*     1 2 1
*     2 3 1
*     3 4 1
*     1 4 1
*     2 5 0
*     3 3
*     1 2 1
*     2 3 1
*     1 3 0
*  �������1
*     Yes
*     No
*  ����1����
*     һ����2�����ݡ�
*     ���ڵ�һ�����ݣ���5��Լ����
*     ����1=����2
*     ����2=����3
*     ����3=����4
*     ����1=����4
*     ����2�ٱ���5
*     ��Ȼ���ǿ����
*         ����1=����2=����3=����4=����һ����ֵ
*         ����5=����һ���ͱ���2��ͬ����ֵ
*         �ʵ�һ���������"Yes"�� 
*     ���ڵڶ������ݣ���3��Լ����
*     ����1=����2
*     ����2=����3
*     ����1�ٱ���3
*         ��ǰ����Լ�����Ƴ�����1=����3����������Լ����������1�ٱ���3��ì�ܡ�
*         �ʵڶ����������"No"��
*  ����
*     ����10%�����ݣ�n,m �� 5��T �� 5��
*     ����50%�����ݣ�n,m �� 1000��T �� 10��
*     ����100%�����ݣ�1 �� n �� 300000, m �� 500000��1 �� a,b �� n��T �� 100��
*     ��֤�������ݵ�n�ܺ���m�ܺͲ�����500000��
*     ʱ�䣺2 sec
*     �ռ䣺256 MB
*   ��ʾ
*   [�ò��鼯��ά����ȵļ��ϡ�]
*   [�ı��� NOI 2015 day1 T1 �����Զ�����]
*   �ҵ�˼·
*       ����ȵĲ����Ͳ��ȵĲ����ֿ�
*       �ȴ�����ȵĲ���������ȵ����ŵ�ͬһ��������
*       �ٴ����ȵĲ�������鲻�ȵ����Ƿ���ͬһ�������У����������ͬһ�����ϣ�ֱ�������No����
                                                        ���в��Ȳ�����ִ���궼û���⣬�����Yes��
*       ����ʹ�ò��鼯����ѯʹ��·��ѹ��
*       �ؼ�����ζ������ݣ�ʹ�ڴ�ռ����С��ʱ��Խ��
*           ÿ����һ�����ݣ��漴����һ������
*           ����һ��ȫ��������¼��ǰ������ġ������ڡ�������ÿ�ζ������ݵ�ʱ�򣬱�ͷͳ�Ƶ�ǰ������ġ������ڡ���������
*               ȫ�������еĽڵ㲻��ʱ�������½ڵ㣻
*               ������ǰ��ġ������ڡ�����ʱ��������ͷ��¼�ĵ�ǰ�顰�����ڡ���������ȷ�����Ҹ���
*               ��������������ʱ��������ͷ�м�¼�ġ������ڡ�����������Ϊ0������ָ�벻�ö�
*           ����ջ�������
*               �п����ڵݹ�ִ��find����ʱ���º���ջ���������Ӧ����ʹ�÷ǵݹ��·��ѹ��
*               �ǵݹ��·��ѹ��
*                   �ṩһ���������ɵ�ȫ��ջ����ͷ��¼ջ����ջ���Ľڵ�ָ�룬ֻ��ջ�����õ�ʱ�򣬲��ڱ�ͷ��������½ڵ�
*                   �������ɵ�ջ���Է���ʹ�ã�ÿ��ֻҪ���±�ͷ�е�ջ��ָ�뼴��
*                   �������ʱ��ɾ��������
*                   findʱ�������ǰ�ڵ�ĸ��ڵ���Ǹõ����ڼ��ϵĸ��ڵ㣬��ֱ�ӷ��ؼ������Ƽ���
*                   ...                        ����...                ���������ѯ�丸�ڵ㣬������;�����ڵ�ѹջ
*                     �ҵ����ڵ�󣬵�ջ��������;ÿ���ڵ�ĸ��ڵ㣬��ʵ��·��ѹ��
*               �ݹ��·��ѹ��
*                   Ϊ��ֹ����ջ�����ÿ������ÿִ��һ�������Ĳ����󣬶��Ը�������ȫ���ڵ���һ��·��ѹ��
*       ���ݽṹ���
*           ��¼�������ڡ�����������ͷ
*           ��¼�������ڡ�����������ڵ�
*           ���Լ�¼300000�������ڴ棬��ʼֵΪ����ֵ����ʾ�ڵ��Լ��������ڼ�¼���ڵ㣬��ʵ�ֲ��鼯
*           һ���������ɵ�ȫ��ջ
*           һ�����ڼ�¼��������ڴ�
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

// ����0
#define MAX_N 300000
#define EQUAL   1
#define UNEQUAL 0

enum output_result_idx
{
    YES = 0,
    NO
};

static const char* g_output_type[2] = { "Yes", "No" };
static int  g_output_cnt;
static char* g_output_result; // ָ���¼���ս�����ڴ�

typedef struct unequal_chain_node
{
    int num1;
    int num2;
    struct unequal_chain_node* next;
}unequal_chain_node_s;

typedef struct unequal_chain_head
{
    int opt_cnt;
    unequal_chain_node_s* tail;   // ָ��β�ڵ㣬�½ڵ����β�ڵ���
    unequal_chain_node_s* next;   // �����нڵ�������
    unequal_chain_node_s* ranger; // ָ��ǰ���Դ洢��������Ľڵ�
}unequal_chain_head_s;

// ָ��ȫ���ڴ棬��MAX_N���ڵ�
static int* g_node;

// ȫ�֡������ڡ���������ͷ
static unequal_chain_head_s* g_unequal_chain_head;

static void set_union(int set_root_a, int set_root_b)
{
    g_node[set_root_b] = set_root_a;

    return;
}

static int set_find_by_recursion(int val)
{
    // �ݹ��
    if (val == g_node[val]) {
        return val;
    }
    g_node[val] = set_find_by_recursion(g_node[val]);
    return g_node[val];
}

static void opt_enchain(int tmp_a, int tmp_b, int opt)
{
    // �����жϣ�˵����ǰ�����ϵĽڵ㲻����
    if (nullptr == g_unequal_chain_head->ranger) {
        g_unequal_chain_head->tail->next = new unequal_chain_node_s;
        g_unequal_chain_head->tail = g_unequal_chain_head->tail->next;
        g_unequal_chain_head->tail->next = nullptr;

        g_unequal_chain_head->ranger = g_unequal_chain_head->tail;
    }

    g_unequal_chain_head->opt_cnt++;
    g_unequal_chain_head->ranger->num1 = tmp_a;
    g_unequal_chain_head->ranger->num2 = tmp_b;
    g_unequal_chain_head->ranger = g_unequal_chain_head->ranger->next;
    
    return;
}

static void safe_recursion(int data_cnt)
{
    int j;

    for (j = 1; j <= data_cnt; j++) {
        set_find_by_recursion(j);
    }

    return;
}

static int process_group_data(int data_cnt, int opt_cnt)
{
    int i;
    int root_a, root_b;
    int tmp_a, tmp_b, tmp_opt;
    unequal_chain_node_s* ranger;

    for (i = 0; i < opt_cnt; i++) {
        scanf("%d %d %d", &tmp_a, &tmp_b, &tmp_opt);
        getchar();

        root_a = set_find_by_recursion(tmp_a);
        root_b = set_find_by_recursion(tmp_b);

        if (root_a == root_b) {
            if (EQUAL == tmp_opt) {
                continue;
            }

            // ��ʱ�Ѿ������ж����ΪNO��������Ҫ����ʣ���������ܷ���
            while (++i < opt_cnt) {
                scanf("%d %d %d", &tmp_a, &tmp_b, &tmp_opt);
                getchar();
            }
            return NO;
        }

        // ���� root_a != root_b
        if (EQUAL == tmp_opt) {
            set_union(root_a, root_b);

            // ��ֹ������̫��ʱ������ջ���������ÿִ��1000�β���������һ��·��ѹ��
            if (i > 0 && 0 == i % 1000) {
                safe_recursion(data_cnt);
            }

            continue;
        }

        // �����������������ꡰ���ڡ�������ͳһ���������ڡ�����
        opt_enchain(tmp_a, tmp_b, tmp_opt);
    }

    // ���������е�����
    ranger = g_unequal_chain_head->next;
    for (i = 0; i < g_unequal_chain_head->opt_cnt && nullptr != ranger; i++) {
        root_a = set_find_by_recursion(ranger->num1);
        root_b = set_find_by_recursion(ranger->num2);
        if (root_a == root_b) {
            return NO;
        }
        ranger = ranger->next;
    }
    
    return YES;
}

static void process()
{
    int i, j;
    int data_cnt, opt_cnt;

    for (i = 0; i < g_output_cnt; i++) {
        scanf("%d %d", &data_cnt, &opt_cnt);
        getchar();

        // ���������ݴ���������ȫ�ֽ������
        g_output_result[i] = (char)process_group_data(data_cnt, opt_cnt);
        
        // ����g_node��׼��������һ������
        for (j = 1; j <= data_cnt; j++) {
            g_node[j] = j;
        }

        // ��������
        g_unequal_chain_head->opt_cnt = 0;
        g_unequal_chain_head->ranger = g_unequal_chain_head->next;
    }

    return;
}

static void free_unequal_chain()
{
    unequal_chain_node_s* cur, *next;

    if (nullptr == g_unequal_chain_head) {
        return;
    }

    if (nullptr == g_unequal_chain_head->next) {
        delete g_unequal_chain_head;
        g_unequal_chain_head = nullptr;
        return;
    }
    
    // ��ͷ��ʼ�ͷ�
    next = g_unequal_chain_head->next;
    delete g_unequal_chain_head;
    g_unequal_chain_head = nullptr;

    while (nullptr != next) {
        cur = next;
        next = next->next;
        delete cur;
    }

    return;
}

static void init()
{
    int i;

    // ��0��Ԫ��û�ã����ݷ�Χ��[1, 300000]
    g_node = new int[MAX_N + 1];
    for (i = 1; i <= MAX_N; i++) {
        g_node[i] = i;
    }

    g_unequal_chain_head = new unequal_chain_head_s;
    g_unequal_chain_head->opt_cnt = 0;
    g_unequal_chain_head->next = new unequal_chain_node_s;
    g_unequal_chain_head->next->next = nullptr;
    g_unequal_chain_head->tail = g_unequal_chain_head->next;
    g_unequal_chain_head->ranger = g_unequal_chain_head->next;

    scanf("%d", &g_output_cnt);
    getchar();
    g_output_result = new char[g_output_cnt];

    return;
}

static void end()
{
    delete[] g_node;

    // �ͷš������ڡ���������
    free_unequal_chain();

    delete[] g_output_result;

    return;
}

static void output()
{
    char i;

    for (i = 0; i < g_output_cnt; i++) {
        printf("%s\n", g_output_type[g_output_result[i]]);
    }

    return;
}

void equation()
{
    init();

    process();
    output();

    end();

    return;
}