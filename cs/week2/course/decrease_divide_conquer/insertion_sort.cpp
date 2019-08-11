/* ��������
*           ��һ��online �������㷨
*           �������ݵ������Ƽ������֣������ݣ���д
*           ���㷨����Ҫ�����ʾ��ǽ������ݲ��뵽һ���Ѿ��ź����
     �����У����ѡ�������ð����������������������ѡ�����ݲ�
     �˷������������е��㷨Ҫ��Ч�Ķ࣬�ؼ����Ǹ��㷨�ܹ�����
     ǰ���Ѿ��ź�������С���Ȼ���㷨�Ͻ��ѡ�������ð������
     ��ͬ����ƽ��ʱ�临�Ӷ��ǲ�ͬ�ġ�
*/

#include <iostream>
#include <cstdio> 

using namespace std;

int g_cnt;
int* g_mem;

void print_result()
{
    int i;

    for (i = 0; i < g_cnt; i++) {
        printf("%d ", g_mem[i]);
    }
    printf("\n");

    return;
}

void insertion_sort()
{
    int i, j, tmp;

    // tips: [0, j] �����Ѿ��ź��������
    for (i = 0; i < g_cnt; i++) {
        for (j = i; j-1 >= 0; j--) {
            if (g_mem[j] >= g_mem[j-1]) {
                // ǰ���Ѿ��ź�������ֱ��break
                break;
            }
            tmp = g_mem[j];
            g_mem[j] = g_mem[j-1];
            g_mem[j-1] = tmp;
        }
    }

    return;
}

void init()
{
    int i;

    scanf("%d", &g_cnt);
    getchar();

    g_mem = new int[g_cnt];
    for (i = 0; i < g_cnt; i++) {
        scanf("%d", &g_mem[i]);
        getchar();
    }

    return;
}

void end()
{
    delete[] g_mem;
    return;
}

int main()
{
    init();

    insertion_sort();
    print_result();

    end();
    
    return 0;
}
