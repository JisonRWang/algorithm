/* ��Ŀ
            KС��
*   ����
            ����һ���ܼ򵥵����⡣����һ������Ϊ n ������ a1,a2,...,an��
     ��������еĵ� k С������k С���Ķ���Ϊ���� a ��С��������
     ��� k ��λ�õ�ֵ�� ����������������������ֻ����a1��ֵ��
     ���������µ���ʽ����ʣ�����ݣ�
                                             a[i]=(p*a[i-1]+q) mod M (1<i��n)
     ���У�mod ����ĺ����ǣ�a mod b ��ֵΪ a ���� b �õ���������
*   �����ʽ
            �����һ��Ϊ���������� n,k�������������
            �ڶ���Ϊ�ĸ��Ǹ����� a1,p,q,M������Ҫ������Ŀ�и���ʽ��
     �����������С�
*   �����ʽ
            ���һ��һ������������ʾ��ԭ���е� k С������
*   ��������1
            5 4
            6 7 5 10
*   �������
            6
*   ����
            ���� 20% �����ݣ�n��10^2��
            ����40% �����ݣ�n��10^4��
            ���� 60% �����ݣ�n��10^6��
            ����100% �����ݣ�1��k��n��3��10^7������������������ int ��Χ�ڡ�
*   ��ʾ
            ����û�п��� STL��Ҳ����˵�㲻��ʹ�� std::sort��
            [ ���ǿ��Բ������ƿ��ŵ�˼�룬���Խ������ ]
*   ˼·
            ʹ��<<���ݽṹ���㷨-C ��������>> �е�д��
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

    // ��1 ��ʼ��a1,p,q,M
    g_mem = new int[g_n+1];
    scanf("%d %lld %lld %lld", &g_mem[1], &p, &q, &M);

    // a[i]=(p*a[i-1]+q) mod M (1<i��n)
    for (i = 2; i <= g_n; i++) {
        // ȡ��֮ǰ�ĳ˻���ܴ�����Ҫ��s64 ���洢
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
