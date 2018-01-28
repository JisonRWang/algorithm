/* ϣ������ 
*  ϣ������һ��Ҫ��ϲ�����������������ʵ�ǳ��򵥣�ϣ��������
*  ��������ı�����һ���ģ�ֻ������������ġ����롱���������Ԫ
*  �ؽ��У���ϣ������ġ����롱������ÿincrement������С�
*/
#include <stdio.h>

void shellsort(char *array, int len)
{
    int i, j, increment; /* �漰��������0�ıȽ�, ���Ա������з��ŵ�, �����ڴ������ݵ�ʱ�������쳣 */
    char tmp;
    
    /* �쳣���� */
    if (len <= 1)
    {
        return ;
    }
    
    /* �������ü����ѭ�� */
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




