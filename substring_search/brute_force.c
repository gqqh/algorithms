//串匹配，蛮力办法，T为文本串，P为模式串
#include <stdio.h>
#include <stdlib.h>

int p[100];	//记录匹配成功的起始位置
int bfsearch(const char *T, const char *P){	//返回匹配成功的次数
	if(!T || !P || *T == '\0' || *P == '\0')
		return -1;
	int ret = 0;
	char *t1, *p1;
	t1 = T;
	int index = 0;
	while(*t1 != '\0'){
		char *tmp;
		p1 = P;
		tmp = t1;
		while(*tmp == *p1 && *tmp != '\0' && *p1 != '\0'){
			tmp++;
			p1++;
		}
		if(*p1 == '\0'){	//成功匹配一次
			p[ret] = index;
			ret ++;
		}
		t1++;	//文本串向后移
		index ++;
	}
	return ret;
}

//测试
int main(){
	char *text = "hello hello how are yohellu? fine, thellohanks! and yellou?";
	char *pattern = "hello";
	//char *text = "hello hello how are yohellu? fine, thellohanks! and yellou?llllllllllllllllllllllllllllll";
	//char *pattern = "l";
	printf("text:%s\npattern:%s\n", text, pattern);
	int ret = bfsearch(text, pattern);
	if(ret <= 0){
		printf("not found %s...\n", pattern);
		return 0;
	}
	printf("find %d times\n", ret);
	int i;
	for(i = 0; i < ret; i++){
		printf("found:%s\n", (text+p[i]));
	}
	return 0;
}