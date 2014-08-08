//kmpsearch
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next[100];
int cmp_count = 0;	//统计比较次数
//T为文本串，P为模式串，返回匹配成功的起始位置在T中的下标，匹配失败时返回-1
int kmpsearch(char *T, char *P){
	int i = 0, j = 0;
	int tLen = strlen(T);
	int pLen = strlen(P);

	while(i < tLen && j < pLen){		//开始匹配
		if(j == -1 || T[i] == P[j]){	//j==-1表示重新匹配模式串的开始；T[i]==P[j]表示匹配成功，然后匹配下一个
			cmp_count++;
			++i;	//i始终向前移动
			++j;	//如果匹配成功则模式串向前走，否则就是j==-1,往前走一步就是令j=0;
		}else{
			j = next[j];	//j向前跳到上一个匹配的位置
		}
	}//end of while

	if(j == pLen){
		return i - j;
	}else{
		return -1;
	}
}

//计算模式串的next数组
void GetNext(char *P, int next[]){
	int pLen = strlen(P);
	next[0] = -1;	//初始化next[0]为-1
	int k = -1;		//next[j] = k
	int j = 0;		//遍历模式串

	while(j < pLen - 1){	//第一个已经初始化，而且是先自加再赋值
		if(k == -1 || P[j] == P[k]){	//k==-1表示递归到了next[0]; P[j]==p[k]表示在之前的基础上又匹配成功了一个
			++j;
			++k;
			next[j] = k;	//如果k==-1,表示又重新匹配，则next[j]=0;否则，表示匹配成功了一个，则next[j]=k;
		}else{
			k = next[k];	//匹配失败则k以上次匹配成功的位置向前遍历
		}
	}//end of while
}
//优化过的计算模式串的next数组
void GetNextOP(char *P, int next[]){
	int pLen = strlen(P);
	next[0] = -1;	//初始化next[0]为-1
	int k = -1;		//next[j] = k
	int j = 0;		//遍历模式串

	while(j < pLen - 1){	//第一个已经初始化，而且是先自加再赋值
		if(k == -1 || P[j] == P[k]){	//k==-1表示递归到了next[0]; P[j]==p[k]表示在之前的基础上又匹配成功了一个
			++j;
			++k;
			if(P[j] != P[k]){	//此时的j和k都已经向后移了
				next[j] = k;	//如果k==-1,表示又重新匹配，则next[j]=0;否则，表示匹配成功了一个，则next[j]=k;
			}else{	//因为如果p[j]==p[k]时，且p[j+1]==p[k+1]，则有next[j+1]=next[next[k+1]]
					//如果匹配到p[j]失败时，会后退到p[next[j]]，如果p[j]==p[next[j]],则肯定会失败，多比较一次
				next[j] = next[k];
			}
		}else{
			k = next[k];	//匹配失败则k以上次匹配成功的位置向前遍历
		}
	}//end of while	
}

//测试
int main(){
	char *text = "helllolleolll hlleolleollellso how are yohelleolleolllou? fine, thelleolleollllohanks! lleolleolland yhello?";
	char *pattern = "lleolleoll";
	//char *text = "hello hello how are yohellu? fine, thellohanks! and yellou?llllllllllllllllllllllllllllll";
	//char *pattern = "l";
	//GetNext(pattern, next);

	//求模式串的next数组
	GetNextOP(pattern, next);
	int i = 0;
	int pLen = strlen(pattern);
	
	//打印next数组
	printf("next:");
	for(; i < pLen; i++){
		printf("%d ", next[i]);
	}
	printf("\ntext:%s\npattern:%s\n", text, pattern);
	
	//打印，文本串从找到的起始位置到结束
	int ret = kmpsearch(text, pattern);
	printf("compare %d times, ", ret);
	if(ret < 0){
		printf("not found %s...\n", pattern);
		return 0;
	}
	printf("found:%s\n", (text+ret));
	
	return 0;
}
