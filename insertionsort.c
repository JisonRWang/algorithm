/* 插入排序 
*/
#include <stdio.h>

void insert_sort(char *array, int len)
{
    int i, j; /* 涉及减法后与0的比较, 所以必须是有符号的, 否则在大量数据的时候会出现异常 */
    char tmp;
    
    /* 异常处理 */
    if (len <= 1)
    {
        return ;
    }
    
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
    
    insert_sort(array, 100);
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




