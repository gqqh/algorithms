/*
 *Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
 *Find all unique triplets in the array which gives the sum of zero.
 *
 *Note:
 * Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
 * The solution set must not contain duplicate triplets.
 *   For example, given array S = {-1 0 1 2 -1 -4},
 *
 *   A solution set is:
 *   (-1, 0, 1)
 *   (-1, -1, 2)
 */
/*
 *解题思想：首先三个数求和结果为0，由于没有让返回三个数的下标，所以问题要比twosum简单点，主要要小心结果可能有重复的问题，所以排序很有必要。
 *1）首先对向量排序，使用三个下标作为标记，i用来做主循环，j和k分别从j=i+1和k=len-1开始从两端往中间遍历，即：while(j<k)循环
 *		如果num[j] + num[k] == -num[i]，则将放入结果集，j++，k--；
 *	 	如果num[j] + num[k] > -num[i]，则需要减小num[j] + num[k]，j++则和增加，k--则和减小，所以，j不变，k--；
 *	  	如果num[j] + num[k] < -num[i]，则需要增大num[j] + num[k]，所以，k不变，j++；
 *2）使用了两个小技巧：
 *		因为显然num[i],num[j],num[k]的大小顺序是：num[i] <= num[j] <= num[k]，所以很明显，如果如果num[i] > 0或者num[k] < 0就不可能有和为0；
 *		为了避免出现重复结果，所以对排序后的数组遍历时，需要谈论当前值与前一个值是否相同，如果相同且前一个值不是第一次访问，则继续往下一个遍历。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<vector<int> > threeSum(vector<int> &num) {
	int len = num.size();
	vector<vector<int> > ret;
	sort(num.begin(), num.end());

	for(int i = 0; i < len - 2; i++){
		if(num[i] > 0)
			return ret;
		else if(i > 0 && num[i] == num[i-1])
			continue;
		for(int j = i + 1; j < len -1; j++){
			if(j > i+1 && num[j] == num[j-1])
				continue;
			for(int k = j+1; k < len; k++){
				// cout<<"i:"<< i <<", j:" << j << ", k:" << k<<endl; 
				if(num[k] < 0)
					continue;
				else if(k > j+1 && num[k] == num[k-1])
					continue;
				else if(num[i] + num[j] + num[k] == 0){
					vector<int> tmp{num[i], num[j], num[k]};
					ret.push_back(tmp);
				}//end if
			}//end for
		}//end for
	}//end
	return ret;
}

vector<vector<int> > threeSum(vector<int> &num) {
	int len = num.size();
	vector<vector<int> > ret;
	sort(num.begin(), num.end());

	for(int i = 0; i < len - 2 && num[i] <= 0; i++){
		if(i != 0 && num[i] == num[i-1])
			continue;
		int j = i + 1;
		int k = len - 1;
		while(j < k && num[k] >= 0){
			if(j != i+1 && num[j] == num[j-1]){
				j++;
				continue;
			}else if(k != len - 1 && num[k] == num[k+1]){
				k--;
				continue;
			}
			if(num[j] + num[k] == -num[i]){
				vector<int> tmp{num[i], num[j], num[k]};
				ret.push_back(tmp);
				j++;
				k--;
			}else if(num[j] + num[k] > -num[i])
				k--;
			else
				j++;
		}//end while
	}//end for
	
	return ret;
}
int main(int argc, char const *argv[])
{
	// std::vector<int> v{-1, 0, 1, 2, -1, -4};
	vector<int> v{-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
	vector<vector<int> > t = threeSum(v);
	int n = t.size();
	for(int i = 0; i < n; i++){
		cout <<"(";
		for(auto c : t[i])
			cout<<c<<" ";
		cout<<")\n";
	}
	return 0;
}