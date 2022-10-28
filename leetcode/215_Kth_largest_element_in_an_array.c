/* 找到数组中的第K个最大元素
 * 思路：使用大根堆的堆排序
 * 39 / 39 test cases passed
 * Runtime: 208 ms
 * Memory Usage: 13.4 MB
 * */

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) 
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}

int big_heap_delete_peak(int *heap)
{
    int peak;
    int i, child;
    int heap_size;

    heap_size = heap[0];
    peak = heap[1];
    heap[1] = heap[heap_size];
    heap[0] = --heap_size;

    // 开始下滤
    for (i = 1; (i<<1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            heap[child] <= heap[child+1]) {
            child++;
        }

        if (heap[i] >= heap[child]) {
            break;
        }

        swap(&heap[i], &heap[child]);
    }

    return peak;
}

// 构建堆
void create_big_heap(int *heap)
{
    int heap_size;
    int i, j, child;

    heap_size = heap[0];

    // 从次底层开始构建，也就是从最后的叶子节点的父节点开始构建
    for (i = heap_size/2; i >= 1; i--) {
        // j 用于迭代子节点，注意，循环条件必须是“小于等于”而不是“小于”
        // 因为有右子节点就是“小于”，如果仅有左子节点就是“等于”
        for (j = i; (j<<1) <= heap_size; j = child) {
            child = j << 1;

            // 如果存在右子节点，则在两个子节点中找到最大的那个
            // 第一个判断成立，则表明一定存在右子节点
            if (child < heap_size &&
                heap[child] <= heap[child+1]) {
                // 切换到右子节点
                child++;
            }

            if (heap[j] >= heap[child]) {
                break;
            }

            swap(&heap[j], &heap[child]);
        }
    }

    return;
}

int findKthLargest(int* nums, int numsSize, int k){
    int i, val;
    int *heap = NULL;

    heap = (int *)malloc(sizeof(int) * (numsSize + 1));

    heap[0] = numsSize;
    for (int i = 0; i < numsSize; i++) {
        heap[i + 1] = nums[i];
    }
    
    create_big_heap(heap);

    for (i = 1; i <= k; i++) {
        val = big_heap_delete_peak(heap);
    }

    free(heap);

    return val;
}
