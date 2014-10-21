/*
 *Find Minimum in Rotated Sorted Array II 
 * Follow up for "Find Minimum in Rotated Sorted Array":
 * What if duplicates are allowed?
 *
 *Would this affect the run-time complexity? How and why?
 *Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 *
 *(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 *Find the minimum element.
 *The array may contain duplicates.
 */
/*
 *解题思路：此题最好先去除后面可能与第一个数相等的值，然后就转化为可以使用之前那个思路的问题了
 *复杂度也还是O(n)了，与蛮力方法一样了。
 */

#include <iostream>
#include <vector>

using namespace std;
/*
 *蛮力解法，从第二个数开始遍历，遇到一个比前面数字小的数就直接返回。
 *复杂度=O(n)
 */
int findMin1(vector<int> &num){
	int len = num.size();

	for(int i = 1; i < len; i++){
		if(num[i] < num[i-1])
			return num[i];
	}
	
	return num[0];
}

/*
 *分析：此题与之前的没有重复值的那题的区别就在于此题后面可能会有一些值与第一个值相等
 *	所以可以先去掉后面与第一个相等的值，然后再使用类似二分查找的方法找到最小值。
 *只要num[start] > num[end]，那么最小值就在[start, end]区间内
 */

int findMin(vector<int> &num){
	int end = num.size() - 1;
	while(end >= 0 && num[end] == num[0])
		--end;
	if(end == -1)
		return num[0];

	int start = 0;
   	while(num[start] > num[end]){
	    int mid = (start + end) / 2;
	    if(num[mid] >= num[start]){
		    start = mid + 1;
	    }else{
		    end = mid;
	    }
	}

	return num[start];
}

int main(int argc, char const *argv[])
{
	int num[] = { 4, 1, 4, 4, 4}; //, 5, 5, 6, 6,  6, 7,  7, 7, 7, 0, 0, 0, 1, 1, 1, 3, 4, 4, 4};
	vector<int> v(num, num+sizeof(num)/sizeof(num[0]));
	cout <<findMin(v)<<endl;
	return 0;
}