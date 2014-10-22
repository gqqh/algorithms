/*
 * 最少插入字符
 * :给定字符串，可以通过插入字符，使其变为回文。求最少插入字符的数量。
 * 例如：
 * ab最少插入1个字符，变为bab，或者aba
 * aa最少插入0个字符
 * abcd最少插入3个字符，*dcb*abcd
 */
/*
 * 分析：可采用动态规划来求解，假设：a1a2...an
 * 问题分解为：
 * 		如果a1==an，那么要插入的字符个数就等于子问题a2a3...an-1的解的个数。
 * 		如果a1!=an，那么要插入的字符个数就等于子问题a1a2...an-1和子问题a2a3...an的最小值加1
 * 所以可以可以用动态规划求解。 
 */
/*
 *动态规划求解问题：首先要看是不是可以把原问题划分成若干，而且子问题之间有重叠，无重叠的可以用分治法求解。
 *	再根据子问题可以写出原问题的解的方程式。然后找到子问题的边界，什么时候可以直接返回，而不用继续划分子问题。
 *	有时候有必要在求解过程中，做备忘录，这样求子问题时如果有重复解，就可以直接返回了。
 */

/*
 * 返回str[start, end]之间需要插入的最小值使得其称为一个回文。
 */
#include <stdio.h>

/*
 *用于求解子问题的递归函数
 */
int min_insert(char *str, int start, int end){
	if(start == end){
		return 0;
	}else if(end - start == 1){
		if(str[start] == str[end])
			return 0;
		else
			return 1;
	}

	if(str[start] == str[end]){
		return min_insert(str, start+1, end-1);
	}else{
		int a = min_insert(str, start+1, end);
		int b = min_insert(str, start, end-1);
		return (a > b ? b : a) + 1;
	}
}

/*
 *求解str的最小插入字符数才能构成回文。
 */
int min_huiwen(char *str, int n){
	if(n <= 0){
		return -1;
	}
	return min_insert(str, 0, n-1); 
}

//测试main
int main(int argc, char const *argv[])
{
	char str[] = "malloc";
	 //注意sizeof是一个运算符，它返回的是括号里面所占的内存大小，单位为字节，所以连字符串末尾的结束符也统计在内了。
	int n = sizeof(str) / sizeof(str[0]) - 1;
	printf("%d\n", min_huiwen(str, n));
	return 0;
}