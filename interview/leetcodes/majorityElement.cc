/**
 * Majority Element:
 * Given an array of size n, find the majority element. 
 * The majority element is the element that appears more than ⌊ n/2 ⌋ times.
 * You may assume that the array is non-empty and the majority element always 
 * 		exist in the array.
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int> &num) {
        int count = 0;
        int ret = num[0];
        int n = num.size();
        int i;
        for(i = 1; i < n; i+= 2){
        	if(num[i] != num[i-1])
        		continue;
        	if(num[i] == ret){
        		count += 2;
        	}else{
        		if(count > 2){
        			count -= 2;
        		}else{
        			count = 2;
        			ret = num[i];
        		}
        	}
        }
        if(i == n && count == 0)
        	return num[n-1];
        return ret;
    }
};

//test
int main(int argc, char const *argv[])
{
	Solution test;
	vector<int> t{1, 2, 0, 3, 2, 4, 2, 2, 5, 2, 6, 2, 2};
	std::vector<int> v{6, 5, 5};
	int r = test.majorityElement(t);
	cout <<r<<endl;
	r = test.majorityElement(v);
	cout <<r<<endl;
	
	return 0;
}