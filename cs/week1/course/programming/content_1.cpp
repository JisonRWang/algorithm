/* ��Ŀ��
*  ĳ�������Ӷ��漰6�������˵�һ׮�ɰ����з���������������������������Ѽ������������鱨��
*     A��B������һ��������
*     A��E��F���������������˲���������
*     A��D��������ͬ������
*     B��C��ͬʱ���������뱾���޹أ�
*     C��D�����ҽ���һ��������
*     ���Dû�в�����������EҲ�����ܲ�������
*  ��̽��������ҳ�
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

    /* ������������˳��Ϊ��
    *    C��D�����ҽ���һ��������
    *    B��C��ͬʱ���������뱾���޹أ�
    *    A��B������һ��������
    *    A��D��������ͬ������
    *    ���Dû�в�����������EҲ�����ܲ���������
    *    A��E��F���������������˲���������
    */
    
    for (j = 2; j < 4; j++) {
        for (i = 0; i < NUM; i++) {
            suspect[i] = UNCONFIRMED;
        }
        suspect[j] = YES;

        // C��D�����ҽ���һ������
        if (YES == C) {
            D = NO;
        }
        else if (YES == D) {
            C = NO;
        }

        // ����ȷ����C��״̬���������ֱ��ȷ��B
        // B��C��ͬʱ���������뱾���޹�
        if (YES == C) {
            B = YES;
        }
        else {
            B = NO;
        }

        // B��C��D��״̬��ʱ��ȫȷ������ʼѰ����һ����Ҫ��������·��ͻ�Ƶ�

        // A��B������һ������
        if (NO == B) {
            A = YES;
            // ��ʱA��D��״̬����֪�����ж��Ƿ��������
            // A��D��������ͬ����
            if (YES == D) {
                // ���������жϣ�˵��ǰ�涼�ƶϴ���
                continue;
            }
            // ���Dû�в�����������EҲ�����ܲ�������
            E = NO;
            // ��ʱA��E��֪
            // A��E��F���������������˲�������
            F = YES;
            // ���
            for (i = 0; i < NUM; i++) {
                cout << name[i] << '\t' << suspect[i] << endl;
            }
        }
        else
        {
            for (i = NO; i <= YES; i++) {
                A = i;
                // ��ʱA��B��C��D����֪
                if (NO == A) {
                    // A��E��F���������������˲�������
                    E = YES;
                    F = YES;
                    // ��֤�����Dû�в�����������EҲ�����ܲ�������
                    if (NO == D) {
                        continue;
                    }
                    // ���
                    for (i = 0; i < NUM; i++) {
                        cout << name[i] << '\t' << suspect[i] << endl;
                    }
                }
                else {
                    // A��D��������ͬ����
                    if (YES == D) {
                        continue;
                    }
                    // ���Dû�в�����������EҲ�����ܲ�������
                    E = NO;
                    // ��ʱA��E����֪
                    // A��E��F���������������˲�������
                    F = YES;
                    // ���
                    for (i = 0; i < NUM; i++) {
                        cout << name[i] << '\t' << suspect[i] << endl;
                    }
                }
            }
        }
    }

    return;
}