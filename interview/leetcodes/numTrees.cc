/**
 * Unique Binary Search Trees
 * Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
 * For example,
 * Given n = 3, there are a total of 5 unique BST's.
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 */
/**
 * 画几个就可以找到规律，从上面能看到，f(3) = 2*f(1) + f(2)，f(4) = 2f(1) + 2f(2), f(5) = 2f(1)+2f(2)+f(3),...
 * 然后就是动态规划，同时做备忘录的方法了。
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	/**
	 * 类似动态规划，同时做备忘记录，可以把遍历过程减少一半。
	 */
    int numTrees(int n) {
		vector<int> ret(n+1, 0);
		ret[0] = 1;
		ret[1] = 1;
		ret[2] = 2;
		for(int i = 3; i <= n; i++)
			for(int j = 1; j <= i; j++)
				ret[i] += ret[j - 1] * ret[i - j]; 
    
		return ret[n];
    }
    //利用对称性，减少一半的遍历
    int numTrees1(int n) {
		vector<int> ret(n+1, 0);
		ret[0] = 1;
		ret[1] = 1;
		ret[2] = 2;
		for(int i = 3; i <= n; i++){

			int t = i / 2;
			for(int j = 1; j <= t; j++){
				ret[i] += (ret[j - 1] * ret[i - j]) * 2; 
			}
			if(i % 2 )
				ret[i] += ret[t] * ret[t];
		}
    
		return ret[n];
    }
};

//test
int main(int argc, char const *argv[])
{
	Solution test;
	int n = 7;
	int ret = test.numTrees(n);
	cout << ret << endl;
	ret = test.numTrees1(n);
	cout << ret << endl;
	return 0;
}