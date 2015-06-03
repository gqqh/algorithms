/** 
 * Integer to Roman:
 * Given an integer, convert it to a roman numeral.
 * 
 * Input is guaranteed to be within the range from 1 to 3999.
 * 个位数举例
 * 		I, 1， II, 2， III, 3 IV, 4 ，V, 5 ，VI, 6， VII, 7， VIII,8 ，IX, 9 
 * 十位数举例
 * 		X, 10， XI, 11 ，XII, 12， XIII, 13， XIV, 14， XV, 15，
 * 		XVI, 16 ，XVII, 17 ，XVIII, 18， XIX, 19， XX, 20，  XXI, 21，
 * 		XXII, 22 ，XXIX, 29， XXX, 30， XXXIV, 34， XXXV, 35 ，XXXIX, 39，
 * 		XL, 40， L, 50 ，LI, 51， LV, 55， LX, 60， LXV, 65， LXXX, 80，
 * 		XC, 90 ，XCIII, 93， XCV, 95 ，XCVIII, 98， XCIX, 99 ，
 * 百位数举例
 * 		C, 100， CC, 200 ，CCC, 300 ，CD, 400， D, 500 ，DC,600 ，DCC, 700，
 * 		DCCC, 800 ，CM, 900， CMXCIX,999， 
 * 千位数举例 
 * 		M, 1000， MC, 1100 ，MCD, 1400 ，MD, 1500 ，MDC, 1600 ，MDCLXVI, 1666，
 * 		MDCCCLXXXVIII, 1888 ，MDCCCXCIX, 1899 ，MCM, 1900 ，MCMLXXVI, 1976， 
 * 		MCMLXXXIV, 1984， MCMXC, 1990 ，MM, 2000 ，MMMCMXCIX, 3999，
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
    string intToRoman(int num){
    	string ret;
		if(num <= 0)	return ret;
		map<int, string> roman;
		roman[1000] = "M";
		roman[500] = "D";
		roman[100] = "C";
		roman[50] = "L";
		roman[10] = "X";
		roman[5] = "V";
		roman[1] = "I";
		int i = 1;
		while(num > 0){
			int d = num % 10;
			if(d == 9){
				ret = roman[i]+roman[i*10] + ret;
			}else if(d > 5){
				string tmp;
				tmp = roman[i*5];
				for(int j = 5; j < d; j++)
					tmp = tmp + roman[i];
				ret = tmp + ret;
			}else if(d == 5){
				ret = roman[i*5] + ret;
			}else if(d == 4){
				ret = roman[i] + roman[i*5] + ret;
			}else if(d > 0){
				string tmp;
				for(int j = 0; j < d; j++)
					tmp =  tmp + roman[i];
				ret = tmp + ret;
			}
			cout <<"num:"<<num<<" d:"<< d<<" ret:"<<ret<<endl; 

			num /= 10;
			i *= 10;
		}

		return ret;        
    }
};
//test
int main(int argc, char const *argv[])
{
	Solution test;
	int n = 3567;
	cout <<test.intToRoman(n)<<endl;
	return 0;
}