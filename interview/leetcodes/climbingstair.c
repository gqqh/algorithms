/*
 *Climbing Stairs Total Accepted:
 * You are climbing a stair case. 
 * It takes n steps to reach to the top. 
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 */
/*
 *典型的动态规划计算题：一共n层楼梯，每次可以走一层，可以走两层：
 * 结果为: f(n) = f(n-1) + f(n-2);
 * 			f(1) = 1;
 * 			f(2) = 2;
 * 但是这样会有大量的重复计算，导致复杂度呈指数级。
 * 但是可以使用迭代的方法，使用一个old[2]用来保存临时的值。从小端往大端求解。  
 * 如果题目变形，改为每次可以最多走3步的话，则变为：
 * 		f(n) = f(n-1) + f(n-2) + f(n-2);
 * 		f(1) = 1;
 * 		f(2) = 2;
 * 		f(3) = 4;
 * 	则递归算法为：
 * 	int f(n){
 * 		if(n==1) return 1;
 * 	 	if(n==2) return 2;
 * 	  	if(n==3) return 4;
 * 	   
 * 	   	return f(n-1) + f(n-2) + f(n-3);
 * 	}
 * 	迭代算法为：
 * 	int f(n){
 * 		int old[3] = {4, 1, 2};
 * 		int i = 4;
 * 		while(i <= n){
 * 			int tmp = old[0] + old[1] + old[2];
 * 			old[i % 3] = tmp;
 * 			++i;
 * 		}
 * 		return old[n % 3];
 * 	}
 */
#include <stdio.h>
//递归解法，大量的重复计算
/*
int climbStairs(int n){
	if (n == 1) return 1;
	if (n == 2) return 2;

	return climbStairs(n-1) + climbStairs(n-2);
}*/
//迭代，减少重复计算
int climbStairs(int n){
	int old[2] = {2, 1};
	int i = 3;
	while(i <= n){
		int tmp = old[0] + old[1];
		old[i % 2] = tmp;
		++i;
	}
	return old[n % 2];
}
//test
int main(int argc, char const *argv[])
{
	for(int n = 1; n < 50; n++)
		printf("f(%d) = %d\n", n, climbStairs(n));
	return 0;
}