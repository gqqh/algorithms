/**
 * Maximum Subarray
 * Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
 * For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
 * 		the contiguous subarray [4,−1,2,1] has the largest sum = 6.
 * More practice:
 * 	If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
 */

#include <iostream>
using namespace std;

class Solution {
public:
    int maxSubArray(int A[], int n) {
		int max = A[0];
		int last = 0;
		for(int i = 0; i < n; i++){
			cout <<"max:"<<max<<" A["<<i<<"]:"<<A[i]<<" last:"<<last<<endl;
			if(last <= 0){
				last = A[i];
			}else{
				last += A[i];
			}
			max = max > last ? max : last;
		}
		return max;        
    }
};
//test
int main(int argc, char const *argv[])
{
	Solution test;
	int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
	int n = sizeof(A) / sizeof(A[0]);
	cout<<test.maxSubArray(A, n)<<endl;
	return 0;
}