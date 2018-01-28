/* 希尔排序 
*  希尔排序一定要结合插入排序来分析，其实非常简单，希尔排序与
*  插入排序的本质是一样的，只不过插入排序的“插入”过程是逐个元
*  素进行，而希尔排序的“插入”过程是每increment间隔进行。
*/
#include <stdio.h>

void shellsort(char *array, int len)
{
    int i, j, increment; /* 涉及减法后与0的比较, 所以必须是有符号的, 否则在大量数据的时候会出现异常 */
    char tmp;
    
    /* 异常处理 */
    if (len <= 1)
    {
        return ;
    }
    
    /* 用于设置间隔的循环 */
    for (increment = len / 2; increment > 0; increment /= 2)
    {
        /* for (i = 1; i < len; i++) */
        for (i = increment; i < len; i++)
        {
            tmp = array[i];
            /* for (j = i; j - 1 >= 0; j--) */
            for (j = i; j - increment >= 0; j -= increment)
            {
                /* if (array[j - 1] > tmp) */
                if (array[j - increment] > tmp)
                {
                    /* array[j] = array[j - 1]; */
                    array[j] = array[j - increment];
                }
                else
                {
                    break;
                }
            }
            array[j] = tmp;
        }
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
    
    shellsort(array, 100);
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




