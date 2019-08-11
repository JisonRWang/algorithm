/* ��Ŀ��
*  ��¥���ߵ�¥�¹���h��̨�ף�ÿһ���������߷�
*     ��һ��̨�ף�
*     ������̨�ף�
*     ������̨�ף�  
*  һ���ж�������¥�ݷ������ֱ���ʲô��
*  ������⣺��ʵ����ν����¥�����Ե�Ч��������������Զ����º��Ե�����������¥�ķ���û�й�ϵ
*/

#include <iostream>
#include <memory.h>

using namespace std;

// �Զ�����
int from_top_to_bottom(int *memo, int stairs)
{
    int step = 0, sum = 0;

    // �ݹ��
    if (0 == stairs) {
        return 1;
    }

    if (0 != memo[stairs]) {
        return memo[stairs];
    }

    for (step = 1; step <= 3; step++) {
        if (step <= stairs) {
            sum += from_top_to_bottom(memo, stairs-step);
        }
    }
    memo[stairs] = sum;

    return sum;
}

// �Զ�����ʹ�ñ���¼
void updown_stairs_from_top_to_bottom(int stairs)
{
    int* memo = nullptr;
    int sum = 0, tmp = stairs + 1;

    if (stairs <= 0) {
        cout << stairs << endl;
        return;
    }
    
    // TODO new ʧ�ܴ���
    // memo[0]û�ã���������̨������memo[index]Ϊ��Ӧ̨��������¥������
    memo = new int[tmp];
    memset(memo, 0, sizeof(int) * tmp);

    sum = from_top_to_bottom(memo, stairs);
    cout << "output: " << sum << endl;

    delete [] memo;
    return;
}

// �Ե�����ʹ�ö�̬�滮����������
void updown_stairs_from_bottom_to_top_iteration(int stairs)
{
    int arr[4] = {0, 1, 2, 4};
    int i = 0, tmp_a = arr[1], tmp_b = arr[2], tmp_c = arr[3], sum = 0;

    if (stairs < 0) {
        cout << stairs << endl;
        return;
    }
    if (0 <= stairs && stairs <= 3) {
        cout << arr[stairs] << endl;
        return;
    }

    for (i = 4; i <= stairs; i++) {
        // sum = ʣһ��̨�� �ǵ��Ϸ��� + ʣ����̨��~ + ʣ����̨��~
        sum = tmp_a + tmp_b + tmp_c;
        tmp_a = tmp_b;
        tmp_b = tmp_c;
        tmp_c = sum;
    }

    cout << "output: " << sum << endl;

    return;
}

// �Ե�����ʹ�ö�̬�滮��β�ݹ鷨��
int bottom_to_top_recursion(int stairs, int a, int b, int c)
{
    if (0 == stairs) {
        return c;
    }
    return bottom_to_top_recursion(stairs-1, b, c, a+b+c);
}
void updown_stairs_from_bottom_to_top_recursion(int stairs)
{
    int sum = 0;
    int arr[4] = { 0, 1, 2, 4 }; // ����Ϊ̨������ֵΪ̨��������Ӧ�ķ�����

    if (stairs < 0) {
        cout << stairs << endl;
        return;
    }
    if (0 <= stairs && stairs <= 3) {
        cout << arr[stairs] << endl;
        return;
    }

    // �����stairs����Ϊ����ʣ���ټ�̨����Ҫ�ߡ�
    sum = bottom_to_top_recursion(stairs-3, arr[1], arr[2], arr[3]);
    cout << "output: " << sum << endl;

    return;
}

void updown_stairs()
{
    int stairs;

    cin >> stairs;

    cout << "�Զ�����" << endl;
    updown_stairs_from_top_to_bottom(stairs);

    cout << "�Ե����ϣ���������" << endl;
    updown_stairs_from_bottom_to_top_iteration(stairs);

    cout << "�Ե����ϣ�β�ݹ飩" << endl;
    updown_stairs_from_bottom_to_top_recursion(stairs);

    return;
}