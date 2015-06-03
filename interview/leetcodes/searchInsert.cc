/**
 * Search Insert Position
 * Given a sorted array and a target value, return the index if the target is found.
 *  If not, return the index where it would be if it were inserted in order.
 *  You may assume no duplicates in the array.
 *  Here are few examples.
 *  [1,3,5,6], 5 → 2
 *  [1,3,5,6], 2 → 1
 *  [1,3,5,6], 7 → 4
 *  [1,3,5,6], 0 → 0
 */

#include <iostream>
using namespace std;

class Solution {
public:
    int searchInsert(int A[], int n, int target) {
		int low = 0;
		int high = n-1;
		int mid;
		while(low <= high){
			mid = (low + high) / 2;
			if(A[mid] > target){
				high = mid - 1;
				continue;
			}
			if(A[mid] < target){
				low = mid + 1;
				continue;
			}

			return mid;
		}
		return low;
    }
};
//test
int main(int argc, char const *argv[])
{
	Solution test;
	int A[] = {1, 3, 5, 6};
	int n = sizeof(A) / sizeof(A[0]);
	int ret = test.searchInsert(A, n, 5);
	cout<<ret<<endl;
	ret = test.searchInsert(A, n, 2);
	cout<<ret<<endl;
	ret = test.searchInsert(A, n, 7);
	cout<<ret<<endl;
	ret = test.searchInsert(A, n, 0);
	cout<<ret<<endl;
	return 0;
}