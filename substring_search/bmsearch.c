//BM算法，在后缀比较蛮力算法的基础上修改
#include <stdio.h>
#include <string.h>

#define ASIZE 256	//字符个数
#define PSIZE 100	//模式串大小

int cmp_count = 0;
int found[100]; 	//记录匹配成功的起始位置

//T为待匹配的文本串，P用来识别的模式串，m为P的长度
//求坏字符移动数组；
/*坏字符匹配原则有两条：
 *1:如果坏字符'*'没有出现在模式串中（即bmBc['*'] = m），
 *    则将模式串移动到坏字符的后面一位，shift(bc) = i + 1; //shift(bc) = i - (m - 1 - m)
 *2:如果坏字符'*'出现在模式串中第k位（即bmBc['*'] = k），
 *    则将模式串的第k位对应到坏字符的那一位，shift(bc) = i - (m - 1 - bmBc['*'])
 *所以：模式串最终移动的位数为：shift(bc) = i - (m - 1 - bmBc['*']) = bmBc['*'] + i + 1 - m; 
*/
void preBmBc(char *P, int bmBc[]){
	int m = strlen(P);	//模式串长度
	int i;
	//初始化所有字符距离为最大值m
	for(i = 0; i < ASIZE; i++){
		bmBc[i] = m;	
	}
	//统计每个字符的距离右侧的最小距离，注意bmBc[P[m-1]] = m
	for(i = 0; i < m-1; i++){
		bmBc[P[i]] = m-1-i;
	}
}

//求好前缀需要的suffix数组，suff[i]的大小为k，m表示模式串长度,从P[i]开始往前的k个字符（P[i-k+1,...,i]）等于P的最后k个字符（P[m-k,...,m-1]）。
//即：for 1 <= i < m; suff[i] = max{k : P[i-k+1, ..., i] = P[m-k, ..., m-1]}.
//如果存在超过一个好前缀，则取最左边的一个
void suffix(char *P, int *suff){
	int m = strlen(P);
	suff[m-1] = m;
	int i, j;	//suff[i] = i - j
	for(i = m-2; i >= 0; --i){
		j = i;
		while(j >= 0 && P[j] == P[m-1-(i - j)]){
			--j;
		}
		suff[i] = i - j;	//j从i开始往前遍历
	}
}

//计算好前缀移动数组
/*
 * 好前缀有三种情况：
 * 1)找到好前缀，如果出现多次则选最左边的一个：
 *		j从0到m-2，如果suff[j]==m-1-i，则bmGs[i]=m-1-j;
 * 2)没有好前缀，则找好前缀的最大后缀： 
 *		i从m-1到0，如果有suff[i]==i+1,则从i+1到m-1-i-1的最大前缀都是m-1-i
 * 3)既不能匹配好后缀也不能找到好后缀的最大前缀时，移动距离为m
 */
void preBmGs(char *P, int bmGs[]){
	int i, j, suff[PSIZE];
	int m = strlen(P);

	suffix(P, suff);	//初始化suff数组
	
	//既不能匹配好后缀也不能找到好后缀的最大前缀时，移动距离为m
	for(i = 0; i < m; ++i){
		bmGs[i] = m;	
	}

	//初始化好后缀的最大前缀
	j = 0;	
	for(i = m-1; i >= 0; --i){
		if(suff[i] == i+1){			//suff[i]==i+1表示，P[0,...,i]为一个最大前缀
			for(; j < m-1-i; ++j){	//j从0到m-1-i
				if(bmGs[j] == m){	//未修改则改为m-1-i表示P[...,i]==P[...,m]
					bmGs[j] = m - 1 - i;
				}
			}//for
		}//if
	}//for
	//初始化好后缀
	for(i = 0; i <= m-2; ++i){
		bmGs[m-1-suff[i]] = m - 1 - i;
	}
}

//T为文本串，P为模式串，成功返回找到次数，失败返回0
int bmsearch(char *T, char *P){
	int i, j, bmGs[PSIZE], bmBc[ASIZE];
	
	//初始化坏字符数组和好前缀数组
	preBmGs(P, bmGs);
	preBmBc(P, bmBc);

	int m = strlen(P);
	int tLen = strlen(T);
	int ret = 0;

	j = 0; 
	while(j <= tLen - m){				//j从前往后遍历文本串
		for(i = m - 1; i >= 0; --i){	//i从后往前遍历模式串
			cmp_count++;
			if(T[j + i] != P[i]){
				break;
			}
		}

		if(i == -1){	//表示匹配成功
			found[ret++] = j;
			j += m;
		}else{
			j += (bmGs[i] > (bmBc[P[i]] - m + 1 + i) ? bmGs[i] : (bmBc[P[i]] - m + 1 + i));	
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
	int ret = bmsearch(text, pattern);
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
