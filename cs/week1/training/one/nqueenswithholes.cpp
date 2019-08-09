/* ��Ŀ
*     ����N�ʺ�����
*  ����
*     N�ʺ�������һ����������⣬��Ŀ������һ��N*N�������ϵ�ÿһ�з���1���ʺ�
��ʹ�䲻�ܻ��๥����ͬһ�С�ͬһ�С�ͬһб���ϵĻʺ󶼻��Զ���������
*     ���ڣ����ǽ������ϵ�һЩλ���ڶ����ڶ���λ�ò��ܷ������ӡ���ʱ����һ���ж����ֿ��ܵķ��÷�����
*  �����ʽ
*     �����һ����һ������N����ʾ���̴�С�� ����������N�У�ÿ����N�����ո������������
��ʾ������λ���Ƿ��ж�����0Ϊ������1Ϊ�ж�����
*  �����ʽ
*     ���һ�У�����һ����������ʾ��ǰN�ʺ�ķ��÷�������
*  ��������
*     4
*     1 1 0 1
*     0 0 0 0
*     0 0 0 0
*     0 0 0 0
*  �������
*     1
*  ���ݷ�Χ
*     1 <= N <= 10
*  ʱ�����ƣ�1 s
*  �ռ����ƣ�512 MB
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

#define ROW 11
#define COL ROW

typedef struct Point
{
    int x;
    int y;
}Point_s;

// ��¼��������������
static int N;

// ���̴�(1,1)��ʼ�������һЩ
static char(*g_holes_table)[COL] = nullptr;

static Point_s g_queens_loc[COL] = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},
                                         {6,0},{7,0},{8,0},{9,0},{10,0} };

static int g_chess_row[ROW] = { 0 }; // ��0��Ԫ��û��
static int g_intercept_offset = 9; // �ؾ�Ϊ��ֵʱʹ�õ�ƫ����
static int g_positive_diagonal[19] = { 0 }; // б��1��19���Խ��ߣ��±귶Χ[0,18]
static int g_negative_diagonal[21] = { 0 }; // б��-1��19���Խ��ߣ��±귶Χ[2,20]��ǰ����Ԫ���˷�

// �������Լ������Խ������Ƿ��������ʺ󣬲��Ҽ���Ƿ��ж�
bool safe_location(Point_s cur_loc)
{
    // ��
    if (1 == g_chess_row[cur_loc.y]) {
        return false;
    }

    if (1 == g_positive_diagonal[cur_loc.y - cur_loc.x + g_intercept_offset]) {
        return false;
    }

    if (1 == g_negative_diagonal[cur_loc.y + cur_loc.x]) {
        return false;
    }

    // �Ƿ��ж�
    if (1 == g_holes_table[cur_loc.x][cur_loc.y]) {
        return false;
    }

    return true;
}

// queen_num [1,10] ��ʾ���10���ʺ����ţ�Ҳ�����̵����±꣨��Ϊ�����зŻʺ�ģ�
void queen_laid(int& sum, int queen_num)
{
    int i;
    Point_s tmp_p;

    // �ݹ�������������һ���ʺ󣬻�Ҫ��������һ�㣬ʵ������һ�����Ѿ�������
    if (N+1 == queen_num) {
        sum++;
        return;
    }

    // ��i��queen���ڵ�i���Һ��ʵ���ȥ�ţ������Ǳ����У������Һ��ʵ��У�
    for (i = 1; i <= N; i++) {
        tmp_p.x = queen_num;
        tmp_p.y = i;
        if (safe_location(tmp_p)) {
            g_queens_loc[queen_num].y = tmp_p.y;
            g_chess_row[tmp_p.y] = 1;
            g_positive_diagonal[tmp_p.y - tmp_p.x + g_intercept_offset] = 1;
            g_negative_diagonal[tmp_p.y + tmp_p.x] = 1;

            queen_laid(sum, queen_num + 1);

            g_queens_loc[queen_num].y = 0;
            g_chess_row[tmp_p.y] = 0;
            g_positive_diagonal[tmp_p.y - tmp_p.x + g_intercept_offset] = 0;
            g_negative_diagonal[tmp_p.y + tmp_p.x] = 0;
        }
    }
    return;
}

void data_input()
{
    int i, j, tmp;

    // ������������ݺϷ���
    scanf("%d", &N);
    if (N <= 0) {
        cout << "Wrong input: N = " << N << endl;
        return;
    }

    for (i = 1; i <= N; i++) {
        // ��(1,1)��ʼ���룬�к��еĵ�0�û��
        for (j = 1; j <= N; j++) {
            scanf("%d", &tmp);
            g_holes_table[i][j] = (char)tmp;
        }
    }

    return;
}

static void init()
{
    int i, j;
    
    g_holes_table = new char[ROW][COL];
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            g_holes_table[i][j] = 0;
        }
    }

    return;
}

static void end()
{
    delete[] g_holes_table;

    return;
}

void n_queens_with_holes()
{
    int sum;

    init();

    data_input();
    
    sum = 0;
    queen_laid(sum, 1);
    cout << sum;

    end();

    return;
}