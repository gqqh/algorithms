/** 
 * N-Queens II
 * Follow up for N-Queens problem.
 * Now, instead of outputting board configurations, return the total number of distinct solutions.
 */
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
    	int ret = 0;
    	
    	// int *column = (int *)malloc(sizeof(int) * n); //定义解空间
    	// int *diagonal_45 = (int *)malloc(sizeof(int) * 2 * n - 1);
    	// int *diagonal_135 = (int *)malloc(sizeof(int) * 2 * n - 1);
    	int *layout = (int *)malloc(sizeof(int) * n); //布局
     //    //清空标志
    	// memset(column, 0, sizeof(int)*n);
    	// memset(diagonal_45, 0, sizeof(int)*n*2-1);
    	// memset(diagonal_135, 0, sizeof(int)*n*2-1);

    	//初始化解空间，解空间结构为一个满二叉树
    	for(int i=0; i < n; i++)
    		layout[i] = -1;
        //先放置第一列
    	backtrack(0, &ret, n, layout);
	   	// free(column);
	   	// free(diagonal_45);
	   	// free(diagonal_135);
	   	free(layout);
	   	return ret;
	}
private:
	void backtrack(int k, int *ret, int n, int *layout){ //回溯遍历第k行
		if(k >= n){ //遍历到了最后一行
			for(int i=0; i<n; i++){
				cout<<layout[i]<<"\t";
			}
			cout<<endl;
			*ret += 1;
			cout<<*ret<<endl;
		}
		else{
			for(int j = 0; j < n; j++){ //遍历该行的所有可能的列
				layout[k] = j;
				//第k行尝试放在(k, layout[k])，能放则放，并且遍历下一层，否则继续下一列尝试
				if(place(k, layout)){	
					backtrack(k+1, ret, n, layout);	//可以则遍历下一级
				}
			}
		}
	}
	bool place(int k, int *layout){ //约束函数，看看能不能放在(k, layout[k])
		for(int j = 0; j < k; j++)
			if(layout[j] == layout[k] || (layout[j]+j) == (layout[k]+k)
						|| (layout[j]-j) == (layout[k]-k)) //三条线上只要有一个不为0就不能放
			return false;
		return true;
	}
};

//test
int main(int argc, char const *argv[])
{
	Solution test;
	int n = 8;
	cout << n << "queens:" << test.totalNQueens(n) << endl;

	return 0;
}