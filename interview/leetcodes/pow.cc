/**
 * Pow(x, n)
 * Implement pow(x, n).
 */
/**
 * 把n写成二进制，然后如果n = 13，则为1101可以转化为：x^8 * x^4 * x^
 * 	把n依次向右移位，如果末尾为1，则乘以当前的因子（ret = x，每次移位ret *= ret， ret=x, x^2, x^4, x^8,...）
 * 					如果末尾为0不乘。
 */
#include <iostream>
using namespace std;

class Solution {
public:
	// //TLE
 //    double pow(double x, int n) {
 //        double ret = 1.0;
 //        while(n-- > 0)
 //            ret *= x;
        
 //        return ret;
 //    }
 	/**
 	 * 把n写成二进制形式就容易了
 	 */
	double pow(double x, int n){
		double ret = 1.0;
		double temp = x;
		bool flag = true;
		if(n < 0){
			flag = false;
			n = - n;
		}
		while(n > 0){
			if(n & 0x01)
				ret *= temp;
			cout<<"n:"<<n<<"\tret:"<<ret<<"\ttmp:"<<temp<<endl;
			temp *= temp;
			n >>= 1;
		}
		return (flag ? ret : (1.0 / ret));
	}
};
//test
int main(int argc, char const *argv[])
{
	Solution test;
	double x = 2.5;
	int n = -3;
	cout<<x<<" ^ "<<n<<" : "<<test.pow(x, n) <<endl;
	return 0;
}