//sunday算法
/*
 *基本思想是：每次从左到右匹配，如果匹配不成功就把模式串向右移动，
 *  移动的位置要看当前不匹配的串的末位对应的字符在模式串中第一次出现的位置。
 */
#include <stdio.h>
#include <string.h>

#define ASIZE 256	//字符表
int pos[ASIZE];		//字符对应的位置
//T代表带匹配的串，P代表模式串 

int cmp_count = 0; 	//算法比较的次数
//求字符表中所有字符在模式串中第一次出现的位置，没出现的做0处理
void GetPosition(char *P, int pos[]){
	int pLen = strlen(P);
	int i;
	for(i = 0; i < ASIZE; i++){
		pos[i] = 0;
	}
	for(i = pLen - 1; i >= 0; --i){
		pos[P[i]] = i;
	}
}
//sunday算法的实现部分，返回查到的位置，否则返回-1
int sunday_search(char *T, char *P){
	int i, j;
	int tLen = strlen(T);
	int pLen = strlen(P);

	j = 0;
	while(j <= tLen - pLen){
		for(i = 0; i < pLen; ++i){
			cmp_count++;
			if(P[i] != T[j+i]){
				break;
			}
		}
		if(i == pLen){	//匹配成功退出
			return j;
		}
		j += pLen - pos[T[j+1]];	
	}

	return -1;
}
//测试
int main(){
	char *text = "hllolleolll hlleolleollellso how are yoheloeolleolllou? fine, thelleolleollllohanks! lleolleolland yhello?";
	char *pattern = "hello";
	//char *text = "hello hello how are yohellu? fine, thellohanks! and yellou?llllllllllllllllllllllllllllll";
	//char *pattern = "l";
	//GetNext(pattern, next);
	
	//初始化字符表中每个字符在模式串中首次出现的位置
	GetPosition(pattern, pos);

	//打印，文本串从找到的起始位置到结束
	int ret = sunday_search(text, pattern);
	if(ret < 0){
		printf("not found:%s...\n", pattern);
		return 0;
	}
	printf("compare %d times, ", cmp_count);
	printf("found starts @[%d]:%s\n", ret, (text+ret));
	
	return 0;
}
