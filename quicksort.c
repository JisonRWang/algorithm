/* 快速排序
*/
#include <stdio.h>

/* left和right之间的跨度 */
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

/* 插入排序，处理少量数据 */
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

/* 三数中值定理获取中值，并将该中值与(right - 1)位置处的数据交换。
*  这个过程不要考虑任何外部处理流程，会把思路搞乱。该函数只要实现
*  上面所说的功能即可。
*/
int getmedian3(char *array, int left, int right)
{
    int center;

    /* 将left, right center三者按照left < center < right的顺序排列 */
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

    /* 将center与right - 1位置处的数据交换 */
    swap(&array[center], &array[right - 1]);
    
    return array[right - 1];
}

/* tips: 该函数内部并没有改变left和right本身的值 */
void quicksort(char *array, int left, int right)
{
    int i, j;
    char pivot;    
    
    if (left + CUTOFF <= right) /* 分治过程的“分”过程: left + CUTOFF 仍然达不到right时就进行“分”处理 */
    {
        /* 这个过程将中值放到(right - 1)位置，并且保证left处的值小于该值，right处的值大于该值 */
        pivot = getmedian3(array, left, right);
    
        /* 因为right处的值一定大于pivot，所以这里j从pivot的位置开始即可
        *  left处的值小于pivot，(right - 1)处的值就是该值，所以循环条件直接++和--
        */
        i = left, j = right - 1;
        for (;;)
        {
            while (array[++i] < pivot) {} /* 从左向右找大于pivot的数 */
            while (array[--j] > pivot) {} /* 从右向左找小于pivot的数 */
            if (i < j)
            {
                swap(&array[i], &array[j]);
            }
            else
            {
                break;
            }
        }
        
        /* 此时ij交汇，并且i位置处的数大于pivot，所以交换一下。
        *  交换之后，i处就是pivot，将array分成两段, i左面的小于pivot，i右面的大于pivot
        */
        swap(&array[i], &array[right - 1]);
        
        /* 这是“分”的本质过程 
        *  tips: 在递归过程中，array始终都是原来最初的那个地址，变化的仅仅是每次递归传入的left和right而已
        */
        quicksort(array, left, i - 1);
        quicksort(array, i + 1, right);
    }
    else /* 递归的基本情况，分治过程的“治”过程: left + CUTOFF > right，说明left和right之间的数据量已经很少了，此时不要再“分”，而是要“治” */
    {
        /* 直接用插入排序把这几个数据处理掉 */
        insertionsort(array + left, right - left + 1);
    }
    
    return ;
}

int main(int argc, char **argv)
{
    int i;
    char array[100];

    for (i = 100; i > 0; i--)
    {
        array[100 - i] = i;
    }

    for (i = 0; i < 100; i++)
    {
        printf("%3d ", (int)array[i]);
        
        if (0 == (i + 1) % 10)
        {
            printf("\n");
        }
    }
    
    quicksort(array, 0, 99);
    printf("=======================================\n");
    
    for (i = 0; i < 100; i++)
    {
        printf("%3d ", (int)array[i]);
        
        if (0 == (i + 1) % 10)
        {
            printf("\n");
        }
    }

    return 0;
}




