/* heap
*  ������
*      ����insert�������ѵ�Ч��
*      percolate�����˷���Ч�ʸ��ߣ�
*  �ѷ���
*      С����
*      �����
*  ����
*      init
*      build_heap
*      insert
*      delete
*      end
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

// tips: a + b �������ʱ����ʹ���������
void swap(int& a, int& b) {
    a = a + b;
    b = a - b;
    a = a - b;
    return;
}

// ����֮ǰҪ���ѵ����һ��ֵ�����Ѷ����Ա�֤���˽��������Ȼ����ȫ������
int small_heap_delete_peak(int* heap)
{
    int i, peak;
    int child, heap_size;

    heap_size = heap[0];
    if (heap_size < 1) {
        // ����һ�����в����ڵ�ֵ��Ҫ����ʵ����������������ݶ�-1
        return -1;
    }
    
    // ȡ�߶Ѷ���ֵ
    peak = heap[1];

    // ���ѵ����һ��ֵ�����Ѷ�
    heap[1] = heap[heap_size--];

    // ��ʼ����
    for (i = 1; (i << 1) <= heap_size; i = child) {
        // child��ʼ��Ϊ���ӽڵ�
        child = i << 1;

        // ǰһ���жϳ�����˵��һ���������ӽڵ�
        if (child < heap_size &&
            heap[child] >= heap[child+1]) {
            // �����У�������ȵ�ʱ����Ȼ�����ӽڵ�˵�£�
            child++;
        }

        if (heap[i] <= heap[child]) {
            break;
        }
        swap(heap[i], heap[child]);
    }

    heap[0] = heap_size;
    return peak;
}

int big_heap_delete_peak(int* heap)
{
    int i, peak;
    int child, heap_size;

    heap_size = heap[0];
    if (heap_size < 1) {
        // ����һ�����в����ڵ�ֵ��Ҫ����ʵ����������������ݶ�-1
        return -1;
    }

    // ȡ�߶Ѷ���ֵ
    peak = heap[1];

    // ���ѵ����һ��ֵ�����Ѷ�
    heap[1] = heap[heap_size--];

    // ��ʼ����
    for (i = 1; (i << 1) <= heap_size; i = child) {
        // child��ʼ��Ϊ���ӽڵ�
        child = i << 1;

        // ǰһ���жϳ�����˵��һ���������ӽڵ�
        if (child < heap_size &&
            heap[child] <= heap[child + 1]) {
            // �����У�������ȵ�ʱ����Ȼ�����ӽڵ�˵�£�
            child++;
        }

        if (heap[i] >= heap[child]) {
            break;
        }
        swap(heap[i], heap[child]);
    }

    heap[0] = heap_size;
    return peak;
}

void insert_small_heap(int* heap, int node)
{
    int i;
    int dad, heap_size;

    // TODO: ����ȱ��Խ���飬���������ʱ��Ӧ�ô���Խ����
    heap_size = heap[0];
    heap[++heap_size] = node; // ���½ڵ���ڶѵ���ĩβ
    heap[0] = heap_size;      // ���¶ѵĴ�С

    // ����
    for (i = heap_size; (i >> 1) >= 1; i = dad) {
        dad = i >> 1;
        if (heap[i] >= heap[dad]) {
            break;
        }
        swap(heap[i], heap[dad]);
    }

    return;
}

void insert_big_heap(int* heap, int node)
{
    int i;
    int dad, heap_size;

    // TODO: ����ȱ��Խ���飬���������ʱ��Ӧ�ô���Խ����
    heap_size = heap[0];
    heap[++heap_size] = node; // ���½ڵ���ڶѵ���ĩβ
    heap[0] = heap_size;      // ���¶ѵĴ�С

    // ����
    for (i = heap_size; (i >> 1) >= 1; i = dad) {
        dad = i >> 1;
        if (heap[i] <= heap[dad]) {
            break;
        }
        swap(heap[i], heap[dad]);
    }

    return;
}

// tips: ��0��Ԫ���Ѿ�����˶ѵĴ�С
void create_small_heap(int* heap)
{
    int child;
    int i, j, heap_size;

    heap_size = heap[0];

    // �Ӵεײ㿪ʼ�����ϣ�ÿ��ֻ��֤��ǰ�ڵ㼰�������ӽڵ�Ķ�������
    for (i = heap_size/2; i >= 1; i--) {
        // ��Ϊ�ǴӴεײ㿪ʼ������������Ҫ����Ľڵ����������ӽڵ�
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            // ��һ���жϳ�����˵��һ���������ӽڵ�
            if (child < heap_size &&
                heap[child] >= heap[child+1]) {
                child++;
            }

            // �ӽڵ����¶��Ѿ�����ã������������ֱ������ѭ��
            if (heap[j] <= heap[child]) {
                break;
            }
            swap(heap[j], heap[child]);
        }
    }

    return;
}

// tips: ��0��Ԫ���Ѿ�����˶ѵĴ�С
void create_big_heap(int* heap)
{
    int child;
    int i, j, heap_size;

    heap_size = heap[0];

    // �Ӵεײ㿪ʼ�����ϣ�ÿ��ֻ��֤��ǰ�ڵ㼰�������ӽڵ�Ķ�������
    for (i = heap_size / 2; i >= 1; i--) {
        // ��Ϊ�ǴӴεײ㿪ʼ������������Ҫ����Ľڵ����������ӽڵ�
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            // ��һ���жϳ�����˵��һ�������ӽڵ�
            if (child < heap_size &&
                heap[child] <= heap[child+1]) {
                child++;
            }

            // �ӽڵ����¶��Ѿ�����ã������������ֱ������ѭ��
            if (heap[j] >= heap[child]) {
                break;
            }
            swap(heap[j], heap[child]);
        }
    }

    return;
}

int* init(int n)
{
    // ��0��Ԫ�ش�ŶѵĴ�С
    int* heap = new int[n+1];
    return heap;
}

int* end(int* heap)
{
    delete[] heap;
    heap = nullptr;
    return heap;
}

void heap()
{
    int i, n; 
    int input[200];
    int* heap_big = nullptr;    // �����
    int* heap_small = nullptr;  // С����

    scanf("%d", &n);
    if (n < 1) {
        cout << "Wrong input: n = " << n << endl;
        return;
    }

    heap_big = init(n);
    heap_small = init(n);
    cout << "���������ݣ� ";
    for (i = 1; i < n + 1; i++) {
        scanf("%d", &heap_big[i]);
        heap_small[i] = heap_big[i];
        input[i] = heap_big[i];
    }

    heap_big[0] = n;
    create_big_heap(heap_big);
    cout << "����ѣ� ";
    for (i = 0; i < n + 1; i++) {
        printf("%d ", heap_big[i]);
    }
    cout << endl;
    cout << "ɾ��peak˳�� ";
    for (i = 1; i < n + 1; i++) {
        printf("%d ", big_heap_delete_peak(heap_big));
    }
    cout << endl;
    cout << "�������ݣ� ";
    for (i = 1; i < n + 1; i++) {
        cout << input[i] << " ";
        insert_big_heap(heap_big, input[i]);
    }
    cout << endl;
    cout << "����ѣ� ";
    for (i = 0; i < n + 1; i++) {
        printf("%d ", heap_big[i]);
    }
    cout << endl << "ɾ��peak˳�� ";
    for (i = 1; i < n + 1; i++) {
        printf("%d ", big_heap_delete_peak(heap_big));
    }
    cout << endl << "**************************************" << endl;

    heap_small[0] = n;
    create_small_heap(heap_small);
    cout << "С���ѣ� ";
    for (i = 0; i < n + 1; i++) {
        printf("%d ", heap_small[i]);
    }
    cout << endl;
    cout << "ɾ��peak˳�� ";
    for (i = 1; i < n + 1; i++) {
        printf("%d ", small_heap_delete_peak(heap_small));
    }
    cout << endl << "�������ݣ� ";
    for (i = 1; i < n + 1; i++) {
        cout << input[i] << " ";
        insert_small_heap(heap_small, input[i]);
    }
    cout << endl;
    cout << "С���ѣ� ";
    for (i = 0; i < n + 1; i++) {
        printf("%d ", heap_small[i]);
    }
    cout << endl;
    cout << "ɾ��peak˳�� ";
    for (i = 1; i < n + 1; i++) {
        printf("%d ", small_heap_delete_peak(heap_small));
    }

    heap_small = end(heap_small);
    heap_big = end(heap_big);

    return;
}