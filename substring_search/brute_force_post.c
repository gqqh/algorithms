//蛮力算法后缀比较法，是BM算法的原型
#include <stdio.h>
#include <string.h>

int cmp_count = 0; 	//纪录比较次数
int found[100];	//记录匹配成功的起始位置

//T为文本串，P为模式串
/*
 * 蛮力算法的另一种形式，整体从左向右匹配，但每一次具体匹配的过程中都是从模式串的后端向前匹配。
 * 函数返回匹配成功的次数，匹配失败返回0
 */
int bfp(char *T, char *P){
	int i, j;		//i遍历P串，j遍历T串
	int ret = 0;
	int tLen = strlen(T);
	int m = strlen(P);
	
	j = 0;
	while(j <= tLen - m){
		for(i = m -1; i >= 0; --i){
			cmp_count++;
			if(P[i] != T[j+i]){
				break;
			}
		}

		if(i == -1){	//匹配成功一次
			found[ret++] = j;
			j += m;
		}else{
			++j;
		}
	}
	return ret;
}
int main(){
	char *text = "hllolleolll hlleolleollellso hhelloow are yoheloeolleolllou? fine, thelleolleollllohanks! lleolleolland yhello?";
	char *pattern = "hello";
	//char *text = "hello hello how are yohellu? fine, thellohanks! and yellou?llllllllllllllllllllllllllllll";
	//char *pattern = "l";
	//GetNext(pattern, next);
	
	//打印，文本串从找到的起始位置到结束
	int ret = bfp(text, pattern);
	if(ret <= 0){
		printf("not found:%s...\n", pattern);
		return 0;
	}
	printf("found %d times.\n", ret);
	int i = 0;
	for(; i < ret; ++i){
		printf("found starts @[%d]:%s\n", found[i], (text+found[i]));	
	}
	printf("total compare %d times.\n", cmp_count);
	return 0;
}
