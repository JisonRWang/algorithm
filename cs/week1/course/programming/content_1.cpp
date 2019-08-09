/* 题目：
*  某地刑侦大队对涉及6个嫌疑人的一桩疑案进行分析，以下内容叙述的是刑侦队搜集到的线索和情报：
*     A、B至少有一人作案；
*     A、E、F三人中至少有两人参与作案；
*     A、D不可能是同案犯；
*     B、C或同时作案，或与本案无关；
*     C、D中有且仅有一人作案；
*     如果D没有参与作案，则E也不可能参与作案
*  编程将作案人找出
*/

#include <iostream>

using namespace std;

#define YES 1
#define NO  0
#define UNCONFIRMED -1
#define NUM 6

void suspect_confirmed()
{
    int i = 0, j = 0;
    int suspect[NUM] = {UNCONFIRMED, UNCONFIRMED, UNCONFIRMED, UNCONFIRMED, UNCONFIRMED, UNCONFIRMED};
    char name[NUM] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int& A = suspect[0], & B = suspect[1], & C = suspect[2], & D = suspect[3], & E = suspect[4], & F = suspect[5];

    /* 重新整理线索顺序为：
    *    C、D中有且仅有一人作案；
    *    B、C或同时作案，或与本案无关；
    *    A、B至少有一人作案；
    *    A、D不可能是同案犯；
    *    如果D没有参与作案，则E也不可能参与作案；
    *    A、E、F三人中至少有两人参与作案；
    */
    
    for (j = 2; j < 4; j++) {
        for (i = 0; i < NUM; i++) {
            suspect[i] = UNCONFIRMED;
        }
        suspect[j] = YES;

        // C、D中有且仅有一人作案
        if (YES == C) {
            D = NO;
        }
        else if (YES == D) {
            C = NO;
        }

        // 上面确定了C的状态，这里可以直接确定B
        // B、C或同时作案，或与本案无关
        if (YES == C) {
            B = YES;
        }
        else {
            B = NO;
        }

        // B、C、D的状态此时完全确定，开始寻找下一个需要分条件套路的突破点

        // A、B至少有一人作案
        if (NO == B) {
            A = YES;
            // 此时A、D的状态都已知，则判断是否符合条件
            // A、D不可能是同案犯
            if (YES == D) {
                // 如果进入此判断，说明前面都推断错误
                continue;
            }
            // 如果D没有参与作案，则E也不可能参与作案
            E = NO;
            // 此时A、E已知
            // A、E、F三人中至少有两人参与作案
            F = YES;
            // 输出
            for (i = 0; i < NUM; i++) {
                cout << name[i] << '\t' << suspect[i] << endl;
            }
        }
        else
        {
            for (i = NO; i <= YES; i++) {
                A = i;
                // 此时A、B、C、D都已知
                if (NO == A) {
                    // A、E、F三人中至少有两人参与作案
                    E = YES;
                    F = YES;
                    // 验证：如果D没有参与作案，则E也不可能参与作案
                    if (NO == D) {
                        continue;
                    }
                    // 输出
                    for (i = 0; i < NUM; i++) {
                        cout << name[i] << '\t' << suspect[i] << endl;
                    }
                }
                else {
                    // A、D不可能是同案犯
                    if (YES == D) {
                        continue;
                    }
                    // 如果D没有参与作案，则E也不可能参与作案
                    E = NO;
                    // 此时A、E都已知
                    // A、E、F三人中至少有两人参与作案
                    F = YES;
                    // 输出
                    for (i = 0; i < NUM; i++) {
                        cout << name[i] << '\t' << suspect[i] << endl;
                    }
                }
            }
        }
    }

    return;
}