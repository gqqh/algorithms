/**
 * Single Number II
 * Given an array of integers, every element appears three times except for one. Find that single one.
 * Note:
 * 	Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
 */
#include <iostream>
#include <stdio.h>
using namespace std;

class Solution {
public:
    int singleNumber(int A[], int n) {
        int total[32];
        for(int i = 0; i < 32; i++)
        	total[i] = 0;
        for(int i = 0; i < n; i++){
        	cout<<"A["<<i<<"]: "<<A[i]<<" = ";
        	for(int j = 0; j < 32; j++){
        		int mask = 0x01 << j;
        		cout<<"mask: "<<mask<<endl;
        		if(A[i] & mask != 0){
        			total[j] += 1;
        			printf("0x%x ", A[i]&mask);
        		}
        		cout<<total[j]<<" ";
        	}
        	cout<<endl;
        }
        int ret = 0;
        cout<<"total: ";
        for(int i = 0; i < 32; i++){
        	cout<<total[i]<<" ";
			if(total[i] % 3 != 0){
				ret += 1 << i;
			}
        }
        cout<<endl;
        return ret;
    }
};
//test 
int main(int argc, char const *argv[])
{
	Solution test;
	int A[] = {0, 0, 0, 7};
	int n = sizeof(A) / sizeof(A[0]);
	cout<<test.singleNumber(A, n) << endl;
	return 0;
}