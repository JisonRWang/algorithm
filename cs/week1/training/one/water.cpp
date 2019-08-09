/* ��Ŀ��
*     ��ˮ����
*  ������
*     ��A��B��C�������ӣ���������Ϊ80ml��50ml��30ml��
*  ����A����װ����80ml��ˮ��B��C���ǿձ���A�е�ˮ���Ե���B����C���У�
*  ��֮��B��CҲ������A�е��������Ի��൹����ȥ��Ϊ�˼���������ĳһ�����Ӷ��ԣ�
*  ���Ǳ����������Ǳ����ա�Ҳ����˵��Ҫô��ˮ�ı��ӿ��ˣ�Ҫô����ˮ�ı������ˣ�
*  ��ε�ˮ�����Ż�ֹͣ�������һ�����򣬽�ԭ����80ml�ľƷֱ���A��B���������У�
*  ����40ml�����ÿһ���Ĳ�����
*  �����ʽ��
*     û������
*  �����ʽ��
*     ��һ�����һ������n����ʾ�����������
*     ֮����n�У�ÿ�б�ʾһ������������������ĸ x �� y����ʾ�� x ���ľƣ�����y�С�
*     ���������з������ɡ�
*  �������룺
*     ��
*  ���������
*     4
*     A B
*     A C
*     B A
*     C B
*  ע�ͣ�
*     ʱ�����ƣ�1 s
*     �ռ����ƣ�512 MB
*     ������������ڽ��������ʽ���Ǵ𰸡�
*  �ڴ�������������ķ���Ϊ��
*     һ����4��
*     ���״̬����A:80, B:0, C:0��
*     A ���� B����A:30, B:50, C:0)
*     A ���� C����A:0, B:50, C:30)
*     B ���� A����A:50, B:0, C:30)
*     C ���� B����A:50, B:30, C:0)
*     ���գ�A����50ml��B����30ml��C����0ml����������ĿҪ�󣬹ʷ���ȷ�𰸡�
*  ˼·��
*     ��A��B��C�������ӳ�����άֱ������ϵ�У�(A,B,C)��(x,y,z)
*     A��B��C���Եķ�Χȷ����һ����ά������ռ䣬�߽�Ϊ(80,50,30)
*     A��ʼ��80ml�ƣ���������ϵ�У���ʼ������Ϊ(80,0,0)
*     �־ƽ��ΪA��40ml��B��40ml��������������Ϊ(40,40,0)
*     �����������Ϊ��(80,0,0)�ߵ�(40,40,0)�Ĳ���
*     avail_capacity = min(max_capacity(x or y or z) - cur_capacity(x or y or z), poured_capacity)
*     poured_capacity = poured_capacity - avail_capacity
*     �´ε�ˮ��������ѡ��A->BC or B->AC or C->AB
*     ����ǰ�������͡����ĸ����ӵ�ˮ��ͳһ����
*     ÿһ��ֻ�ܴ�һ����������һ�����ӵ�ˮ������ͬʱ���������ӵ�ˮ
*  ��ȫ׼��
*     x+y+z = 80
*     0<=x<=80,0<=y<=50,0<=z<=30
*     ��ˮ������������ˮʱ���뱣֤��ˮ
*     ÿһ������֮��Ľ������������֮ǰ�κ�һ���Ĳ��������ͬ����(x,y,z)��ֵ��ͬ
*
*/

#include <iostream>

using namespace std;

#define MAX_STEPS 50

enum Glass
{
    GA = 0,
    GB,
    GC,

    GLASS_MAX
};

typedef struct State
{
    char glass[GLASS_MAX];
}State_s;

typedef struct Step
{
    char from;
    char to;
}Step_s;

static char g_max_capacity[GLASS_MAX] = { 80, 50, 30 };
static char g_glass_name[GLASS_MAX] = { 'A', 'B', 'C' };
static Step_s g_steps[MAX_STEPS]; // ��0��Ԫ��û��

// ���ء���Ϊ�ȷ�ˮʱ���κ�һ�η�ˮ�Ľ���϶�����10�ı�������������ֱ�ӽ���Χ��С10��
// ע��0<=x<=80,0<=y<=50,0<=z<=30Ӧ�ö�Ӧ���±�
static char repeat[8+1][5+1][3+1] = { {{0}} };

void std_out(char step)
{
    char i;

    cout << (int)step << endl;
    for (i = 1; i <= step; i++) {
        cout << g_glass_name[g_steps[i].from] << " " << g_glass_name[g_steps[i].to];
        if (i < step) {
            cout << endl;
        }
    }

    return;
}

void my_out(int& sum, char step)
{
    char i;

    cout << "��" << sum << "�ַ����� " << endl;
    for (i = 1; i <= step; i++) {
        cout << g_glass_name[g_steps[i].from] << " " << g_glass_name[g_steps[i].to] << endl;
    }

    return;
}

bool update_state(char src, char dst, State_s prev_state, State_s& cur_state)
{
    char i;
    char src_cap, dst_cap, dst_max_cap;

    src_cap = prev_state.glass[src];
    dst_cap = prev_state.glass[dst];
    dst_max_cap = g_max_capacity[dst];

    // ûˮ���Ե�����
    if (src_cap <= 0) {
        return false;
    }

    // Ŀ����������
    if (dst_cap == dst_max_cap) {
        return false;
    }

    for (i = 0; i < GLASS_MAX; i++) {
        if (i != src && i != dst) {
            cur_state.glass[i] = prev_state.glass[i];
            break;
        }
    }
    if (src_cap <= dst_max_cap - dst_cap) {
        cur_state.glass[src] = 0;
        cur_state.glass[dst] = dst_cap + src_cap;
    }
    else {
        cur_state.glass[src] = src_cap - (dst_max_cap - dst_cap);
        cur_state.glass[dst] = dst_max_cap;
    }

    // ����
    if (1 == repeat[cur_state.glass[0]/10][cur_state.glass[1]/10][cur_state.glass[2]/10]) {
        return false;
    }

    return true;
}

// ÿһstep�����������ĸ����ӷ�ˮ���͡��ֵ����ĸ����ӡ�������ֻ������һ�����ӷ�ˮ
// ���Я������һ��״̬����ǰstepҪ������һ��step��stateȥ������
void pouring_water(int& sum, char step, State_s prev_state)
{
    char i, j;
    State_s cur_state;

    if (step < 0 || step >= MAX_STEPS) {
        cout << "Fatal error: out of range. Step: " << step << endl;
        return;
    }

    // �ݹ����������������ƣ����������һ���ǽ���ݹ����ǰһ����
    if (40 == prev_state.glass[GA] &&
        40 == prev_state.glass[GB] &&
        0 == prev_state.glass[GC]) {
        sum++;

        std_out(step-1);
        //my_out(sum, step-1);
        return;
    }

    // �����������ӣ���ÿ�������з�ˮ��from i to j
    for (i = 0; i < GLASS_MAX; i++) {
        for (j = 0; j < GLASS_MAX; j++) {
            if (i == j) {
                continue;
            }
            if (update_state(i, j, prev_state, cur_state)) {
                g_steps[step].from = i;
                g_steps[step].to = j;
                repeat[cur_state.glass[0] / 10][cur_state.glass[1] / 10][cur_state.glass[2] / 10] = 1;
                pouring_water(sum, step+1, cur_state);
                repeat[cur_state.glass[0] / 10][cur_state.glass[1] / 10][cur_state.glass[2] / 10] = 0;
                
                // ����OJҪ�����Ҫ���Լ��������ע�͵�����ж�
                if (1 == sum) {
                    return;
                }
            }
        }
    }
}

void separating_water()
{
    int sum;
    char i, step;
    State_s cur_state;

    for (i = 0; i < MAX_STEPS; i++) {
        g_steps[i].from = -1;
        g_steps[i].to = -1;
    }

    sum = 0;
    cur_state.glass[GA] = 80;
    cur_state.glass[GB] = 0;
    cur_state.glass[GC] = 0;
    repeat[8][0][0] = 1;

    // step ��1��ʼ
    pouring_water(sum, 1, cur_state);

    return;
}