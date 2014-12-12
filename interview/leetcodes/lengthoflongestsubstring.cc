/*Longest Substring Without Repeating Characters:
 * Given a string, find the length of the longest substring without repeating characters.
 * For example, the longest substring without repeating letters for "abcabcbb" is "abc", 
 * 		which the length is 3. 
 * For "bbbbb" the longest substring is "b", with the length of 1.
 */
/*大致思想：对于每一个字母记录其上一次出现的位置，与再次出现的位置的差就是到这个字母为止最长的子串了，
 *  同时应当每次出现重复字母时，就把所有哈希值都变成重复字母的第一个的位置。
 *  设一个起始的标杆，如果出现重复则把标杆移到第一个重复的字母的位置，如何判断字母重复？
 *  	可以根据该字母的哈希值和标杆位置比较即可，在标杆前不重复，标杆后重复。
 * 	同时应当记录一个到目前位置的最大长度，以及对应的下标，这样就可以记录最大子串了。
 *
 * 记录位置直接用256个ASCI值，时间复杂度为O(n)，n为字符串长度,空间复杂度O(1);
 */
#include <stdio.h>
#include <stdlib.h>

/**求string的最长不含重复字母的子串，使用一个int hash[256]记录每一个字母上一次出现的位置，
 * 		同时使用flag记录上一次出现重复字母的位置，注意，此处记录的是重复字母的第一个字母。然后每次比较新字母
 * 		的hash值和flag的位置关系判断新字母是否应该加入：
 * 			如果hash值 <= flag则可以加入，此时应当比较i-flag 与max的大小关系，如果已经比max大了，表示新的最长串出现了。
 * 			否则表示重复，则更新flag值。
 * 		注意每一新字母都要更新其hash值。 			
 * @param  s 输入串
 * @return   最大无重复字母子串长度
 */
int lengthOfLongestSubstring(char *s) {
    int hash[256];
    int flag = -1;
    int max = 0;
	int i;
	for(i = 0; i < 256; i++)
		hash[i] = -1;	

	i = 0;
	while(s[i] != 0){
		//先判断是否重复，若重复则
		// printf("%d:\t%c:hash=%d\tflag=%d\tmax=%d\t-->\t", i, s[i], hash[s[i]], flag, max);
		if(hash[s[i]] <= flag)
			max = (i-flag > max) ? i-flag : max;
		else
			flag = hash[s[i]];
	
		hash[s[i]] = i;
		// printf("hash=%d\tflag=%d\tmax=%d\n", hash[s[i]], flag, max);
		i++; 
	}

	return max;    
}
int main(int argc, char const *argv[])
{
	// char s[] = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";
	char s[] = "abcabcbb";
	printf("%s:%d\n", s, lengthOfLongestSubstring(s));
	char s1[] = "bbbbb";
	printf("%s:%d\n", s1, lengthOfLongestSubstring(s1));
	return 0;
}