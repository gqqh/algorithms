/**
 * Best Time to Buy and Sell Stock
 * Say you have an array for which the ith element is the price of a given stock on day i.
 * If you were only permitted to complete at most one transaction 
 * 		(ie, buy one and sell one share of the stock), design an algorithm to
 * 		 find the maximum profit.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	/**
	 * f(n) = f(n-1) + A[n]-A[n-1];
	 * f(n) <= 0 ? 0 : f(n);
	 * f(1) = 0;
	 * max = f(n) > max ? f(n) : max;
	 */
    int maxProfit(vector<int> &prices) {
 		int max = 0, fn = 0;
 		int n = prices.size();
 		
 		for(int i = 1; i < n; i++){
			fn += prices[i] - prices[i-1];
			if(prices[i] < prices[i-1])
				fn = fn > 0 ? fn : 0;
 			max = max > fn ? max : fn;
 		}

 		return max;
    }
};
//test
int main(int argc, char const *argv[])
{
	Solution test;
	vector<int> prices {-10, 1, 3, 2, 4, 11, 7, 9, 3, 5, 10};
	vector<int> prices1 {};
	int ret = test.maxProfit(prices);
	cout << ret << endl;
	return 0;
}