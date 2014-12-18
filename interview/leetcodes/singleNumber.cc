/**
 * Single Number:
 * Given an array of integers, every element appears twice except for one. Find that single one.
 * Note:
 * 		Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
 */
/**
 * 1、使用集合，利用集合的互异性，每次插入失败则表示已存在（插入的返回值是一个std::pair(<iterator>, bool)），则删除，否则表示不存在，插入成功。
 * 		最终返回返回第一个元素的值:*set.first()
 * 2、或者利用异或的特性，从第一个元素到最后一个元素，一次进行异或，最终的结果即为single number。
 * 		1, 2, 3, 2, 1
 * 		0001
 * 	  ^	0010
 * 	  ^	0011
 * 	  ^	0010
 * 	  ^	0001
 * 	---------
 * 		0011	
 */
#include <iostream>
#include <set>

class Solution {
public:
	/**
	 * 使用集合记录出现的过的值，重复则删除，否则加入，最终返回唯一的元素
	 */
	int singleNumber1(int A[], int n) {
		std::set<int> a_set;
		for(int i = 0; i < n; i++){
			if(!(a_set.insert(A[i])).second)
				a_set.erase(A[i]);
		}
		return *a_set.begin();
    }
    /**
     * 把所有的数的异或操作，返回最终值，以为两个相等的值的异或为0
     */
    int singleNumber(int A[], int n){
    	int ret = A[0];
    	for(int i = 1; i < n; i++)
    		ret ^= A[i];
    	
    	return ret;
    }

};

int main(int argc, char const *argv[])
{
	Solution test;
	int A[] = {3, 1, 3 ,2, 2};
	int n = sizeof(A) / sizeof(A[0]);
	std::cout <<test.singleNumber(A, n) << std::endl;
	return 0;
}