//kmpsearch
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next[100];
int cmp_count = 0;	//统计比较次数
int found[100]; 	//记录匹配成功的起始位置

//T为文本串，P为模式串
/*
 *1)kmp算法利用了匹配过的信息，重新利用已经匹配过的串，每次从左向右匹配，如果不匹配就令j = next[j];
 *2)next[j]的含义是，如果当前字符不匹配时，就从模式串中查找已经匹配过的坏字符前面几个字符与开头的几个字符相同，
 *		这样就可以用开头的几个字符与坏字符前面的几个字符对应，从而可以后面的继续匹配。
 *3)计算next数组时，next[i] = max{k : P[0,...,k-1] == P[i-k,..., i-1]}， next[0]=-1
 *4)计算next数组的算法是：初始化next[0]=-1， 然后递归求解, 由next[j]=k，求next[j+1]
 *	a)若	P[j] == P[k]，则next[j+1] = next[j]+1 = k+1;
 *	b)若P[j] != P[k], 则令k=next[k]，依次继续向前找，直到P[j] == P[k]或者next[k]==-1,然后再next[j+1] = next[j]+1 = k+1;
 *5)优化过的计算next数组，详见过程分析
 */
//返回匹配成功的次数，匹配失败时返回0
int kmpsearch(char *T, char *P){
	int i, j;	//i遍历P，j遍历T
	int tLen = strlen(T);
	int m = strlen(P);
	int ret = 0;

	j = 0;
	while(j <= tLen - m){	//遍历文本串T
		for(i = 0; i < m; i++){	//遍历模式串P
			cmp_count++;
			if(T[j+i] != P[i]){	//不匹配
				break;
			}
		}
		
		if(i == m){		//匹配成功
			found[ret++] = j;
			j += m;		//跳一个模式串长度
		}else{
			j += i - next[i];	//跳到下一个位置
		}	
	}
	
	return ret;
}

//计算模式串的next数组
void GetNext(char *P, int next[]){
	int m = strlen(P);
	next[0] = -1;	//初始化next[0]为-1
	int k = -1;		//next[j] = k
	int j = 0;		//遍历模式串

	while(j < m - 1){	//第一个已经初始化，而且是先自加再赋值
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
	int m = strlen(P);
	next[0] = -1;	//初始化next[0]为-1
	int k = -1;		//next[j] = k
	int j = 0;		//遍历模式串

	while(j < m - 1){	//第一个已经初始化，而且是先自加再赋值
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
	char *text = "hllolleolll hlleolleollellso hhelloow are yoheloeolleolllou? fine, thelleolleollllohanks! lleolleolland yhello?";
	char *pattern = "hello";
	//char *text = "hello hello how are yohellu? fine, thellohanks! and yellou?llllllllllllllllllllllllllllll";
	//char *pattern = "l";
	//GetNext(pattern, next);

	//求模式串的next数组
	GetNextOP(pattern, next);
	int i = 0;
		
	//打印next数组
/*	int m = strlen(pattern);
	printf("next:");
	for(; i < m; i++){
		printf("%d ", next[i]);
	}
	printf("\ntext:%s\npattern:%s\n", text, pattern);
*/	
	//打印，文本串从找到的起始位置到结束
	int ret = kmpsearch(text, pattern);
	if(ret <= 0){
		printf("not found %s...\n", pattern);
		return 0;
	}
	printf("found %d times.\n", ret);
	for(; i< ret; i++){
		printf("found starts @[%d]:%s\n", found[i], (text+found[i]));
	}
	printf("total compare %d times.\n", cmp_count);
	
	return 0;
}
