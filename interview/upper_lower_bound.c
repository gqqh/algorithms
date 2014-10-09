/*
 *主要实现二分查找，及<algorithm>中的upper_bound(),和lower_bound()两个函数
 *都是利用二分查找的思想，具体的边界值不一样
 */

#include <stdio.h>
 #include <stdlib.h>

/* 二分查找 
 * 参数：X输入已排序的数组，n为X数组大小， value为要查找的值
 * 返回：value所在指针，不存在时返回NULL
 */

int* binary_search(int X[], int n, int value){
    int low = 0;
    int high = n - 1;
    int mid = (low + high) / 2;

    while (low <= high){
        if (value == X[mid])
            return X + mid ;
        else if (value > X[mid]){
            low = mid + 1;
            mid = (low + high) / 2;
        } else {
            high = mid - 1;
            mid = (low + high) / 2;
        }
    }//end while

    return  NULL;
}

/* upper_bound(X.begin, X.end, value) [X,begin, X.end)
  * 参数：X.begin为数组X的开始，X.end为数组结尾（不含）， value为要找的值
  * 返回：大于value的第一个值的指针，或者X.end当找不到时。
  */
int *upper_bound(int *begin, int *end, int value){
    int low = 0;
    int high = end - begin - 1;
    int mid = (low + high) / 2;

    while(low <= high){
        if (value >= begin[mid]){   //因为要找比它大的最小值，所以等于时也要向上找
            low = mid + 1;
            mid = (low + high) / 2;
        }else{
            high = mid - 1;
            mid = (low + high) / 2;
        }
    }//end while

    return begin + mid + 1; //找到的值是大于等于value的最小值的前一个元素
 }

/* lower_bound(X.begin, X.end, value) [X,begin, X.end)
  * 参数：X.begin为数组X的开始，X.end为数组结尾（不含）， value为要找的值
  * 返回：小于value的第一个值的指针，或者X.begin当找不到时。
  */
int *lower_bound(int *begin, int *end, int value){
    int low = 0;
    int high = end - begin - 1;
    int mid = (low + high) / 2;

    while(low <= high){
        if (value <= begin[mid]){   //因为是找比它小的最大值，所以等于也要向下找
            high  = mid - 1;
            mid = (low + high) / 2;
        }else{
            low = mid + 1;
            mid = (low + high) / 2;
        }
    }//end while
    return begin + mid;     //找到的值是小于value的最大值
 }

// 测试以上三个函数
int main(int argc, char const *argv[])
 {
     int X[] = {0, 0, 1, 1, 2, 2, 2, 3, 4, 4, 5};
     int n = sizeof(X) / sizeof(X[0]) ;
     
     int value = 5;
     int *mid = binary_search(X, n, value);
     int *low = lower_bound(X, &X[0]+n, value);
     int *upper = upper_bound(X, &X[0]+n, value);

     printf("low = %ld, mid = %ld, upper = %ld\n", low-X, mid -X, upper - X);
    if (mid != NULL)
        printf("bsearch: %d = %d\n",  value, *mid);
    else
        printf("bsearch:%d not found!\n", value);
     low ++;
     while(low < upper){
        printf("%d \n", *low);
        low++;
     }

     return 0;
 }