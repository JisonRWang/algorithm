/*  题目
*      花里花哨的计算器
*   描述
*      有一个花里花哨的计算器，它可以在输入的时候，指定输入的字体。每种字体的对应如下所示：
*      字体a：
*          1234567890
*      字体b：
*          !@#$%^&*()
*      字体c：
*          qwertyuiop
*      字体d：
*          asdfghjkl;
*      字体e：
*          zxcvbnm,./
*      字体f：
*          ... .-. .-. ... .-. .-. .-. .-. .-. .-.
*          ..| ..| ..| |.| |.. |.. ..| |.| |.| |.|
*          ... .-. .-. .-. .-. .-. ... .-. .-. ...
*          ..| |.. ..| ..| ..| |.| ..| |.| ..| |.|
*          ... .-. .-. ... .-. .-. ... .-. .-. .-.
*   现在告诉你输入的数字，以及每个数字所指定的字体。请显示正确的输出。
*   输入格式
*       第一行为一个数字T，表示有T组数据。
*       接下来有T行，每行有一个字符串，表示输入的数字以及每个数字对应
的字体，格式为n_1 A_1 n_2 A_2 n_3 A_3 …，其中n_i 为数字（0~9），A_i为
其前面那个数字的字体（a~f）。数字个数小于100。
*   输出格式
*       输出正确的显示。注意，f字体为多行字体，其他字体为单行字体。若所
有数字的字体均为单行字体，则输出为单行。若其中存在一个或多个多行字体，则
输出多行，所有单行字体显示在最低行，上方用’.’填充。
*   样例输入
*       2
*       1a2b3c4d5e
*       1a2b3c4d5e6f7a
*   样例输出
*       1@efb
*       ......-..
*       .....|...
*       ......-..
*       .....|.|.
*       1@efb.-.7
*   数据范围
*       T ≤ 5
*   时间限制：1 s
*   空间限制：512 MB
*   思路：
*       纯编程题，没什么明显的算法。
*   
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

// 字符索引表，通过字符找到指定的字体
static const char** g_char_style_table;
static char (*g_char_f_style)[5][3];

// 输入，数字不超过100个，那么加上对应的类型和末尾的'\0'，总字符数不超过201个，这里用210个
// g_char_input是数组指针，g_char_input+1，跨越的是210个元素！！！
static char (*g_char_input)[210];

void init_f_style();

static void init()
{
    int i, j;

    // 直接用字符'a'~'f'做索引，'f'的十进制ascii码是102，'a'是97
    // 因为f类型太特殊，所以不挂到这张表上，到时候通过判断索引直接确定f
    // 这里可以用一个offset优化一下
    g_char_style_table = new const char* [103];
    g_char_style_table[97] = "0123456789";  // 'a'类型字体
    g_char_style_table[98] = ")!@#$%^&*(";  // 'b'
    g_char_style_table[99] = "pqwertyuio";  // 'c'
    g_char_style_table[100] = ";asdfghjkl"; // 'd'
    g_char_style_table[101] = "/zxcvbnm,."; // 'e'

    g_char_f_style = new char[10][5][3];
    init_f_style();

    // T ≤ 5
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

    // f类型只有5行，所以其他style的数字要补4行的'.'，这里逐行输出
    for (row = 0; row < 5; row++) {
        // 扫描字符串
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

            // 处理f类型
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

    // 扫描查看是否存在f类型
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

    // 不对输入参数做校验
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

// 由于函数太长，所以放到最下面
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