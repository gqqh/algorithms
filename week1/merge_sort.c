#include <stdio.h>
#include <stdlib.h>

void merge_array(int *list1, int list1_size, int *list2, int list2_size);
void merge_sort(int *list, int list_size)
{
	if(list_size <= 1) 
		return;
	int *list1 = list;
	int list1_size = list_size / 2;
	int *list2 = list1 + list1_size;
	int list2_size = list_size - list1_size;

	merge_sort(list1, list1_size);
	merge_sort(list2, list2_size);

	merge_array(list1, list1_size, list2, list2_size);
}

void merge_array(int *l1, int ls1, int *l2, int ls2)
{
	int i = 0, j = 0, k = 0;
	int list[ls1 + ls2];
	while(i < ls1 && j < ls2){
		list[k++] = l1[i] < l2[j] ? l1[i++] : l2[j++];
	}
	while(i < ls1){
		list[k++] = l1[i++];
	}
	while(j < ls2){
		list[k++] = l2[j++];
	}

	for(i = 0; i < ls1 + ls2; i++)
		l1[i] = list[i];
}

int main()
{
	int n = 11;
	int num[11] = {3, 5, 2, 9, 1, 6, 8, 11, 4, 7, 10};
	merge_sort(num, n);
	
	int i = 0; 
	for(i = 0; i < n; i++)
		printf("%d ", num[i]);
	printf("\n");
	return 0;
}
