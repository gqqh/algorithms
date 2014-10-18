/*
 *堆排序：分为大顶堆和小顶堆，下面分析时，单讲大顶堆。
 *A[0,1,2,...,n-1]，看成一个完全二叉树，
 *如果所有的i属于[0,1,...,n/2 -1]：
 *			1）A[i] >= A[2i+1]
 *			2)2i+2<n,则A[i] >= A[2i+2]
 *则认为A是一个大顶堆。
 *
 *for(i = n/2 -1; i >=0; i--):
 *	if(i * 2 + 2 == n):	//i只有左孩子
 *		if(A[2*i] >= A[2*i+1]):
 *			A[2*i] <--> A[2*i+1]
 *		else:
 *			continue;
 *	if(A[i] >= A[2*i+1] && A[i] >= A[2*i+2]):
 *		continue;
 *	else if(A[i] < A[2*i+1]):
 *		A[i] <--> A[2*i+1]
 *	else:
 *		A[i] <--> A[2*i+2] 			
 * //堆初始化完毕				
 *每次把堆顶元素拿走之后，剩余的要重新调整，调整方案是把最后一个元素放在第一个，然后跟初始化一样了。
 *
 */

#include <stdio.h>
/*
 *对A[0,1,...,n-1]进行堆调整
 */
void printer(int A[], int n){
	int i;
	for(i=0; i<n;i++){
		printf("%d ", A[i]);
	}
	printf("\n");
}
void heap_adjust_big(int A[], int n){ 	//大顶堆，用来排序作为从小到大排序用的，因为每次交换首位两个元素
	int i;
	for (i = n/2 - 1; i >= 0; --i){
		if (i*2 + 2 == n){ 	//最后一个节点只有左孩子
 			if (A[i] < A[2*i+1]){
 				int tmp = A[i];
 				A[i] = A[2*i+1];
 				A[2*i+1] = tmp;
 			}
		}else{
			if(A[i] >= A[2*i+1] && A[i] >= A[2*i+2]){
				continue;
			}else if(A[2*i+1] >= A[2*i+2]){
				int tmp = A[i];
 				A[i] = A[2*i+1];
 				A[2*i+1] = tmp;	
			}else{
				int tmp = A[i];
 				A[i] = A[2*i+2];
 				A[2*i+2] = tmp;
			}
		}
	}
}

void heap_adjust_small(int A[], int n){
	int i;
	for (i = n/2 - 1; i >= 0; --i){
		if (i*2 + 2 == n){ 	//最后一个节点只有左孩子
 			if (A[i] > A[2*i+1]){
 				int tmp = A[i];
 				A[i] = A[2*i+1];
 				A[2*i+1] = tmp;
 			}
		}else{
			if(A[i] <= A[2*i+1] && A[i] <= A[2*i+2]){
				continue;
			}else if(A[2*i+1] <= A[2*i+2]){
				int tmp = A[i];
 				A[i] = A[2*i+1];
 				A[2*i+1] = tmp;	
			}else{
				int tmp = A[i];
 				A[i] = A[2*i+2];
 				A[2*i+2] = tmp;
			}
		}
	}
}
void heap_sort(int A[], int n, void heap_adjust(int *, int )){
	int i, tmp;
	for(i = n; i > 1; --i){
		heap_adjust(A, i);
		tmp = A[0];
		A[0] = A[i-1];
		A[i-1] = tmp;
	}
}

int main(int argc, char const *argv[])
{
	int A[] = {3, 12, 32, 9, 34, 11, 200, 283, 12, 0, 4, 10};
	int n = sizeof(A) / sizeof(A[0]);
	heap_sort(A, n, heap_adjust_big);
	printf("从小到大：\n");
	printer(A, n);
	
	int B[] = {3, 12, 32, 9, 34, 11, 200, 283, 12, 0, 4, 10};
	n = sizeof(B) / sizeof(B[0]);
	heap_sort(B, n, heap_adjust_small);
	printf("从大到小：\n");
	printer(B, n);
	return 0;
}

