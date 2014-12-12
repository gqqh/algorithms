/*heapsort.c:首先建立一个堆，然后依次把第一个跟最后一个换位置，并且同时调整堆。
 *分为大顶堆和小顶堆，下面分析时，单讲大顶堆。
 *A[0, ..., n-1]，看成一个完全二叉树，
 *	如果所有的i属于[0,1,..., (n/2)-1]：有l = 2*i+1, r = 2*i+2;
 *			1）A[i] >= A[l]
 *			2)如果右孩子存在(即：r < n), 则A[i] >= A[r]
 *   则认为A是一个大顶堆。
 *1）建立堆：从最后一个非叶子节点(i=(n/2)-1)开始，逐个向前进行调整堆，调整某一个节点时要递归向下到树底，
 *			确保以每一个节点为根的树是一个堆，直到树根。
 *		//A[0, ..., n-1]
 *		build_heap(A, n, adjust){
 *			for(i = (n/2)-1; i >= 0; --i){
 *				adjust(A, i, n)
 *			}
 *		}//end build_heap
 *2）调整堆思想：在A[0, ..., i, ..., n-1]上，调整以i为根的树是一个堆。
 *			//A[0, ..., i, ..., n-1];
 *		adjust(A, i, n){
 *			l = 2 * i + 1;
 *			r = 2 * i + 2;
 *			bigger = i;
 *		
 *			if (l < n && A[bigger] < A[l])
 *				bigger = l;
 *			if (r < n && A[bigger] < A[r])
 *				bigger = r;
 *			if (bigger != i){
 *				A[i] <---> A[bigger];
 *				adjust(A, bigger, n);
 *			}
 *		}//end adjust
 *3）排序思想：每次把第一个A[0]与A[k]交换，在A[0, ..., k-1]上进行调整堆。对应升序为大顶堆，降序为小顶堆。
 *		heap_sort(A, n, adjust){
 *			build_heap(A, n, adjust);
 *			for(i=n-1; i>0; --i){
 *				A[0] <---> A[i];
 *				adjust(A, 0, --n);
 *			}
 *		}			
 *每次把堆顶元素拿走之后，剩余的要重新调整，调整方案是把最后一个元素放在第一个，然后跟初始化一样了，
 *  这样能保证第一个元素是最大值（大顶堆），或者最小值（小顶堆）。
 *
 */

#include <stdio.h>

/*打印堆*/
void printer(int A[], int n){
	int i;
	for(i=0; i<n;i++){
		printf("%d ", A[i]);
	}
	printf("\n");
}
//在A[0, ..., i, ..., n-1]上调整为以A[i]为根的树是一个大顶堆
void heap_adjust_big(int A[], int i, int n){
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int bigger = i;

	/*如果左孩子存在，则跟左孩子比较*/
	if (l < n && A[bigger] < A[l])
		bigger = l;
	/*如果右孩子存在，则跟右孩子比较*/
	if (r < n && A[bigger] < A[r])
		bigger = r;
	/*如果父节点不是最小，则继续递归往下调整*/
	if (bigger != i){
		int tmp = A[i];
		A[i] = A[bigger];
		A[bigger] = tmp;

		heap_adjust_big(A, bigger, n);	
	}
}
//在A[0, ..., i, ..., n-1]上调整为以A[i]为根的树是一个小顶堆
void heap_adjust_small(int A[], int i, int n){
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int smaller = i;

	/*如果左孩子存在，则跟左孩子比较*/
	if (l < n && A[smaller] > A[l])
		smaller = l;
	/*如果右孩子存在，则跟右孩子比较*/
	if (r < n && A[smaller] > A[r])
		smaller = r;
	/*如果父节点不是最小，则继续递归往下调整*/
	if (smaller != i){
		int tmp = A[i];
		A[i] = A[smaller];
		A[smaller] = tmp;

		heap_adjust_small(A, smaller, n);	
	}
}
/*建堆*/
void build_heap(int A[], int n, void adjust(int *, int, int)){
	int i = (n / 2) - 1;
	for(; i >= 0; --i)
		adjust(A, i, n);
}
/*堆排序*/
void heap_sort(int A[], int n, void adjust(int *, int, int)){
	//创建堆
	build_heap(A, n, adjust);
	int i;
	/*从最后一个元素向前，依次与第一个元素交换，调整第一个元素为最大或者最小*/
	for(i = n-1; i > 0; --i){
		int tmp = A[0];
		A[0] = A[i];
		A[i] = tmp;
		adjust(A, 0, --n);
	}
}

/*test*/
int main(int argc, char const *argv[])
{
	/*测试大顶堆*/
	int A[] = {3, 12, 3, 4, 32, 9, 34, 3, 4, 11, 2, 3, 4, 200, 283, 12, 0, 4, 10};
	int n = sizeof(A) / sizeof(A[0]); 
	heap_sort(A, n, heap_adjust_big);
	printf("从小到大：\n");
	printer(A, n);
	
	/*测试小顶堆*/
	int B[] = {3, 12, 32, 9, 3, 34, 11, 3, 4, 200, 4, 283, 12, 2, 3, 4, 0, 4, 10};
	n = sizeof(B) / sizeof(B[0]);
	heap_sort(B, n, heap_adjust_small);
	printf("从大到小：\n");
	printer(B, n);
	
	return 0;
}

