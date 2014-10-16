/*
 *Find Minimum in Rotated Sorted Array 
 *
 *Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 *(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 *Find the minimum element.
 *You may assume no duplicate exists in the array.
 */
/*
 *算法思想：由于数组是由一个升序序列旋转而成的，所以是属于分段有序的：
 *num = {a1, a2, a3, ..., an}
 *则有1<= i <= n, ai+1 <= ai+2 <= ... <= an >= a0 <= a1 <= ... <=ai <= ai+1
 *可以使用二分法：
 *当num[start] <= num[end]满足时，必有最小值在[start, num]中
 *	if start==end:	
 *		return num[start]
 *	mid = (start + end) >> 1;
 *	if num[mid] >= num[start]:
 *		start = mid + 1
 *	else:
 *		end = mid
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 *蛮力解法
 */
int brute_force(vector<int> &num){
	int len = num.size();
	for(int i=0; i<len-1; i++){
		if(num[i] > num[i+1])
			return num[i+1];
	}
	return num[0];
}

/*
 *递归解法
 */
int find(vector<int> &num, int start, int end){
	if(start == end){
		return num[start];
	}
	if(num[start] < num[end])
		return num[start];
	int mid = (start+end)/2;
	if(num[start] <= num[mid]){
		return find(num, mid+1, end);
	}else{
		return find(num, start, mid);
	}
}
int findMin1(vector<int> &num){
	find(num, 0, num.size()-1);
}
/*
 *迭代解法
 */
int findMin(vector<int> &num) {
	int start = 0;
	int end = num.size()-1;
	int mid;
	while(num[start] >= num[end]){
		if(start == end){
			return num[start];
		}
		mid = (start + end) >> 1;
		if(num[start] <= num[mid])
			start = mid + 1;
		else
			end = mid;
	}
	return num[start];
}

int main(int argc, char const *argv[])
{
	int num[] = {3,  3};
	vector<int> v(num, num+sizeof(num)/sizeof(num[0]));
	cout <<findMin(v)<<endl;
	cout <<findMin1(v)<<endl;
	cout <<brute_force(v)<<endl;
	return 0;
}
