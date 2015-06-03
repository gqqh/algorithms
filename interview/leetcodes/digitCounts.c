/**
 * Digit count:
 * count the numbers of k's between 0 and n. k can be 0-9.
 * for example, n = 12, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
 * 		then k = 1, return 5. because [1, 10, 11, 12] total 5's 1
 * 1、蛮力方法：从1遍历到n，一次统计每个数中k的个数。
 * 	digitCounts(int k, int n){ 
 * 		int count = 0;
 * 		
 * 		for(int i = 0; i <= n; i++){
 * 			int d = i % 10;
 * 			count += (d == k) ? 1: 0;
 * 			for(int t = i / 10; t > 0; t--){
 * 				int tmp = t % 10;
 * 				count += (d == k) ? 1 : 0;
 * 				t /= 10;
 * 			}
 * 		}
 * 		return count;
 * 	}
 * 
 * 2、思路：这个题目要对n分段讨论。分为t = n / 10, d = n % 10;
 * 		1）如果n < 10，即t = 0； 则如果k > d，则返回0， 否则返回1
 * 		2）如果n >= 10，t >= 1, 在i in [0-9]:每个数在每一轮中出现一次，0 < i < t的i出现10次；
 * 				然后对于每个d，i=t增加d次，[0-d]各增加一次。
 * 	digitCounts(int k, int n){
 * 		int t = n / 10;
 * 		int d = n % 10;
 *
 * 		int ret = 0;
 * 		if()
 * 		
 * 	
 * 	}
 */
#include <stdio.h>

/**
 * 蛮力，计算每个数字中k出现的次数，累计。
 * @param  k （0-9）
 * @param  n 统计[0, n]中出现数字k
 * @return   统计[0-n]中所有数中数字k出现的次数
 */
int count_n(int n, int k){
	int count = 0;
	int d = n % 10;
	if(d == k){
		count ++;
	}
	int t = n / 10;
	while(t > 0){
		d = t % 10;
		if(d == k){
			count++;
		}
		t /= 10;
	}
	return count;
}
int digitCounts1(int k, int n){ 
	int count = 0, i, t;
	for(i = 0; i <= n; i++){
		int t = count_n(i, k);
		count += t;
		printf("now i=%d , t = %d, count = %d\n", i, t, count);
	}
	return count;
}
int digitCounts2(int k, int n) {
	
}

//test
int main(int argc, char const *argv[])
{
	int n = 212, k = 0;
	printf("n = %d, there are %ds %d\n", n, digitCounts1(k, n), k);	
	return 0;
}
