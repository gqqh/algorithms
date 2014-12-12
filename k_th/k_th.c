#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*1、先排序，选出第k个数，复杂度O（nlogn）;破坏了原来数据的顺序；*/
int cmp(const void *a, const void *b){
	if( *((int *)a) >= *((int *)b))
		return -1;
	return 1;
}
int k_th1(int S[], int n, int k){
	qsort(S, n, sizeof(S[0]), cmp);
	return S[k-1];
}

/* 2、用选择排序，选择k次，找出第k大的数，复杂度O（n*k）；破坏原来数据顺序； */
int k_th2(int S[], int n, int k){
	int i, j, max;
	for(i = 0; i < k; i++){
		max = i;
		for(j = i; j < n; j++){
			if(S[j] > S[max]){
				max = j;
			}
		}
		int tmp = S[max];
		S[max] = S[i];
		S[i] = tmp;
	}

	return S[k-1];
}

/*3、使用快速排序的思想，从数组S中随机选出一个元素X，把数组分成Sa和Sb两部分，Sa中的元素小于等于X，Sb中元素大于等于X。这时有两种情况：
 *	1）如果Sb中元素个数小于k-1（即Sa中元素个数大于n-k个），则问题变为从Sa中找出第（k-|Sb|-1）大的数；
 *	2）如果Sb中元素个数大于k-1（即Sa中元素个数小于n-k个），则问题变为从Sb中找出第（k）大的数；
 *	3）如果Sb中元素个数等于k-1（即Sa中元素个数等于n-k个），则X即为第k大的数。
 *	
 *	复杂度为：O（n）；
 */
int _k_th3(int S[], int b, int e, int k){
	int n = e - b + 1;
	if(e < b || e-b+1 < k)	return;
	/*随机从S[b, ..., e]中找一个元素作为比较值*/
	int t = random() % n + b;
	int p = S[t];
	S[t] = S[b];
	int low = b, high = e;
	
	while(low < high){
		//从高往低
		while(low < high){
			if(S[high] >= p)
				high--;
			else{
				S[low++] = S[high];
				break;
			}
		}
		//从低往高
		while(low < high){
			if(S[low] <= p)
				low++;
			else{
				S[high--] = S[low];
				break;
			}
		}
	}//end while
	S[low] = p;
	// int j;
	// printf("b=%d, e=%d, t=%d, low=%d, k=%d\n", b, e, t, low, k);
	// for(j=b; j <= e; j++)
	// 	printf("%d ", S[j]);
	// printf("\n\n");
	/*|Sa|=low-b, |Sb|=e-low*/
	if(e-low == k - 1){ //|Sb| = k-1
		return S[low];
	}else if(e-low > k-1){ 
		return _k_th3(S, low+1, e, k);
	}else{
		return _k_th3(S, b, low-1, k-(e-low+1));
	}	
}
int k_th3(int S[], int n, int k){
	return _k_th3(S, 0, n-1, k);
}

/* 4、在原数组上建大顶堆O(n)，然后pop出k次即可得到第k大数，复杂度为O(klogn);复杂度为O（n+klogn）； */
/*调整大顶堆*/
void heap_adjust(int S[], int i, int n){
	int l = i * 2 + 1;
	int r = i * 2 + 2;
	int bigger = i;

	if (l < n && S[bigger] < S[l])
		bigger = l;
	if (r < n && S[bigger] < S[r])
		bigger = r;
	if (bigger != i){
		int tmp = S[i];
		S[i] = S[bigger];
		S[bigger] = tmp;

		heap_adjust(S, bigger, n);
	}
}
/*在[0, ..., n-1]上建调整大顶堆*/
void build_heap(int S[], int n){
	int i;
	for (i = n/2 - 1; i >= 0; --i){
		heap_adjust(S, i, n);
	}
}
int k_th4(int S[], int n, int k){
	build_heap(S, n);
	
	int i, ret;
	for(i = 0; i < k; ++i){
		ret = S[0];
		S[0] = S[n-1-i];
		S[n-1-i] = ret;
		/*每次从0开始往下调整，此时数组的考虑长度为n-1-i*/
		heap_adjust(S, 0, n-1-i);
	}

	return ret;
}

/* 5、维护一个小顶堆，然后将S中剩余的数依次跟堆顶比较，如果大于堆顶则替换，并调整堆；
 * 	  如果小于堆顶则继续下一个比较。复杂度O（n*logk）； 
 */
/*调整小顶堆*/
void heap_adjust_small(int *heap, int i, int k){
	int l = i * 2 + 1;
	int r = i * 2 + 2;
	int smaller = i;

	if (l < k && heap[smaller] > heap[l])
		smaller = l;
	if (r < k && heap[smaller] > heap[r])
		smaller = r;
	if (smaller != i){
		int tmp = heap[i];
		heap[i] = heap[smaller];
		heap[smaller] = tmp;
		heap_adjust_small(heap, smaller, k);
	}
}
/*建立一个小顶堆A[0, ..., k-1];*/
void build_heap_small(int *heap, int k){
	int i; 
	for(i = k/2 - 1; i >= 0; --i){
		heap_adjust_small(heap, i, k);
	}
}
/*插入t到小顶堆，*/
void heap_insert(int *heap, int k, int t){
	if (t > heap[0]){
		heap[0] = t;
		heap_adjust_small(heap, 0, k);
	}
}
int k_th5(int S[], int n, int k){
	int *heap = (int *)malloc(sizeof(int) * k);
	int i; 
	for(i = 0; i < k; i++)
		heap[i] = S[i];

	build_heap_small(heap, k);
	for(; i < n; i++){
		heap_insert(heap, k, S[i]);
	}

	return heap[0];
}

/* 6、用hash保存每个元素出现的次数，结合计数排序的思想，找出第k大的数。
 *	  假设所有元素出现的范围为[0, m],时间复杂度O（n+m）；空间复杂度O(n+m);
 */
int k_th6(int S[], int n, int k){
	int max_num = 1000; //假设所有可能的数在[-max_num, max_num)之间
	int *hash = (int *)malloc(sizeof(int) * 2 * max_num);
	if(hash == NULL){
		perror("malloc");
		exit(0);
	}

	memset(hash, 0, 2 * max_num * sizeof(int));
	int i;
	for(i = 0; i < n; i++)
		hash[S[i] + max_num] += 1;
	
	int count = 0;
	for(i = 2 * max_num - 1; i >= 0; i--){
		count += hash[i];
		if(count >= k)
			break;
	}
	return i - max_num;
}

/*test main*/
int main(int argc, char const *argv[])
{
	while(1){
	int S1[] = {2, 3, 4, 1, 3, 9, 8, 2, 10, 299, 323, 123, -12, 23, -434, 67};
	int n = sizeof(S1) / sizeof(S1[0]);
	int k = 0;
	while(k < 1 || k > n){
		printf("input k in [1, %d]:", n);
		scanf("%d", &k);
		if(k == -1)
			return;
	}
	//k_th1
	printf("k_th1:%d-th num is :%d\n", k, k_th1(S1, n, k));
	//k_th2
	int S2[] = {2, 3, 4, 1, 3, 9, 8, 2, 10, 299, 323, 123, -12, 23, -434, 67};
	printf("k_th2:%d-th num is :%d\n", k, k_th2(S2, n, k));
	//k_th3
	int S3[] = {2, 3, 4, 1, 3, 9, 8, 2, 10, 299, 323, 123, -12, 23, -434, 67};
	printf("k_th3:%d-th num is :%d\n", k, k_th3(S3, n, k));
	//k_th4
	int S4[] = {2, 3, 4, 1, 3, 9, 8, 2, 10, 299, 323, 123, -12, 23, -434, 67};
	printf("k_th4:%d-th num is :%d\n", k, k_th4(S4, n, k));
	//k_th5
	int S5[] = {2, 3, 4, 1, 3, 9, 8, 2, 10, 299, 323, 123, -12, 23, -434, 67};
	printf("k_th5:%d-th num is :%d\n", k, k_th5(S5, n, k));
	//k_th6
	int S6[] = {2, 3, 4, 1, 3, 9, 8, 2, 10, 299, 323, 123, -12, 23, -434, 67};
	printf("k_th6:%d-th num is :%d\n", k, k_th6(S6, n, k));
	}
	return 0;
}