//串匹配，蛮力办法，T为文本串，P为模式串
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int found[100];	//记录匹配成功的起始位置
int cmp_count = 0;	//纪录比较次数
/*
 * 蛮力算法，从前往后一次比较，不成功就继续向后移，成功则记录位置。
 */
int bfsearch(const char *T, const char *P){	//返回匹配成功的次数
	int ret = 0;
	int i, j;	//i遍历模式串，j遍历文本串
	int tLen = strlen(T);
	int m = strlen(P);
	
	j = 0;
	while(j <= tLen - m){
		for(i = 0; i < m; ++i){
			cmp_count++;
			if(T[j+i] != P[i]){
				break;
			}
		}
		
		if(i == m ){	//成功匹配一次
			found[ret++] = j;
			j += m;
		}else{
			++j;
		}
	}
	return ret;
}

//测试
int main(){
	char *text = "hllolleolll hlleolleollellso hhelloow are yoheloeolleolllou? fine, thelleolleollllohanks! lleolleolland yhello?";
	char *pattern = "hello";
	//char *text = "hello hello how are yohellu? fine, thellohanks! and yellou?llllllllllllllllllllllllllllll";
	//char *pattern = "l";
//	printf("text:%s\npattern:%s\n", text, pattern);
	int ret = bfsearch(text, pattern);
	if(ret <= 0){
		printf("not found %s...\n", pattern);
		return 0;
	}
	printf("find %d times\n", ret);
	int i = 0;
	
	for(i = 0; i < ret; i++){
		printf("found starts @[%d]:%s\n", found[i], (text+found[i]));
	}
	printf("total compare %d times.\n", cmp_count);
	return 0;
}