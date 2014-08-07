//蛮力算法后缀比较法，是BM算法的原型
#include <stdio.h>
#include <string.h>

//T为文本串，P为模式串
int bfp(char *T, char *P){
	int i;		//遍历P串
	int j = 0;	//遍历T串
	int tLen = strlen(T);
	int pLen = strlen(P);
	while(j <= tLen - pLen){
		i = pLen - 1;
		while(i >= 0 && *(P + i) == *(T + j + i)){
			--i;
		}
		if(i == -1){
			return j;
		}
		j++;
	}
	return -1;
}
int main(){
	char *text = "hllolleolll hlleolleollellso how are yoheloeolleolllou? fine, thelleolleollllohanks! lleolleolland yhello?";
	char *pattern = "hello";
	//char *text = "hello hello how are yohellu? fine, thellohanks! and yellou?llllllllllllllllllllllllllllll";
	//char *pattern = "l";
	//GetNext(pattern, next);
	
	//打印，文本串从找到的起始位置到结束
	int ret = bfp(text, pattern);
	if(ret < 0){
		printf("not found:%s...\n", pattern);
		return 0;
	}
	printf("found starts @[%d]:%s\n", ret, (text+ret));
	
	return 0;
}
