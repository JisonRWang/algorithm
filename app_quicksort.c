/* ���������Ӧ��
*  �ÿ����㷨����һ�������е�k����С��������˭��k��0��ʼ
*/
#include <stdio.h>

#define    SIZE      100
#define    CUTOFF    (3)

/* ���������е��������ᱻչ���������������ʵ����������ǰ���������չ�����ǵ���һ��һ��ĺ����� 
*  ���������������ʹ��gcc -E �ᷢ��Ԥ����֮��ĸú���������һ��ĺ����������ˡ�
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
        
        /* ������д��������ж�֮�⣬����һ��Ҫд�ڼ����ݹ�֮ǰ����Ϊ���i != k����ô���� 
        *  �����ݹ飬���ڼ����ݹ�֮ǰ��һ��Ҫ��pivot�ŵ����Լ���ȥ��λ�ã������ܼ�������(right - 1)
        *  ������Ϊ�����ᵼ��ʵ�ʴ�С������û����ʵ��Ӧ��ȥ��λ�ã����յ����߼�����������
        *  �ݹ��ʱ��һ��Ĵ������ӵ���һ�㣬���յ��¼��μ��Ĵ����ۻ�������
        */
        swap(&array[i], &array[right - 1]);
        
        /* ���ҵ�k����С���� */
        if (k == i)
        {
            /* error: printf("the num is %d\n", (int)array[right - 1]);(����Ӧ��swap(&array[i], &array[right - 1])
            *  ���������λ�ã��������������else�С�
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
        /* ԭ���������㷨�Ĺ��� */
        quicksort(array, left, i - 1);
        quicksort(array, i + 1, right);
#endif
    }
    else /* tips: ��һ������Ҫ�����Һ����׺��� */
    {
        /* �ܽ������˵����Ȼ��k�����䵽�˱�����[left, right]��Χ�ڵ��Ǹ�����Ĵ�С����CUTOFF���� 
        *  insertionsort()�Ὣ[left, right]��Χ�ڵ�����һ�飬ʹ�������ڵ����������У���ˣ���k��������array[k]��
        *  tips: left��rightʼ�ն�����arrayΪ�����±�!!!
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




