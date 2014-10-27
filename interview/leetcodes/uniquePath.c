/*
 *Unique Paths:
 * A robot is located at the top-left corner of a m x n grid .
 * The robot can only move either down or right at any point in time. 
 * The robot is trying to reach the bottom-right corner of the grid.
 * 
 * How many possible unique paths are there?
 * 
 * Above is a 3 x 7 grid. How many possible unique paths are there?
 * Note: m and n will be at most 100.
 */
/*
 *解题思路：最关键的就是要在求C(N, k)时防止溢出，不能先求出N!,k!,(N-k)!，这样会溢出；
 *          要用C(N, k) = n*(n-1)*...*(n-k+1)/k!；
 *          同时i从k到1计算，而且j从n到(n-k+1)同时计算，且每次都要除以最大公约数
 */

#include <stdio.h>

/*
 *求最大公约数，用互余的方法求gcd
 */
int gcd(int a, int b){
    int t;
    if(a < b){
        t = a;
        a = b;
        b = t;
    }
    //a > b
    while(b != 0){
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

/*
 * min
 */
int min(int a, int b){
    return a > b ? b : a;
}

/*
 *求组合数C（N， k） = n ! / (k! * (n-k)!)
 *                  = n*(n-1)*...*(n-k+1) / k!
 *    注意为了避免溢出，一定要每次同时求k!和n*(n-1)*...*(n-k+1),
 *    而且要，同时i从k到1计算，而且j从n到(n-k+1)同时计算，且每次都要除以最大公约数
 */
int C(int N, int k){
        int tmp1 = 1, tmp2 = 1; //tmp1 = k!, tmp2 = n*(n-1)*...*(n-k+1);
        
        int i = k, j = N;
        //i从k到1，j从N到N-k+1,这个顺序可以最大范围防止溢出
        while(i >= 1 || j >= N - k + 1){
            if(i >= 1)
                tmp1 *= i--;
            if(j >= N - k + 1)
                tmp2 *= j--;
            //每轮都要除以最大公约数
            int g = gcd(tmp2, tmp1);
            tmp2 /= g;
            tmp1 /= g;
        }

        return tmp2;
    }
int uniquePaths(int m, int n) {
        int N = m + n - 2;
        int k = min(m, n) - 1;
        return C(N, k);
}

int main(int argc, char const *argv[])
{
    while(1){
        int n;
        printf("n=");
        scanf("%d", &n);
        int k;
        printf("k=");
        scanf("%d", &k);
        printf("C(%d, %d) = %d\n", n, k, C(n, k));
    }
    return 0;
}