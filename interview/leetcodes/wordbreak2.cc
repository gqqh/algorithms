/*
 * Word Break II:
 * Given a string s and a dictionary of words dict, add spaces in s to construct a sentence 
 * 		where each word is a valid dictionary word.
 * 		Return all such possible sentences.
 *
 * For example, given 
 * s = "catsanddog",dict = ["cat", "cats", "and", "sand", "dog"].
 * A solution is ["cats and dog", "cat sand dog"].
 */
/*
 * 解题思路：可以利用动态规划，备忘录的方法，标记出那些地方可能是一些分词点。
 *  用f(i)表示s[0,...,i]是否可以划分，f(i)=true当且仅当存在j在[0,i]内有f(j)==true,同时s.substr(j, i-j)也是一个单词。
 *  当最终f(s.size())==true，则表示该string可以划分成单词。
 *  这题我们是要组成句子，
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
			if(flag[j] && (dict.find(s.substr(j, i-j)) != dict.end() || s[j] == ' ')){ //允许string中有空格
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