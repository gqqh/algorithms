//sunday算法
/*
 *基本思想是：每次从左到右匹配，如果匹配不成功就把模式串向右移动，
 *  移动的位置要看当前不匹配的串的末位对应的字符在模式串中第一次出现的位置。
 */
#include <stdio.h>
#include <string.h>

#define ASIZE 256	//字符表
int pos[ASIZE];		//字符对应的位置
int found[100]; 	//记录匹配成功的起始位置
int cmp_count = 0; 	//算法比较的次数

//T代表带匹配的串，P代表模式串 
/*求字符表中所有字符在模式串中从右端第一次出现的位置，没出现的做最大m处理
 *统计模式串中每个字符与结尾的距离加1,就是当匹配失败时，j向后移动的距离
 */
void GetPosition(char *P, int pos[]){
	int m = strlen(P);
	int i;
	for(i = 0; i < ASIZE; i++){
		pos[i] = m;
	}
	for(i = 0; i < m; ++i){
		pos[P[i]] = m - i;
	}
}
//sunday算法的实现部分，返回查到的位置，否则返回-1
int sunday_search(char *T, char *P){
	int i, j;	//j遍历模式串，i遍历文本串
	int tLen = strlen(T);
	int m = strlen(P);
	int ret = 0;

	j = 0;
	while(j <= tLen - m){
		for(i = m-1; i >= 0; --i){
			cmp_count++;
			if(P[i] != T[j+i]){
				break;
			}
		}

		if(i == -1){	//匹配成功退出
			found[ret++] = j;
			j += m;	
		}else{
			if(j + m >= tLen){	//越界
				break;
			}
			j += pos[T[j+m]];		
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
	//GetNext(pattern, next);
	
	//初始化字符表中每个字符在模式串中首次出现的位置
	GetPosition(pattern, pos);

	//打印，文本串从找到的起始位置到结束
	int ret = sunday_search(text, pattern);
	if(ret <= 0){
		printf("not found %s...\n", pattern);
		return 0;
	}
	printf("found %d times.\n", ret);
	int i;
	for(i = 0; i< ret; i++){
		printf("found starts @[%d]:%s\n", found[i], (text+found[i]));
	}
	printf("total compare %d times.\n", cmp_count);
	
	return 0;
}
