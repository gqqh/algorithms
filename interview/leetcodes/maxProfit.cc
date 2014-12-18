/**
 * Best Time to Buy and Sell Stock II:
 * Say you have an array for which the i-th element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. 
 * You may complete as many transactions as you like (ie, buy one and sell one
 * 		share of the stock multiple times). However, you may not engage in 
 * 		multiple transactions at the same time (ie, you must sell the stock 
 * 		before you buy again).
 */
/**
 * 这个题目就是找数组中处于上升的数据段，使用两个指针，分别锁定一个增长段的首尾两个元素，其差值
 * 就是这段的profit，然后继续找下一段。要注意找边界的问题。
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	/**
	 * 使用两个下标遍历，每次如果下一时刻比此刻更贵，就等待，否则就卖出。同时把起点设为下一个时刻
	 * 结束时直接将最后一个元素减去此时的起点值。
	 */
    int maxProfit(vector<int> &prices) {
    	int profit = 0, i, j;
    	int size = prices.size() - 1;
    	if(size < 1)	return profit;
        for(i = 0, j = 0; i < prices.size(); i++){
        	if(prices[i] <= prices[i+1])
        		continue;
        	else{
        		profit += prices[i] - prices[j];
        		j = i + 1;
        	}
        }
        profit += prices[i] - prices[j];
        return profit;
    }
};
//test
int main(int argc, char const *argv[])
{
	Solution test;
	vector<int> prices {-10, 1, 3, 2, 4, 9, 7, 9, 3, 5, 10};
	vector<int> prices1 {};
	int ret = test.maxProfit(prices1);
	cout << ret << endl;
	return 0;
}