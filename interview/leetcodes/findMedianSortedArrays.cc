/*
 *Median of Two Sorted Arrays Total Accepted:
 * There are two sorted arrays A and B of size m and n respectively.
 * Find the median of the two sorted arrays. 
 * The overall run time complexity should be O(log (m+n)).
 */
/*
 * 解题思路：如果m+n为奇数，就是找第k=(m+n+1)/2大元素，若为偶数则找第k1=(m+n)/2和第k2=k1+1大的两个元素。
 * 1）典型的merge排序，用两个下标，分别从头开始遍历A，B两个数组，找出中位数，但是这样的复杂度是O（m+n），而题目中要求O(log(m+n)).
 * 2）那就使用剪枝法，充分利用有序，每次减掉肯定不包含第k大的那一列数组。
 */
#include <stdio.h>

/* 解法1
 * 从A[sa, ea]，B[sb, eb]范围内，找第k大的值，其中A、B均为升序的数组。
 * 此方法为O(m+n).
 */

double find_kmax(int A[], int sa, int ea, int B[], int sb, int eb, int k){
	while(sa <= ea && sb <= eb && k > 1){
		if(A[sa] < B[sb])
			++sa;
		else
			++sb;

		--k;
	}

	if(sa > ea){
		return B[sb + k - 1] * 1.0;
	}else if(sb > eb){
		return A[sa + k - 1] * 1.0;
	}else{
		return (A[sa] > B[sb] ? B[sb] : A[sa]) * 1.0;
	}
}
double findMedianSortedArrays(int A[], int m, int B[], int n) {
	int k = (m + n) / 2;
	int i = 0, j = 0;
	//查找第k大的元素
	
	double ret = find_kmax(A, 0, m-1, B, 0, n-1, k+1); 
	if((m+n) % 2 == 1)	//奇数
		return	ret;
	else{
		return (find_kmax(A, 0, m-1, B, 0, n-1, k) + ret) / 2.0;
	}
}

//main test
int main(int argc, char const *argv[])
{
	int A[] = {1, 3, 5, 6, 7, 8};
	int B[] = {2, 4, 6};
	int m = sizeof(A) / sizeof(A[0]);
	int n = sizeof(B) / sizeof(B[0]);
	printf("the median is %f.\n", findMedianSortedArrays(A, m, B, n));
	return 0;
}