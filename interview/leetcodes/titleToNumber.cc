/**
 * Excel Sheet Column Number
 * Related to question Excel Sheet Column Title
 * Given a column title as appear in an Excel sheet, return its corresponding column number.
 * For example:
 *  A -> 1
 *  B -> 2
 *  C -> 3
 *  ...
 *  Z -> 26
 *  AA -> 27
 *  AB -> 28 
 */
/**
 * 就是把26进制数转换成10进制数，简单的进制转化，而且还告诉了数的长度。
 */
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int titleToNumber(string s) {
		int len = s.size();
		int ret = 0;
		for(int i = 0; i < len; i++){
			ret *= 26;
			ret += s[i] - 'A' + 1;
		}        
		return ret;
    }
};
//test
int main(int argc, char const *argv[])
{
	Solution test;
	string s = "AB";
	cout << test.titleToNumber(s)<<endl;
	return 0;
}