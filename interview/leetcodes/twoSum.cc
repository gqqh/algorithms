/*
 * Two Sum :
 * Given an array of integers, find two numbers such that they add up to a 
 * 		specific target number.
 * 		
 * The function twoSum should return indices of the two numbers such that they 
 * 		add up to the target, where index1 must be less than index2. 
 *   	Please note that your returned answers (both index1 and index2) are 
 *    	not zero-based.
 *     	You may assume that each input would have exactly one solution.
 *
 *	Input: numbers={2, 7, 11, 15}, target=9
 *	Output: index1=1, index2=2
 */
/*
 *算法思想：使用一个结构体记录numbers的值和其对应的index，然后对值进行从小到大排序
 * 		排序后使用两个下标进行遍历，i=0, j=numbers.size()-1;
 * 		if nodes[i].value + nodes[j].value == target:
 * 			ret[0] = min(i, j) + 1
 * 			ret[1] = max(i, j) + 1
 * 		else if nodes[i].value + nodes[j].value > target:
 * 			j--
 * 		else
 * 			i++
 * 		因为告诉你会有两个数之和为target，所以这样就行了。
 * 也可以用std::map<numbers[i], i>的映射来解决，如果
 *  for(int i=0; i<numbers.size(); i++){
 *  	iter = map.find(target - numbers[i])
 *  	if(iter != map.end()):
 *  		找到
 *  	else:
 *  		map[numbers[i]] = i;
 *  }
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
#include <map>

using namespace std;

//蛮力算法O(n^2)
// vector<int> brute_force(vector<int> &numbers, int target){
// 	int len = numbers.size();
// 	vector<int> ret;
// 	for(int i = 0; i < len - 1; i++){
// 		for(int j = i + 1; j < len; j++){
// 			if(numbers[i] + numbers[j] == target){
// 				ret.push_back(i+1);
// 				ret.push_back(j+1);
// 				return ret;
// 			}//if
// 		}//for
// 	}//for
// 	return ret;
// }
//先排序，再用两个指针处理
struct node{
	int value;
	int index; 
};
bool cmp(struct node a, struct node b){
	return a.value < b.value;
}

vector<int> twoSum(vector<int> &numbers, int target){
	int len = numbers.size();

	std::vector<struct node > nums;	
	for(int i = 0; i < len; i++)
		nums.push_back(node{numbers[i], i});
	
	sort(nums.begin(), nums.end(), cmp); 		
	vector<int> ret;
	
	int i = 0, j = len - 1;
	int tmp = nums[0].value + nums[j].value;
	while(tmp != target){
		if(tmp > target)
			j--;
		else
			i++;
		tmp = nums[i].value + nums[j].value;
	}
	if(nums[i].index > nums[j].index){
		ret.push_back(nums[j].index+1);
		ret.push_back(nums[i].index+1);
	}else{
		ret.push_back(nums[i].index+1);
		ret.push_back(nums[j].index+1);
	}

	return ret;
}
vector<int> twoSum_map(vector<int> &numbers, int target){
	map<int, int> numbersMap; 	//值到索引的映射
	map<int, int>::iterator iter;
	vector<int> ret;

	for(int i = 0; i<numbers.size(); i++){
		iter = numbersMap.find(target - numbers[i]); 	//看看另一半是否已经存入，查找也是logN的复杂度，N为当前map的大小
		if (iter != numbersMap.end()){			//找不到时返回最后一个元素的后面一个指针，也就是end();
			if(iter->second > i){
				ret.push_back(i+1);
				ret.push_back(iter->second + 1);
			}else{
				ret.push_back(iter->second + 1);
				ret.push_back(i+1);
			}
		}else{ 	//另一半尚未存入
			numbersMap[numbers[i]] = i;
		}
	}

	return ret;
}

int main(int argc, char const *argv[])
{
	// vector<int> v{572,815,387,418,434,530,376,190,196,74,830,561,973,771,640,37,539,369,327,51,623,575,988,44,659,48,22,776,487,873,486,169,499,82,128,31,386,691,553,848,968,874,692,404,463,285,745,631,304,271,40,921,733,56,883,517,99,580,55,81,232,971,561,683,806,994,823,219,315,564,997,976,158,208,851,206,101,989,542,985,940,116,153,47,806,944,337,903,712,138,236,777,630,912,22,140,525,270,997,763,812,597,806,423,869,926,344,494,858,519,389,627,517,964,74,432,730,843,673,985,819,397,607,34,948,648,43,212,950,235,995,76,439,614,203,313,180,760,210,813,920,229,615,730,359,863,678,43,293,978,305,106,797,769,3,700,945,135,430,965,762,479,152,121,935,809,101,271,428,608,8,983,758,662,755,190,632,792,789,174,869,622,885,626,310,128,233,82,223,339,771,741,227,131,85,51,361,343,641,568,922,145,256,177,329,959,991,293,850,858,76,291,134,254,956,971,718,391,336,899,206,642,254,851,274,239,538,418,21,232,706,275,615,568,714,234,567,994,368,54,744,498,380,594,415,286,260,582,522,795,261,437,292,887,405,293,946,678,686,682,501,238,245,380,218,591,722,519,770,359,340,215,151,368,356,795,91,250,413,970,37,941,356,648,594,513,484,364,484,909,292,501,59,982,686,827,461,60,557,178,952,218,634,785,251,290,156,300,711,322,570,820,191,755,429,950,18,917,905,905,126,790,638,94,857,235,889,611,605,203,859,749,874,530,727,764,197,537,951,919,24,341,334,505,796,619,492,295,380,128,533,600,160,51,249,5,837,905,747,505,82,158,687,507,339,575,206,28,29,91,459,118,284,995,544,3,154,89,840,364,682,700,143,173,216,290,733,525,399,574,693,500,189,590,529,972,378,299,461,866,326,43,711,460,426,947,391,536,26,579,304,852,158,621,683,901,237,22,225,59,52,798,262,754,649,504,861,472,480,570,347,891,956,347,31,784,581,668,127,628,962,698,191,313,714,893};
	std::vector<int> v{0, 76, 25};
	vector<int> r;
	// r = brute_force(v, 9);
	// for(auto i : r)
	// 	cout << i << endl;
	r = twoSum(v, 101);
	for(auto i : r)
		cout << i << endl;
	return 0;
}
