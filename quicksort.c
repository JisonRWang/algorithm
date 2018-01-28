/* ��������
*/
#include <stdio.h>

/* left��right֮��Ŀ�� */
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

/* �������򣬴����������� */
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

/* ������ֵ�����ȡ��ֵ����������ֵ��(right - 1)λ�ô������ݽ�����
*  ������̲�Ҫ�����κ��ⲿ�������̣����˼·���ҡ��ú���ֻҪʵ��
*  ������˵�Ĺ��ܼ��ɡ�
*/
int getmedian3(char *array, int left, int right)
{
    int center;

    /* ��left, right center���߰���left < center < right��˳������ */
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

    /* ��center��right - 1λ�ô������ݽ��� */
    swap(&array[center], &array[right - 1]);
    
    return array[right - 1];
}

/* tips: �ú����ڲ���û�иı�left��right�����ֵ */
void quicksort(char *array, int left, int right)
{
    int i, j;
    char pivot;    
    
    if (left + CUTOFF <= right) /* ���ι��̵ġ��֡�����: left + CUTOFF ��Ȼ�ﲻ��rightʱ�ͽ��С��֡����� */
    {
        /* ������̽���ֵ�ŵ�(right - 1)λ�ã����ұ�֤left����ֵС�ڸ�ֵ��right����ֵ���ڸ�ֵ */
        pivot = getmedian3(array, left, right);
    
        /* ��Ϊright����ֵһ������pivot����������j��pivot��λ�ÿ�ʼ����
        *  left����ֵС��pivot��(right - 1)����ֵ���Ǹ�ֵ������ѭ������ֱ��++��--
        */
        i = left, j = right - 1;
        for (;;)
        {
            while (array[++i] < pivot) {} /* ���������Ҵ���pivot���� */
            while (array[--j] > pivot) {} /* ����������С��pivot���� */
            if (i < j)
            {
                swap(&array[i], &array[j]);
            }
            else
            {
                break;
            }
        }
        
        /* ��ʱij���㣬����iλ�ô���������pivot�����Խ���һ�¡�
        *  ����֮��i������pivot����array�ֳ�����, i�����С��pivot��i����Ĵ���pivot
        */
        swap(&array[i], &array[right - 1]);
        
        /* ���ǡ��֡��ı��ʹ��� 
        *  tips: �ڵݹ�����У�arrayʼ�ն���ԭ��������Ǹ���ַ���仯�Ľ�����ÿ�εݹ鴫���left��right����
        */
        quicksort(array, left, i - 1);
        quicksort(array, i + 1, right);
    }
    else /* �ݹ�Ļ�����������ι��̵ġ��Ρ�����: left + CUTOFF > right��˵��left��right֮����������Ѿ������ˣ���ʱ��Ҫ�١��֡�������Ҫ���Ρ� */
    {
        /* ֱ���ò���������⼸�����ݴ���� */
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




