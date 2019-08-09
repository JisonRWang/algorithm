/* heap
*  构建堆
*      连续insert法（建堆低效）
*      percolate法（此方法效率更高）
*  堆分类
*      小根堆
*      大根堆
*  操作
*      init
*      build_heap
*      insert
*      delete
*      end
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

// tips: a + b 不会溢出时才能使用这个方法
void swap(int& a, int& b) {
    a = a + b;
    b = a - b;
    a = a - b;
    return;
}

// 下滤之前要将堆底最后一个值掰到堆顶，以保证下滤结束后堆依然是完全二叉树
int small_heap_delete_peak(int* heap)
{
    int i, peak;
    int child, heap_size;

    heap_size = heap[0];
    if (heap_size < 1) {
        // 返回一个堆中不存在的值，要根据实际情况决定，这里暂定-1
        return -1;
    }
    
    // 取走堆顶的值
    peak = heap[1];

    // 将堆的最后一个值掰到堆顶
    heap[1] = heap[heap_size--];

    // 开始下滤
    for (i = 1; (i << 1) <= heap_size; i = child) {
        // child初始化为左子节点
        child = i << 1;

        // 前一个判断成立，说明一定存在右子节点
        if (child < heap_size &&
            heap[child] >= heap[child+1]) {
            // 靠右行（左右相等的时候，依然拿右子节点说事）
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
        // 返回一个堆中不存在的值，要根据实际情况决定，这里暂定-1
        return -1;
    }

    // 取走堆顶的值
    peak = heap[1];

    // 将堆的最后一个值掰到堆顶
    heap[1] = heap[heap_size--];

    // 开始下滤
    for (i = 1; (i << 1) <= heap_size; i = child) {
        // child初始化为左子节点
        child = i << 1;

        // 前一个判断成立，说明一定存在右子节点
        if (child < heap_size &&
            heap[child] <= heap[child + 1]) {
            // 靠右行（左右相等的时候，依然拿右子节点说事）
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

    // TODO: 这里缺少越界检查，后面操作的时候应该带上越界检查
    heap_size = heap[0];
    heap[++heap_size] = node; // 将新节点挂在堆的最末尾
    heap[0] = heap_size;      // 更新堆的大小

    // 上滤
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

    // TODO: 这里缺少越界检查，后面操作的时候应该带上越界检查
    heap_size = heap[0];
    heap[++heap_size] = node; // 将新节点挂在堆的最末尾
    heap[0] = heap_size;      // 更新堆的大小

    // 上滤
    for (i = heap_size; (i >> 1) >= 1; i = dad) {
        dad = i >> 1;
        if (heap[i] <= heap[dad]) {
            break;
        }
        swap(heap[i], heap[dad]);
    }

    return;
}

// tips: 第0个元素已经存放了堆的大小
void create_small_heap(int* heap)
{
    int child;
    int i, j, heap_size;

    heap_size = heap[0];

    // 从次底层开始逐步向上，每次只保证当前节点及其所有子节点的堆序性质
    for (i = heap_size/2; i >= 1; i--) {
        // 因为是从次底层开始处理，所以这里要处理的节点至少有左子节点
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            // 第一个判断成立，说明一定存在右子节点
            if (child < heap_size &&
                heap[child] >= heap[child+1]) {
                child++;
            }

            // 子节点往下都已经处理好，所以这里可以直接跳出循环
            if (heap[j] <= heap[child]) {
                break;
            }
            swap(heap[j], heap[child]);
        }
    }

    return;
}

// tips: 第0个元素已经存放了堆的大小
void create_big_heap(int* heap)
{
    int child;
    int i, j, heap_size;

    heap_size = heap[0];

    // 从次底层开始逐步向上，每次只保证当前节点及其所有子节点的堆序性质
    for (i = heap_size / 2; i >= 1; i--) {
        // 因为是从次底层开始处理，所以这里要处理的节点至少有左子节点
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            // 第一个判断成立，说明一定有右子节点
            if (child < heap_size &&
                heap[child] <= heap[child+1]) {
                child++;
            }

            // 子节点往下都已经处理好，所以这里可以直接跳出循环
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
    // 第0个元素存放堆的大小
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
    int* heap_big = nullptr;    // 大根堆
    int* heap_small = nullptr;  // 小根堆

    scanf("%d", &n);
    if (n < 1) {
        cout << "Wrong input: n = " << n << endl;
        return;
    }

    heap_big = init(n);
    heap_small = init(n);
    cout << "请输入数据： ";
    for (i = 1; i < n + 1; i++) {
        scanf("%d", &heap_big[i]);
        heap_small[i] = heap_big[i];
        input[i] = heap_big[i];
    }

    heap_big[0] = n;
    create_big_heap(heap_big);
    cout << "大根堆： ";
    for (i = 0; i < n + 1; i++) {
        printf("%d ", heap_big[i]);
    }
    cout << endl;
    cout << "删除peak顺序： ";
    for (i = 1; i < n + 1; i++) {
        printf("%d ", big_heap_delete_peak(heap_big));
    }
    cout << endl;
    cout << "插入数据： ";
    for (i = 1; i < n + 1; i++) {
        cout << input[i] << " ";
        insert_big_heap(heap_big, input[i]);
    }
    cout << endl;
    cout << "大根堆： ";
    for (i = 0; i < n + 1; i++) {
        printf("%d ", heap_big[i]);
    }
    cout << endl << "删除peak顺序： ";
    for (i = 1; i < n + 1; i++) {
        printf("%d ", big_heap_delete_peak(heap_big));
    }
    cout << endl << "**************************************" << endl;

    heap_small[0] = n;
    create_small_heap(heap_small);
    cout << "小根堆： ";
    for (i = 0; i < n + 1; i++) {
        printf("%d ", heap_small[i]);
    }
    cout << endl;
    cout << "删除peak顺序： ";
    for (i = 1; i < n + 1; i++) {
        printf("%d ", small_heap_delete_peak(heap_small));
    }
    cout << endl << "插入数据： ";
    for (i = 1; i < n + 1; i++) {
        cout << input[i] << " ";
        insert_small_heap(heap_small, input[i]);
    }
    cout << endl;
    cout << "小根堆： ";
    for (i = 0; i < n + 1; i++) {
        printf("%d ", heap_small[i]);
    }
    cout << endl;
    cout << "删除peak顺序： ";
    for (i = 1; i < n + 1; i++) {
        printf("%d ", small_heap_delete_peak(heap_small));
    }

    heap_small = end(heap_small);
    heap_big = end(heap_big);

    return;
}