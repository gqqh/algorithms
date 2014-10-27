/*
 *Word Break
 * Given a string s and a dictionary of words dict, determine if s can be 
 * segmented into a space-separated sequence of one or more dictionary words.
 *
 *For example, given
 * s = "leetcode",
 * dict = ["leet", "code"].
 * Return true because "leetcode" can be segmented as "leet code".
 */
/*
 *解题思路；用一个bool flag[s.size()+1]作为标志,如果认为s[0...i]可以划分为多个单词，则flag[i+1]=true;如果最后f(i)=true,即存在j,使得f[j]=true 
 *				&& s.substr(j,i-j)在字典中查询到。另外，如果s[i] == ' ',则flag[i+1]=true;
 *		
 *		vector<bool> flag(s.size()+1, false);
 *		flag[0] = true;
 *		for(int i = 1; i <= s.size(); i++){
 *			if(flag[i-1] && s[i]==' '){
 *				flag[i] == true;
 *				continue;
 *			}
 *			for(int j = i - 1; j >= 0; j--){
 *			 	//flag[j]==true;代表从开始到j可以被分成若干个存在的词。
 *			 	//dict.find(s.substr()) != dict.end();表示s[j,i)这个词
 *			 	//s[j] == ' ';表示也有可能是这个空格，则空格也满足条件
 *				if(flag[j] && (dict.find(s.substr(j, i-j)) != dict.end() || s[j]==' '){
 *					flag[i] = true;
 *					break;
 *				}
 *			}
 *		}//end for
 *		return flag[s.size()];
 */				

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

bool wordBreak(string s, unordered_set<string> &dict) {
	int len = s.size();	
	vector<bool> flag(len + 1, false);
	flag[0] = true;

	for(int i = 1; i <= len; i++){
		for(int j = i - 1; j >= 0; j--){
//			if(flag[j] && (dict.find(s.substr(j, i-j)) != dict.end() || s[j] == ' ')){ //允许string中有空格
			if(flag[j] && dict.find(s.substr(j, i-j)) != dict.end()){ //不考虑string中有空格
				flag[i] = true;
				break;
			}
		}
	}

	return flag[len];
}

//test
int main(int argc, char const *argv[])
{
	unordered_set<string> dict{"leet", "cood", "hello", "world", "ni", "hao"};//, "leetcood"};
	string s = "leetcoodhelloworld   ni haoworld";
	printf("%d\n", wordBreak(s, dict));
	return 0;
}