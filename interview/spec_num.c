/*
 * 寻找特殊数字
 * 问题
 * 给定一个升序的数组A，让你在数组中找到任意下标x，使得A[x] == x。（数组下标从0开始）
 * 例如：
 * [-1, 1, 2, 3, 10]中，x = 3即为所求。
 * 算法思想：使用二分查找、分治的思想
  * low, hight ,mid = (low + high) / 2
 *  while(low <= high):
 *      if A[mid] == mid:
 *          count++;
 *          count += fun(A, low, mid-1) + fun(mid+1, high)
 *      else if A[mid] > mid:
 *          high = mid - 1;
 *          mid = (low + high) / 2
 *      else:
 *          low = mid + 1;
 *          mid = (low + high) / 2;
 *  return count;
 *  复杂度：O(logn)
 */

#include <stdio.h>

/*寻找特殊数字：A[0...n-1]中A[x] == x的值。
 * 参数：升序数组A[0...n-1]， n为A的大小
 * 返回值：满足x的个数
 */
int spec_num(int A[], int low, int high){
    int count = 0;
    int mid;

    while(low <= high){
        mid = (low + high) >> 1;
        if (A[mid] == mid){
            printf("A[%d] = %d\n", mid, mid);
            count ++;
            count += spec_num(A, low, mid-1) + spec_num(A, mid +1, high);
            break;
        }else if (A[mid] > mid){
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }

    return count ;
}

/*
 * 如果确定最多只有一个元素的话，就可以直接用二分查找了
 * 如果找到则输出
 */
int one_num(int A[], int n){
    int low = 0;
    int high = n-1;
    int mid;
    int flag = 0;

    while(low <= high){
        mid = (low + high) >> 1;
        if (A[mid] == mid) {
            flag = 1;
            break;
        }else if(A[mid] > mid){
            high = mid -1;
        }else{
            low = mid + 1;
        }
    }
    if(flag){
        printf("A[%d] = %d\n", mid, mid);
    }else{
        printf("not found...\n");
    }
    return flag;
}
/*
 * 蛮力算法，从头到尾遍历
 * 复杂度：O(n)
 */
int brute_force(int A[], int n){
    int i = 0;
    int count = 0;
    for (i = 0; i < n; i++){
        if (A[i] == i){
            count ++;
            printf("A[%d] == %d\n", i, i);
        }
    }
    return count;
}


//测试spec_num函数
int main(int argc, char const *argv[])
{
    int A[] = {-1, 1, 2, 3, 5, 8, 10};
    int n = sizeof(A) / sizeof(A[0]);

    int t = spec_num(A, 0, n-1);
    printf("spec_num:%d\n", t);
    
    t = brute_force(A, n);
    printf("brute_force:%d\n", t);

    printf("one_num:");
    t = one_num(A, n);

    return 0;
}