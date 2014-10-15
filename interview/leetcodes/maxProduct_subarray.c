/*
 *Find the contiguous subarray within an array (containing at least one number) 
 *   which has the largest product.
 *   For example, given the array [2,3,-2,4],the contiguous subarray [2,3] has 
 *   the largest product = 6.
 */
/*
 *解题思想：
 *首先考虑到乘积遇到0，就会变成0，所以首先应当用0把整个数组分成若干不含0的几段，然后分而治之
 *zero_p = find_first_zero(A, start, end);
 *if zero_p > -1:   //有0
 *  return max(mproduct(A, start, zero_p-1), 0, mproduct(A, zero_p+1, end))
 *else:     //没有0
 *  在没有0的情况下，就意味着这一段只有正数和负数，且当负数的个数为偶数时，乘积仍为正数，且比原来的大，
 *  所以，分两种情况：   1）负数的个数为偶，则所有数直接相乘，即为此段最大乘积；
 *                      2）负数个数为奇数，则要以第一个奇数和最后一个奇数为分段点。
 *  neg_num = find_negative(A, start, end);
 *  if neg_num == 0 || neg_num % 2 == 0:
 *      return product(A, start, end);
 *  else:
 *      neg_p1 = find_first_neg(A, start, end);
 *      neg_p2 = find_last_neg(A, start, end);
 *      return max(mproduct(A, start, neg_n2 - 1), mproduct(A, neg_n1+1, end));
 *  
 */
#include <stdio.h>

/*
 * 找到[start, end]第一个0的位置，没找到则返回-1
 */
int find_first_zero(int A[], int start, int end){
        while(start <= end){
            if(A[start] == 0)
                return start;
            ++start;
        }
            
        return -1;  //all zero
}

/*
 *统计[start, end]中负数的个数，没有则返回0
 */
int total_negative(int A[], int start, int end){
    int ret = 0;
    while(start <= end){
        if(A[start] < 0)
            ++ret;
        ++start;
    }

    return ret;
}

/*
 *返回[start, end]中的第一个负数的起始位置，不存在则返回-1
 */
int find_first_neg(int A[], int start, int end){
    while(start <= end){
        if (A[start] < 0)
            return start;
        ++start;
    }
 
    return -1;
}

/*
 *返回[start, end]中的最后一个负数的位置，不存在则返回-1
 */
int find_last_neg(int A[], int start, int end){
    while(end >= start){
        if (A[end] < 0)
            return end;
        --end;
    }
 
    return -1;
}

/*
 *返回[start, end]之间的乘积
 */
int product(int A[], int start, int end){
    if(start > end)
        return -0x7fffffff;
    else if (start == end)
        return start;

    int ret = 1;
    while(start <= end){
        ret *= A[start];
        ++start;
    }

    return ret;
}

/*
 *计算[start, end]之间的最大乘积
 */
int mProduct(int A[], int start, int end) {
    if (start > end)    
        return -0x7fffffff;
    else if (start == end) 
        return A[start];
    
    //找到接下来的第一个0
    int i = find_first_zero(A, start, end);
    if (i != -1){   //找到一个0，分成两段，0也要参与比较
        int tmp1 = mProduct(A, start, i-1);
        int tmp2 = mProduct(A, i+1, end);
        int tmp3 = tmp1 > tmp2 ? tmp1 : tmp2;

        return tmp3 > 0 ? tmp3 : 0;
    }else{  //没有0
        int neg_num = total_negative(A, start, end);
        if(neg_num == 0 || neg_num % 2 == 0)    //没有负数，或者负数为偶数个
            return product(A, start, end);
        else{
            int first_neg = find_first_neg(A, start, end);
            int last_neg = find_last_neg(A, start, end);
            int tmp1 = mProduct(A, start, last_neg - 1);
            int tmp2 = mProduct(A, first_neg + 1, end);
            return (tmp1 > tmp2 ? tmp1 : tmp2);
        } 
    }
}

int maxProduct(int A[], int n){
    return mProduct(A, 0, n-1);
}
int main(int argc, char const *argv[])
{
    int A[] = {0, 0, 10, 0, 0};
    int n = sizeof(A) / sizeof(A[0]);
    printf("%d\n", maxProduct(A, n));

    return 0;
}