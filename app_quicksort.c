/* 快速排序的应用
*  用快排算法查找一个数列中第k个大小的数据是谁，k从0开始
*/
#include <stdio.h>

#define    SIZE      100
#define    CUTOFF    (3)

/* 并不是所有的内联都会被展开，编译器会根据实际情况决定是把内联函数展开还是当做一个一般的函数， 
*  比如该内联函数，使用gcc -E 会发现预编译之后的该函数被当做一般的函数来处理了。
*/
static inline void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
    return ;
}

void insertionsort(char *array, int len)
{
    int i, j;
    char tmp;
    
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

int getmedian3(char *array, int left, int right)
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

void quicksort(char *array, int left, int right, int k)
{
    int i, j;
    char pivot;    
    
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
            printf("the num is %d\n", (int)array[i]);
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
        printf("By insertionsort(), the num is %d\n", (int)array[k]);
    }
    
    return ;
}

int main(int argc, char **argv)
{
    int i, k;
    char array[SIZE];
    
    if (1 == argc)
    {
        return 0;
    }
    k = atoi(argv[1]);

    for (i = SIZE; i > 0; i--)
    {
        array[SIZE - i] = i;
    }

    for (i = 0; i < SIZE; i++)
    {
        printf("%3d ", (int)array[i]);
        
        if (0 == (i + 1) % 10)
        {
            printf("\n");
        }
    }
    
    printf("=======================================\n");
    
    quicksort(array, 0, SIZE - 1, k);
        
    return 0;
}




