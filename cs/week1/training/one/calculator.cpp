/*  ��Ŀ
*      ���ﻨ�ڵļ�����
*   ����
*      ��һ�����ﻨ�ڵļ��������������������ʱ��ָ����������塣ÿ������Ķ�Ӧ������ʾ��
*      ����a��
*          1234567890
*      ����b��
*          !@#$%^&*()
*      ����c��
*          qwertyuiop
*      ����d��
*          asdfghjkl;
*      ����e��
*          zxcvbnm,./
*      ����f��
*          ... .-. .-. ... .-. .-. .-. .-. .-. .-.
*          ..| ..| ..| |.| |.. |.. ..| |.| |.| |.|
*          ... .-. .-. .-. .-. .-. ... .-. .-. ...
*          ..| |.. ..| ..| ..| |.| ..| |.| ..| |.|
*          ... .-. .-. ... .-. .-. ... .-. .-. .-.
*   ���ڸ�������������֣��Լ�ÿ��������ָ�������塣����ʾ��ȷ�������
*   �����ʽ
*       ��һ��Ϊһ������T����ʾ��T�����ݡ�
*       ��������T�У�ÿ����һ���ַ�������ʾ����������Լ�ÿ�����ֶ�Ӧ
�����壬��ʽΪn_1 A_1 n_2 A_2 n_3 A_3 ��������n_i Ϊ���֣�0~9����A_iΪ
��ǰ���Ǹ����ֵ����壨a~f�������ָ���С��100��
*   �����ʽ
*       �����ȷ����ʾ��ע�⣬f����Ϊ�������壬��������Ϊ�������塣����
�����ֵ������Ϊ�������壬�����Ϊ���С������д���һ�������������壬��
������У����е���������ʾ������У��Ϸ��á�.����䡣
*   ��������
*       2
*       1a2b3c4d5e
*       1a2b3c4d5e6f7a
*   �������
*       1@efb
*       ......-..
*       .....|...
*       ......-..
*       .....|.|.
*       1@efb.-.7
*   ���ݷ�Χ
*       T �� 5
*   ʱ�����ƣ�1 s
*   �ռ����ƣ�512 MB
*   ˼·��
*       ������⣬ûʲô���Ե��㷨��
*   
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

// �ַ�������ͨ���ַ��ҵ�ָ��������
static const char** g_char_style_table;
static char (*g_char_f_style)[5][3];

// ���룬���ֲ�����100������ô���϶�Ӧ�����ͺ�ĩβ��'\0'�����ַ���������201����������210��
// g_char_input������ָ�룬g_char_input+1����Խ����210��Ԫ�أ�����
static char (*g_char_input)[210];

void init_f_style();

static void init()
{
    int i, j;

    // ֱ�����ַ�'a'~'f'��������'f'��ʮ����ascii����102��'a'��97
    // ��Ϊf����̫���⣬���Բ��ҵ����ű��ϣ���ʱ��ͨ���ж�����ֱ��ȷ��f
    // ���������һ��offset�Ż�һ��
    g_char_style_table = new const char* [103];
    g_char_style_table[97] = "0123456789";  // 'a'��������
    g_char_style_table[98] = ")!@#$%^&*(";  // 'b'
    g_char_style_table[99] = "pqwertyuio";  // 'c'
    g_char_style_table[100] = ";asdfghjkl"; // 'd'
    g_char_style_table[101] = "/zxcvbnm,."; // 'e'

    g_char_f_style = new char[10][5][3];
    init_f_style();

    // T �� 5
    g_char_input = new char[5][210];
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 210; j++) {
            g_char_input[i][j] = '\0';
        }
    }

    return;
}

static void end()
{
    delete[] g_char_style_table;
    delete[] g_char_f_style;
    delete[] g_char_input;

    return;
}

void complicated_output(const char* str)
{
    int row, i, num;
    char c_num, style;

    // f����ֻ��5�У���������style������Ҫ��4�е�'.'�������������
    for (row = 0; row < 5; row++) {
        // ɨ���ַ���
        i = 0;
        while ('\0' != str[i]) {
            c_num = str[i++];
            style = str[i++];

            num = c_num - '0';
            if ('f' != style) {
                if (4 != row) {
                    cout << '.';
                    continue;
                }
                cout << g_char_style_table[style][num];
                continue;
            }

            // ����f����
            cout << g_char_f_style[num][row][0];
            cout << g_char_f_style[num][row][1];
            cout << g_char_f_style[num][row][2];
        }
        if (row < 4) {
            cout << endl;
        }
    }

    return;
}

void uncomplicated_output(const char* str)
{
    int i, num;
    char c_num, style;

    i = 0;
    while ('\0' != str[i]) {
        c_num = str[i++];
        style = str[i++];

        num = c_num - '0';
        cout << g_char_style_table[style][num];
    }

    cout << endl;

    return;
}

void output(const char* str)
{
    int i;
    bool f_style;

    // ɨ��鿴�Ƿ����f����
    for (i = 0; str[i] != '\0'; i++) {
        f_style = false;
        if ('f' == str[i]) {
            f_style = true;
            break;
        }
    }

    if (!f_style) {
        uncomplicated_output(str);
        return;
    }

    complicated_output(str);
    return;
}

void calculator()
{
    int i, T;

    init();

    // �������������У��
    T = 0;
    scanf("%d", &T);
    if (T < 1) {
        cout << "Wrong input." << endl;
        return;
    }
    for (i = 0; i < T; i++) {
        scanf("%s", g_char_input[i]);
    }

    for (i = 0; i < T; i++) {
        output(g_char_input[i]);
    }

    end();

    return;
}

// ���ں���̫�������Էŵ�������
void init_f_style()
{
    int i,j,k;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 3; k++) {
                g_char_f_style[i][j][k] = '.';
            }
        }
    }

    /*
         012
       0 .-.
       1 |.|
       2 ...
       3 |.|
       4 .-.
    */
    g_char_f_style[0][0][1] = g_char_f_style[0][4][1] = '-';
    g_char_f_style[0][1][0] = g_char_f_style[0][1][2] = g_char_f_style[0][3][0] = g_char_f_style[0][3][2] = '|';

    /*
         012
       0 ...
       1 ..|
       2 ...
       3 ..|
       4 ...
    */
    g_char_f_style[1][1][2] = g_char_f_style[1][3][2] = '|';

    /*
         012
       0 .-.
       1 ..|
       2 .-.
       3 |..
       4 .-.
    */
    g_char_f_style[2][0][1] = g_char_f_style[2][2][1] = g_char_f_style[2][4][1] = '-';
    g_char_f_style[2][1][2] = g_char_f_style[2][3][0] = '|';

    /*
         012
       0 .-.
       1 ..|
       2 .-.
       3 ..|
       4 .-.
    */
    g_char_f_style[3][0][1] = g_char_f_style[3][2][1] = g_char_f_style[3][4][1] = '-';
    g_char_f_style[3][1][2] = g_char_f_style[3][3][2] = '|';

    /*
         012
       0 ...
       1 |.|
       2 .-.
       3 ..|
       4 ...
    */
    g_char_f_style[4][2][1] = '-';
    g_char_f_style[4][1][0] = g_char_f_style[4][1][2] = g_char_f_style[4][3][2] = '|';

    /*
         012
       0 .-.
       1 |..
       2 .-.
       3 ..|
       4 .-.
    */
    g_char_f_style[5][0][1] = g_char_f_style[5][2][1] = g_char_f_style[5][4][1] = '-';
    g_char_f_style[5][1][0] = g_char_f_style[5][3][2] = '|';

    /*
         012
       0 .-.
       1 |..
       2 .-.
       3 |.|
       4 .-.
    */
    g_char_f_style[6][0][1] = g_char_f_style[6][2][1] = g_char_f_style[6][4][1] = '-';
    g_char_f_style[6][1][0] = g_char_f_style[6][3][0] = g_char_f_style[6][3][2] = '|';

    /*
         012
       0 .-.
       1 ..|
       2 ...
       3 ..|
       4 ...
    */
    g_char_f_style[7][0][1] = '-';
    g_char_f_style[7][1][2] = g_char_f_style[7][3][2] = '|';

    /*
         012
       0 .-.
       1 |.|
       2 .-.
       3 |.|
       4 .-.
    */
    g_char_f_style[8][0][1] = g_char_f_style[8][2][1] = g_char_f_style[8][4][1] = '-';
    g_char_f_style[8][1][0] = g_char_f_style[8][3][0] = g_char_f_style[8][3][2] = '|';
    g_char_f_style[8][1][2] = '|';

    /*
         012
       0 .-.
       1 |.|
       2 .-.
       3 ..|
       4 .-.
    */
    g_char_f_style[9][0][1] = g_char_f_style[9][2][1] = g_char_f_style[9][4][1] = '-';
    g_char_f_style[9][1][0] = g_char_f_style[9][1][2] = g_char_f_style[9][3][2] = '|';

    return;
}