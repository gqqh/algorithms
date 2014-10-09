#include <iostream>
#include <algorithm>
using namespace std;

/* 算法思想：
 * x^y > y ^x，其中x，y都是非负整数；
 * x^y,y^x都是 >= 0；当x >=3, y >= 3时，x^y > y^x <==> yln(x) > xln(y)
 * <==>ln(x)/x > ln(y)/y
 * <==>f(x) = ln(x)/x, (x >=3)
 * <==>f'(x) = (1-ln(x))/x^2, x>=3 ==> f'(x) < 0
 * <==>f(x)单调递减
 * <==>当y>x时，有f(x) > f(y)即：x^y > y^x
 * 所以算法的目标就是找到x >= 3, y >=3时y比x大的个数，
 * 以及在x=0,1,2和y=0,1,2的情况
 * 其中：
 * x=0时，0^y = 0 > y^0=1不可能，所以此时满足的(x, y)个数为0
 * x=1时，1^y = 1 > y^1 = y，y只能为0,所以此时满足的(x, y)个数为y为0的个数
 * x=2时，2^y > y^2,y为0,1,5,6.....即除了2,3,4之外的所有y均符合，即：{0,1}+{y|x < y} - {3,4}
 * x=3时，3^y > y^3,y为0,1,2,4,5,6……，即除了3之外的所有y都符合，即：{0,1}+{y|x<y}+{2}
 * x=4时，4^y > y^4,y为0,1,5,6，……即：{0，1} + {y|x < y}
 *
 * 1）先对y进行排序，然后统计其中y=0，1，2，3，4，5的个数。
 * 2）遍历x数组，对于其中每个x分别讨论：
 *     a）如果x=0；return 0；
 *     b）如果x=1；return y[0]；
 *     c）ret = len({y | y > x}) + y[0] + y[1]
 *     d）如果x = 2; return ret - y[3] - y[4];
 *     e）如果x = 3；return ret + y[2];
 *     f）否则，return ret;
 * 3）返回个数即可。
 */

/*功能：统计每一个x在Y数组中存在数对的个数；
 * 参数：x为当前统计的数，Y[]为Y数组，n为Y数组的元素个数，
 *             no_y 为Y[0...4]出现的次数，数组长度为5.
 * 返回：x的数对个数
 */
int countx(int x, int Y[], int n, int no_y[]){
    // a）如果x=0；return 0；
    if (x == 0)  
        return 0;
    // b）如果x=1；return y[0]；
    if (x == 1) 
        return no_y[0];
    // c）ret = len({y | y > x}) + y[0] + y[1]
    // upper_bound函数可以求出，在[Y, Y+n)这个区间内第一个大于x的指针
    int *idx = upper_bound(Y, Y+n, x);  
    int ret = (Y + n) - idx;

    // d）如果x = 2; return ret - y[3] - y[4];
    if (x == 2)
        return ret - no_y[3] - no_y[4];
    // e）如果x = 3；return ret + y[2];
    if (x == 3)
        return ret + no_y[2];

    return ret;
}

/*功能：统计数对个数：
 * 参数：X[]，Y[]为输入的数组，m,n分别为X，Y的元素个数
 * 返回：数对的个数
 */
int countPairs(int X[], int Y[], int m, int n){
    //对Y进行排序
    sort(Y, Y+n);

    //统计Y[0...4]
    int no_y[5] = {0};
    for(int i = 0; Y[i] < 5; i++){
        no_y[Y[i]] ++;
    }

    int total_pairs = 0;
    for(int i = 0; i < m; i++){
        total_pairs += countx(X[i], Y, n, no_y);
    }

    return total_pairs;
}

// test countPairs
int main(int argc, char const *argv[])
{
    int X[] = {2, 1, 19, 20, 3, 4, 100, 50, 39, 23, 54};
    int Y[] = {4, 2, 8, 3, 18, 40, 288, 42, 12, 45};
    
    int n = sizeof( Y ) / sizeof( Y[0] );
    int m = sizeof( X ) / sizeof( X[0] );

    cout << "Total pairs = " << countPairs(X, Y, m, n) << endl;
    return 0;
}