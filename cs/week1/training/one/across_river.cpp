/* ��Ŀ��
*      ��������
*  ������
*      ũ��(Human)���ӡ�һ��ũ�����һֻ��(Wolf)��һֻ��(Sheep)��һЩ��(Vegetable)���ӡ�
*  �ӱ�ֻ��һ���������ڴ�̫С��ֻ��װ��ũ�������һ�������������˿��ܵ�����£���Ҫ����
*  ��Ҫ�Բˣ�����ũ����β���ʹ��������ƽ������?
*  �����ʽ��
*      û������
*  �����ʽ��
*      ���һ�У�Ϊ���յĹ��ӷ�ʽ��������ʽΪ��������Ա��������Ա��������Ա��������Ա��...��������Ա��
*      ��ȥ�ͻ�������Ա֮�䣬�ÿո������
*      ���ĸ�����Ӣ�ĵ�����ĸ��ָ��Ӧ������(H->Human,W->Wolf,S->Sheep,V->Vegetable)
*      ���������з������ɡ�
*  �������룺
*      ��
*  ���������
*      HS H HW H
*  ע�ͣ�
*      ʱ�����ƣ�1 s
*      �ռ����ƣ�512 MB
*      ������������ڽ��������ʽ���Ǵ𰸡�
*  ��������������ķ���Ϊ��
*      �˺����ȥ���˻������˺��ǹ�ȥ���˻�������ʱ�԰��ǰ�����ˣ���������ĿҪ�󣬹ʷ���ȷ�𰸡�
*  �ҵ�˼·��
*      ���á���������������ʼ״̬�ڶ������������������ʾ״̬(H,W,S,V)��1-->���ڣ�0-->������
*      ��(H,W,S,V)����Ϊ4bit�����������ɱ�ʾ�����ݷ�ΧΪ[0,15]
*      ����ĳһ����������ֵ�״̬Ϊ(0,1,1,1)(0,1,1,0)(0,0,1,1)
*      ��������4bit���������ķ�����(1,0,0,0)(1,0,0,1)(1,1,0,0)���������ͬһʱ��԰���״̬
*      ���ԣ���ĳһ��������һ����6�ֲ�������ֵ�״̬����(0,1,1,1)(0,1,1,0)(0,0,1,1)(1,0,0,0)(1,0,0,1)(1,1,0,0)
*      ֻҪ��֤ĳһ������������6��״̬����ôһ�����Ա�֤��һ����״̬Ҳ�ǰ�ȫ��
*      �ɺ�ʱ��ÿ�����͵Ķ���Ϊ���¼���(1,1,0,0)(1,0,1,0)(1,0,0,1)(1,0,0,0)
*      ��ȻֻҪĳһ����������6���������һ�����ǰ�ȫ�ģ���ô�Ϳ���ֱ�ӽ��������Ϊֻ����һ��
*      ��ĳһ�����߶��������������Ĺ��̣���ĳһ�����������������ӡ��Ĺ���
*      �����������ѧģ�ͣ�ֻվ����ʼ״̬��һ��ȥ˼������
*          ״̬��Χ[0,15]����ʼ״̬Ϊ15������״̬Ϊ0
*          ��������⼴���ڰ�ȫ�����£��ӳ�ʼ״ֵ̬15ͨ��������мӼ��������ճ�Ϊ����״ֵ̬0
*          ��һ�β���Ϊ������
*          ״̬���̣�15-a+b-c+d-e...-n = 0�����У�a,b,c,d...n�Ŀ�ѡֵΪ(1,1,0,0)(1,0,1,0)(1,0,0,1)(1,0,0,0)
*          ��������(1,1,0,0)==>12, (1,0,1,0)==>10, (1,0,0,1)==>9, (1,0,0,0)==>8
*          ��ֹ״̬(0,1,1,1)==>7, (0,1,1,0)==>6, (0,0,1,1)==>3, (1,0,0,0)==>8, (1,0,0,1)==>9, (1,1,0,0)==>12
*          ��ȫ״̬ģ�ͣ�
*              ��������������һ������֮���״̬����Χ[0,15]
*              ÿ�εĲ����������Ϊ����6��ֵ��7,6,3,8,9,12
*              ���Ρ��ӡ�֮��Ľ��������֮ǰ�κ�һ�Ρ��ӡ�֮��Ľ����ͬ
*              ���Ρ�����֮��Ľ��������֮ǰ�κ�һ�Ρ�����֮��Ľ����ͬ
*              ִ�С��ӡ�����ʱ������һ��״̬+��ǰ��������������������4bit����������ÿһbit������ͬʱΪ1��
ͬʱΪ1��ʾ��Ӧλ�Ķ����Ѿ����ڲ��ҵ�ǰ�����ֻ�����һ���ö����������Ѿ������ˣ���������Ķ������ּ���һֻ��
���������У�������˶���Ψһ�ģ�
*              ִ�С���������ʱ������һ��״̬-��ǰ������������Ϊ��������һbitΪ1ʱ����Ϊ����������һbitҲ����
Ϊ1������ĳһλ������ֻ�������������1-1��1-0��0-0����������0-1���ڱ����д���ĺ������ĳһ�ֶ������ڵ�����£�
�����������������1-1��ʾ���ǵ�ʱ�������ǣ�0-1��ʾû�ǵ�ʱ�������ǣ�����û����ģ�1-0��ʾ���ǵ��ǲ����ߣ���
*/

#include <iostream>

using namespace std;

#define STEP_MAX       100 // ����ֵ
#define INIT_STATE_VAL 15
#define END_STATE_VAL  0

typedef struct Step
{
    char opt_index; // ��¼��������������
    char state_val; // ��¼���������Ľ��
}Step_s;

// ������Ӧ(H,W,S,V)�е�bit
static char g_illegal_val[6] = { 3,6,7,8,9,12 };
// �����ǺϷ�ֵ
static const char* g_legal_val_name[INIT_STATE_VAL+1] = {"END", "V", "S", "SV", "W",
                                                       "WV", "WS", "WSV", "H", "HV",
                                                       "HS", "HSV", "HW", "HWV", "HWS", "HWSV"};
static char g_opt[4] = { 8,9,10,12 };
static const char* g_opt_name[4] = {"H","HV","HS","HW"}; // ��g_opt���±���ȫ��Ӧ���������
static Step_s* g_path = nullptr;

void std_out(int step)
{
    char i;

    // ����Ŀʾ��Ҫ��ֻ�������������ֱ�Ӵӵ�1���Ĳ���ֵ��ʼ����������һ���Ĳ���ֵ
    for (i = 1; i <= step; i++) {
        cout << g_opt_name[g_path[i].opt_index];
        if (i < step) {
            cout << " ";
        }
    }
    //cout << endl;

    return;
}

void my_out(int sum, int step)
{
    char i, dir;

    cout << "��" << sum << "�ַ����� ";
    cout << g_legal_val_name[g_path[0].state_val] << " ";
    for (i = 1; i <= step; i++) {
        dir = (0 == i % 2) ? 1 : -1;
        (1 == dir) ? (cout << "+") : (cout << "-");
        cout << g_opt_name[g_path[i].opt_index] << " ";
        cout << g_legal_val_name[g_path[i].state_val] << " ";
    }
    cout << endl;

    return;
}

bool safe_opt(int step)
{
    char tmp, tmp_prev, tmp_opt;
    char i, dir, cur_opt, cur_state_val, prev_state_val;

    dir = (0 == step % 2) ? 1 : -1;
    prev_state_val = g_path[step - 1].state_val;
    cur_opt = g_opt[g_path[step].opt_index];

    // Ҫ��֤cur_opt�ĵ���λ��prev_state_val�ĵ���λ����Ӧ��ÿһλ������ͬʱΪ1
    if ((1 == dir) && 
        (0 != (prev_state_val & cur_opt))) {
        return false;
    }
    if (-1 == dir) {
        // cur_state_val = prev_state_val - cur_opt��������Ϊ��
        if (prev_state_val < cur_opt) {
            return false;
        }
        // ��֤ÿһλ����ʱ�����������0-1�����
        tmp = 1;
        for (i = 0; i < 4; i++) {
            tmp_prev = prev_state_val & tmp;
            tmp_opt = cur_opt & tmp;
            if (tmp_prev < tmp_opt) {
                return false;
            }

            tmp <<= 1;
        }
    }

    cur_state_val = g_path[step].state_val;
    if (cur_state_val < 0 || cur_state_val > INIT_STATE_VAL) {
        return false;
    }

    for (i = 0; i < 6; i++) {
        if (cur_state_val == g_illegal_val[i]) {
            return false;
        }
    }

    // ����ظ���ע�⣬i>=0��Ϊ�˼���Ƿ�����ʼ״̬��ֵ��ͬ
    for (i = step-2; i >= 0; i -= 2) {
        if (cur_state_val == g_path[i].state_val) {
            return false;
        }
    }

    return true;
}

void across_river(int& sum, int step)
{
    char i, dir;

    // �����Ĳ������ٴ�1��ʼ����0����ʾ��ʼ״̬��û�в�����������1�����в��������Լ��������
    if (step < 1 || step >= STEP_MAX) {
        cout << "Fatal error: out of range. The step is " << step << endl;
        return;
    }

    // �ݹ�������˹�ɺ��������ƣ����ж�����step���������һ������һ����
    if (0 == g_path[step-1].state_val) {
        sum++;

        std_out(step-1);
        //my_out(sum, step-1);

        return;
    }

    // ������������
    dir = (0 == step % 2) ? 1 : -1;
    for (i = 0; i < 4; i++) {
        g_path[step].opt_index = i;
        g_path[step].state_val = g_path[step - 1].state_val + dir * g_opt[g_path[step].opt_index];
        if (safe_opt(step)) {
            across_river(sum, step+1);
        }
        
        // Ϊ�ύOJ�������ȫ��������������ж�ȥ������
        if (1 == sum) {
            return;
        }
    }

    return;
}

void animals_across_river()
{
    int i, sum;

    g_path = new Step_s[STEP_MAX];
    for (i = 0; i < STEP_MAX; i++) {
        g_path[i].opt_index = -1;
        g_path[i].state_val = -1;
    }

    sum = 0;
    g_path[0].state_val = INIT_STATE_VAL;
    across_river(sum, 1);

    delete[] g_path;
    return;
}