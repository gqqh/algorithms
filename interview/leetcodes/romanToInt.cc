/**
 * Roman to Integer
 * Given a roman numeral, convert it to an integer.
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
    int romanToInt(string s) {
		int i = s.size();
		if(i < 0)	return 0;
		int roman[255];
		//用直接映射代替map
		//map<char, int> roman;
		roman['M'] = 1000;
		roman['D'] = 500;
		roman['C'] = 100;
		roman['L'] = 50;
		roman['X'] = 10;
		roman['V'] = 5;
		roman['I'] = 1;

		int ret = roman[s[i-1]];
		while(--i > 0){
			if(roman[s[i]] <= roman[s[i-1]]){
				ret += roman[s[i-1]];
			}else{
				ret -= roman[s[i-1]];
			}
		}
		// if(s.size() >= 2){
		// 	if(roman[s[0]] >= roman[s[1]])
		// 		ret += roman[s[0]];
		// 	else
		// 		ret -= roman[s[0]];
		// }

		return ret;        
    }
};
//test
int main(int argc, char const *argv[])
{
	Solution test;
	string s = "MMMCMXCIX";
	cout <<test.romanToInt(s)<<endl;
	return 0;
}