#include <stdio.h>
#include <stdlib.h>
/*
 *计数排序非常基础，他的主要目的是对整数排序并且会比普通的排序算法性能更好。
 *这个算法由以下步骤组成：
 *1)初始化一个计数数组，大小是输入数组中的最大的数。
 *2)遍历输入数组，遇到一个数就在计数数组对应的位置上加一。例如：遇到5，就将计数数组第五个位置的数加一。
 *3)把计数数组直接覆盖到输出数组（节约空间）。
 * 时间复杂度：O(n + k)，n是输入数组长度，k是最大的数的大小。
 * 空间复杂度：O(n + k)，n是输入数组长度，k是最大的数的大小。
 */
 //打印数组
void printArray(int *array, int size){
    int curr;
    for(curr = 0; curr < size; curr++){
        printf("%d, ", array[curr]);
    }
    printf("\n");
} //寻找数组中的最大值
int findmax(int *array, int size){
    int max = array[0];
    int curr;
    for(curr = 1; curr < size; curr++){
        if(array[curr] > max){
            max = array[curr];
        }
    }
    return max;
} 

 //计数排序
void countSort(int *array, int size){
    int curr = 0;
    int max = findmax(array, size);
    int *count_array = calloc(max, sizeof(int));    //calloc会默认初始化为0

    for(curr = 0; curr < size; curr++){     //初始化计数数组
        count_array[array[curr]] ++;
    }

    int num = 0;
    curr = 0;
    while(curr <= size){
        while(count_array[num] > 0){
            array[curr] = num;
            count_array[num] --;
            curr ++;
            if(curr > size){
                break;
            }//end if
        }//end while
        num ++;
    }
}

//测试主函数 
int main(){
    int test1[] = {2, 6, 4, 3, 2, 3, 4, 6, 3, 4, 3, 5, 2, 6};
    int size1 = 14;
 
    countSort(test1, size1);
    printArray(test1, size1);
 
    int test2[] = {5, 6, 7, 8, 5};
    int size2 = 5;
 
    countSort(test2, size2);
    printArray(test2, size2);
    
    int test3[] = {8, 1, 2, 3, 3, 4};
    int size3 = 6;
 
   countSort(test3, size3);
   printArray(test3, size3);
  return 0;
}