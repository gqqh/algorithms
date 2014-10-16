/*
 *Given an input string, reverse the string word by word.
 *For example,
 *Given s = "the sky is blue",
 *return "blue is sky the".
 
 *Clarification:
 *What constitutes a word?
 *A sequence of non-space characters constitutes a word.
 *Could the input string contain leading or trailing spaces?
 *Yes. However, your reversed string should not contain leading or trailing spaces.
 *How about multiple spaces between two words?
 *Reduce them to a single space in the reversed string.
 */
/*
 *算法思想：从后往前遍历一个字符串；逐个字符处理，使用两个下标i,j处理，j标记一个单词后面的
 *	空格；i继续往前遍历，进行一位预判
 *	如果i==0或者下一个是空格：则将substr(i,j)追加到返回值后面
 *		此时，如果i！=0，则返回值后面追加一个空格
 *	直到字符串处理结束。
 *
 * 另：自己又实现了一个，把每一个单词逆序处理的。："eht yks si eulb"
 */
/*
 *注意：编译需要添加编译选项：-std=c++11
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//stack
char *stack;
int size = 10;
int len = 0;	//栈中已有的元素个数

char *ret;
int rsize = 10;
int rlen = 0;	//返回字符串的个数

void init(){
	stack = (char *)malloc(sizeof(char) * size);
	ret = (char *)malloc(sizeof(char) * 10);
}
void free_m(){
	free(ret);
	free(stack);
}
void push(const char ch){
	if(len == size){
		size *= 2;
		stack = (char *)realloc(stack, size);
	}
	//push
	stack[len++] = ch;
}
//pop
char pop(){
	return stack[--len];
}

//把字符写入ret
void write_words(){
	bool flag = 0;	//如果写入内容，则置为1，否则为0
	if(len != 0){	//如果栈不为空，则拷贝
		flag = 1;
		while(len >= rsize - rlen){	//如果空间不够，则先拓展，要保证拓展的够到位
			rsize *= 2;
			ret = (char *)realloc(ret, rsize);
		}
		
		while(len > 0){
			ret[rlen] = pop();
			rlen++;
		} 	
	}
	if(flag){
		ret[rlen++] = ' ';
	}	
}
/*
 *
 */
void reverseWords1(string &s) {
	init();	//init stack
	int j = s.length()-1;
	int i = 0;
	while(i <= j){
		if (s[i] != ' '){	//非空入栈
			push(s[i]);
		}else{ 				//空字符则把非空栈中的内容出栈，赋值给
			write_words();
		}
		++i;
	}
	write_words();

	s.assign(ret, rlen);
	if(rlen > 1)
		s = s.erase(rlen -1); 	//删除最后一个空格
	free_m();
}

void reverseWords(string &s){
	int j = s.length();
	string rets= "";
	for(int i = s.length() - 1; i >= 0; i--){ //遍历
		if(s[i] == ' '){	//空格
			j = i; 	//记录最后一个空格
		}else if(i == 0 || s[i-1] == ' '){	//i前面就是空格
			rets += s.substr(i,j-i);
			if(s[i-1] == ' ')
				rets.append(" ");
		}
	}
	if(rets[rets.length()-1] == ' '){
		rets.pop_back();
	}
	s = rets;
}

  
int main(int argc, char const *argv[])
{
	string s = "  hello      world!     ";
	reverseWords1(s); //单词逆序
	cout <<"|"<< s <<"|" << endl;
	string s1 = "+---...2x+--x--+x-+-x2...---+";
	reverseWords(s1); //整体逆序，单词正常
	cout <<"|"<< s1 <<"|" << endl;
 
	return 0;
}
