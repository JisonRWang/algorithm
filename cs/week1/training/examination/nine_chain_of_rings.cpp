/* 题目
*     九连环
*  描述
*     九连环是一款经典的智力玩具，其规则与玩法见这里(https://chinesepuzzles.org/zh/nine-linked-rings-puzzle/) 。
*     一个经典的九连环如下图所示。我们按下图的示意，将环从左到右编号。
*     小C拿一个九连环玩了七七四十九天，将其中一些环解下了。现在，你拿着这个小C玩过的九连环，
*     问最少需要多少步，可以将所有环解下？其中，一步指将一个环解下，或将一个环挂上。
*  输入描述
*     第一行一个正整数n，表示被解下环的数量。
*     第二行有n个正整数x[i]，表示被解下的环的编号。
*  输出描述
*     输出将环解下的最少步数
*  样例输入
*     8
*     2 3 4 5 6 7 8 9
*  样例输出
*     1
*  数据范围
*     0≤n≤9,1≤xi≤9
*     时间限制：1 s
*     空间限制：512 MB
*  我的思路
*     解下第i环，需要先把第i-1环放上去，然后解下第i环，且前面1~i-2环都已经在下面，再把第i-1环解下
*     放上第i环，需要先把第i-1环放上去，再放上第i环，再把第i-1环解下
*     算出每一环单独在杆上时（即1~i-1环都不在杆上，解下i环的步骤数），将其接下来的步骤数，然后根
据输入数据判断当前哪些环在杆上，然后将在杆上的环依次序逐个解下（即叠加单独解下每个环时的步骤数即可）。
*     注意，这道题与普通的九连环求解问题不同，普通求解九连环是一口气求解N个环，并且这些环都是在杆上
的，而这道题里的环，是九个环中某几个环被解下，然后要把其余的环都解下。
*     注意，假设有四个环，将这四个环取下的步骤数和有三个环在下，第四个环在上面的情况时的步骤数是不同的，
四个环都在上面然后将这四个环取下的过程中，是不会出现前三个环在下面而第四个环在上面的情况的。也就是说，
四个环都在上面时，将四个环取下的过程并不是依环的排列顺序将其逐个取掉的，而是有一定的规则的。
*     我最初的想法应该是错的，开始我认为取下所有环的过程是逐个取下，但从取四个环的例子中可以看出，并不是这样。
*     算了，暂时放弃，想了几个小时都抽象不出来。。。/_\
*/

#if 0
#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

// 解下每个环的步骤数，第0个元素表示第0个环，即没有环，对应0步
static int solution_per_ring[10] = { 0 };

void calculating_per_ring_steps()
{
    int i, sum;

    solution_per_ring[0] = 0;
    solution_per_ring[1] = 1;

    // 解下前i个环的总步数，初始化为1表示在解下第2个环之前的所有环，总共有1步
    sum = 1; 
    for (i = 2; i < 10; i++) {
        // 先把第i-1个环放上，再解下第i个环，再把前i-1个环解下
        solution_per_ring[i] = 1 + 1 + solution_per_ring[i-1] /*+ sum*/;
        //sum += solution_per_ring[i];
    }

    return;
}

void nine_chain_rings()
{
    int i, sum; 

    calculating_per_ring_steps();

    for (i = 0; i < 10; i++) {
        cout << solution_per_ring[i] << " ";
    }

    //解下九连环需要的所有步骤数
    sum = 0;
    for (i = 1; i < 9; i++) {
        sum += solution_per_ring[i];
    }
    cout << sum;

    return;
}
#endif