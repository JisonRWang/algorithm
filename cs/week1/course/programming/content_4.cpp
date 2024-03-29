/* 题目：
*  分书问题
*     有编号为0、1、2、3、4的5本书，准备分给A、B、C、D、E五个人，请
*     写一个程序，输出所有的分书方案，要求每个分书方案都能让每个人都
*     皆大欢喜（即每个人都分到感兴趣的书）。
*  这5个人对5本书的阅读兴趣如下表所示：
*     0   1   2   3   4
*  A  0   0   1   1   0
*  B  1   1   0   0   1
*  C  0   1   1   0   1
*  D  0   0   0   1   0
*  E  0   1   0   0   1
*  我的思路（和老师的使用回溯的方法相同）：
*      采用深度优先的方式，用递归做逐层遍历。以人为切入点，从A开始，遍历这个人的所喜欢的书，发现他感兴趣的书时，如果这本书没被分出去，
*  则将该书分给这个人，然后递归遍历B喜欢的书，如果该书没被分配，则将该书分配给B，然后递归遍历C喜欢的书，直至E。如果某个人所感兴趣的书
*  已经被分配出去，则继续找这个人感兴趣的书，如果找到，就分配，然后进去下一个人的递归流程；如果没找到，则本层递归结束，说明这种方案不行，
*  回到上一层递归后，继续接着上一层原来的循环继续查找上一个人感兴趣的书，作为另一种方案的开始，如果找到，则进入下一个人的递归；如果没找到，
*  则该层递归结束，返回上一层递归，以此类推。这里采用的是“深度优先”的方式，用递归来实现回溯。这种方式和跳马问题的深度优先方式如出一辙。
*      数据结构使用两张表，一张记录每个人所感兴趣的书（二维表），一张表记录每本书被分给了谁（一维表，索引是书，值为该书所分配的人）
*  不使用回溯的思路：
*      使用一个状态变量来记录本次的分配情况并将该状态变量传给下一次递归。个人理解，其实不能算不回溯，只是说这种方法不用去修改全局的
*  图书分配情况表，每次递归都使用本层递归自己临时创建的状态记录表去记录当前的分配情况，因为是临时的不是全局的，所以只是少了一个修改
*  全局表的动作，回溯本身这个动作还是要做的，只是这种方法在回溯之后不用修改全局图书分配表（没有这张表，只有属于每层递归自己的临时分配表）。
*/

#include <iostream>

using namespace std;

enum Distributing_Books_Person_Name {
    READER_A = 0,
    READER_B,
    READER_C,
    READER_D,
    READER_E,

    READER_COUNT
};

static char g_name[5] = {'A', 'B', 'C', 'D', 'E'};
static int g_books[5] = { -1, -1, -1, -1, -1 };
static int g_prefer[READER_COUNT][5] = { {0, 0, 1, 1, 0},
                                     {1, 1, 0, 0, 1},
                                     {0, 1, 1, 0, 1},
                                     {0, 0, 0, 1, 0},
                                     {0, 1, 0, 0, 1} };

// 以人为突破点，从第零个人开始分配书，一直递归分配到最后一个人
void distributing_books_by_person(int& sum, int reader)
{
    int i;

    // 递归基
    if (READER_COUNT == reader) {
        sum++;
        cout << "第" << sum << "种方案： ";

        // 遍历books
        for (i = 0; i < 5; i++) {
            cout << g_name[g_books[i]] << " ";
        }
        cout << endl;
        return;
    }

    // 遍历当前reader的喜好
    for (i = 0; i < 5; i++) {
        if (1 == g_prefer[reader][i] && -1 == g_books[i]) {
            g_books[i] = reader;
            // tips: 这里的reader+1不能换成++reader更不能换成reader++(会导致栈溢出)
            distributing_books_by_person(sum, reader+1);

            // 一个人不能被分配1本以上的书，下一步要开始试着给这个人分配下一本书了，
            // 所以这本书的分配状态要置回去
            g_books[i] = -1;
        }
    }

    return;
}

void distributing_books()
{
    int sum;

    sum = 0;
    distributing_books_by_person(sum, READER_A);

    return;
}