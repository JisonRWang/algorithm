/* 题目：
*  从楼上走到楼下共有h个台阶，每一步有三种走法
*     走一个台阶；
*     走两个台阶；
*     走三个台阶；  
*  一共有多少种下楼梯方案？分别是什么？
*  个人理解：其实无所谓上下楼，可以等效于迈步。这里的自顶向下和自底向上与上下楼的方向没有关系
*/

#include <iostream>
#include <memory.h>

using namespace std;

// 自顶向下
int from_top_to_bottom(int *memo, int stairs)
{
    int step = 0, sum = 0;

    // 递归基
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

// 自顶向下使用备忘录
void updown_stairs_from_top_to_bottom(int stairs)
{
    int* memo = nullptr;
    int sum = 0, tmp = stairs + 1;

    if (stairs <= 0) {
        cout << stairs << endl;
        return;
    }
    
    // TODO new 失败处理
    // memo[0]没用，索引代表台阶数，memo[index]为对应台阶数的上楼方法数
    memo = new int[tmp];
    memset(memo, 0, sizeof(int) * tmp);

    sum = from_top_to_bottom(memo, stairs);
    cout << "output: " << sum << endl;

    delete [] memo;
    return;
}

// 自底向上使用动态规划（迭代法）
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
        // sum = 剩一级台阶 是的上法数 + 剩两级台阶~ + 剩三级台阶~
        sum = tmp_a + tmp_b + tmp_c;
        tmp_a = tmp_b;
        tmp_b = tmp_c;
        tmp_c = sum;
    }

    cout << "output: " << sum << endl;

    return;
}

// 自底向上使用动态规划（尾递归法）
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
    int arr[4] = { 0, 1, 2, 4 }; // 索引为台阶数，值为台阶数所对应的方法数

    if (stairs < 0) {
        cout << stairs << endl;
        return;
    }
    if (0 <= stairs && stairs <= 3) {
        cout << arr[stairs] << endl;
        return;
    }

    // 这里的stairs含义为“还剩多少级台阶需要走”
    sum = bottom_to_top_recursion(stairs-3, arr[1], arr[2], arr[3]);
    cout << "output: " << sum << endl;

    return;
}

void updown_stairs()
{
    int stairs;

    cin >> stairs;

    cout << "自顶向下" << endl;
    updown_stairs_from_top_to_bottom(stairs);

    cout << "自底向上（迭代法）" << endl;
    updown_stairs_from_bottom_to_top_iteration(stairs);

    cout << "自底向上（尾递归）" << endl;
    updown_stairs_from_bottom_to_top_recursion(stairs);

    return;
}