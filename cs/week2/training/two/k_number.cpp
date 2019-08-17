/* 题目
            K小数
*   描述
            这是一道很简单的问题。给你一个长度为 n 的序列 a1,a2,...,an，
     求这个序列的第 k 小的数。k 小数的定义为：将 a 从小到大排序
     后第 k 个位置的值。 由于输入数据量过大，输入只给出a1的值，
     并采用如下递推式生成剩余数据：
                                             a[i]=(p*a[i-1]+q) mod M (1<i≤n)
     其中，mod 运算的含义是：a mod b 的值为 a 除以 b 得到的余数。
*   输入格式
            输入第一行为两个正整数 n,k，含义见描述。
            第二行为四个非负整数 a1,p,q,M，你需要根据题目中给出式子
     计算完整序列。
*   输出格式
            输出一行一个正整数，表示第原序列第 k 小的数。
*   输入样例1
            5 4
            6 7 5 10
*   输出样例
            6
*   限制
            对于 20% 的数据，n≤10^2；
            对于40% 的数据，n≤10^4；
            对于 60% 的数据，n≤10^6；
            对于100% 的数据，1≤k≤n≤3×10^7，输入中其它数都在 int 范围内。
*   提示
            本题没有开启 STL，也就是说你不能使用 std::sort。
            [ 但是可以采用类似快排的思想，线性解决本题 ]
*   思路
            使用<<数据结构与算法-C 语言描述>> 中的写法
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

int g_n;
int g_k;

int *g_mem;

#define    CUTOFF    (3)

static inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return ;
}

void insertionsort(int *array, int len)
{
    int i, j;
    int tmp;
    
    for (i = 1; i < len; i++)
    {
        tmp = array[i];
        for (j = i; j - 1 >= 0; j--)
        {
            if (array[j - 1] > tmp)
            {
                array[j] = array[j - 1];
            }
            else
            {
                break;
            }
        }
        array[j] = tmp;
    }

    return ;
}

int getmedian3(int *array, int left, int right)
{
    int center;

    center = (left + right) / 2;
    if (array[left] > array[center])
    {
        swap(&array[left], &array[center]);
    }
    if (array[left] > array[right])
    {
        swap(&array[left], &array[right]);
    }
    if (array[center] > array[right])
    {
        swap(&array[center], &array[right]);
    }

    swap(&array[center], &array[right - 1]);
    
    return array[right - 1];
}

void quicksort(int *array, int left, int right, int k)
{
    int i, j;
    int pivot;    
    
    if (left + CUTOFF <= right) 
    {
        pivot = getmedian3(array, left, right);
    
        i = left, j = right - 1;
        for (;;)
        {
            while (array[++i] < pivot) {} 
            while (array[--j] > pivot) {} 
            if (i < j)
            {
                swap(&array[i], &array[j]);
            }
            else
            {
                break;
            }
        }
        
        /* 这句必须写在下面的判断之外，而且一定要写在继续递归之前，因为如果i != k，那么必须 
              *  继续递归，但在继续递归之前，一定要将pivot放到他自己该去的位置，而不能继续留在(right - 1)
              *  处，因为那样会导致实际大小的数据没到它实际应该去的位置，最终导致逻辑错误，尤其在
              *  递归的时候，一层的错误会叠加到下一层，最终导致几何级的错误累积！！！
              */
        swap(&array[i], &array[right - 1]);
        
        /* 查找第k个大小的数 */
        if (k == i)
        {
            /* error: printf("the num is %d\n", (int)array[right - 1]);(这句对应的swap(&array[i], &array[right - 1])
                     *  不在上面的位置，而在下面的两个else中。
                     */
            printf("%d\n", array[i]);
        }
        else if (k < i)
        {
            quicksort(array, left, i - 1, k);
        }
        else
        {
            quicksort(array, i + 1, right, k);
        }
        
#if 0
        /* 原快速排序算法的过程 */
        quicksort(array, left, i - 1);
        quicksort(array, i + 1, right);
#endif
    }
    else /* tips: 这一步很重要，而且很容易忽略 */
    {
        /* 能进到这里，说明虽然第k个数落到了闭区间[left, right]范围内但是该区间的大小不足CUTOFF，而 
              *  insertionsort()会将[left, right]范围内的数排一遍，使该区间内的数按序排列，因此，第k个数就是array[k]。
              *  tips: left和right始终都是以array为起点的下标!!!
              */
        insertionsort(array + left, right - left + 1);
        printf("%d\n", array[k]);
    }
    
    return ;
}

void init()
{
    int i;
    long long p, q, M, tmp;

    scanf("%d %d", &g_n, &g_k);
    getchar();

    // 从1 开始，a1,p,q,M
    g_mem = new int[g_n+1];
    scanf("%d %lld %lld %lld", &g_mem[1], &p, &q, &M);

    // a[i]=(p*a[i-1]+q) mod M (1<i≤n)
    for (i = 2; i <= g_n; i++) {
        // 取余之前的乘积会很大，所以要用s64 来存储
        tmp = (p * g_mem[i-1] + q) % M;
        g_mem[i] = (int)tmp;
    }

    return;
}

void end()
{
    delete[] g_mem;

    return;
}

int main()
{
    init();

    quicksort(g_mem, 1, g_n, g_k);

    end();

    return 0;
}
