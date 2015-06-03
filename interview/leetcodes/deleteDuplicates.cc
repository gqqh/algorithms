/**
 * Remove Duplicates from Sorted List
 * Given a sorted linked list, delete all duplicates such that each element appear only once.
 * For example,
 * Given 1->1->2, return 1->2.
 * Given 1->1->2->3->3, return 1->2->3.
 */
#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
typedef struct ListNode{
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL){}
} ListNode;

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
		if(head == NULL)
			return head;
		ListNode *cur, *post;
		cur = head;
		post = cur->next;
		while(post != NULL){
			if(cur->val == post->val){
				// delete(post);
				post = post->next;
				cur->next = post;
			}else{
				cur = post;
				post = post ->next;
			}
		}
		return head;        
    }
};

//test
int main(int argc, char const *argv[])
{
	Solution test;
	ListNode n0(1);
	ListNode n1(1);
	ListNode n2(2);
	ListNode n3(3);
	ListNode n4(3);
	ListNode n5(4);
	n0.next = &n1;
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	// n4.next = &n5;

	test.deleteDuplicates(&n0);
	ListNode *cur = &n0;
	while(cur!= NULL){
		cout<<cur->val<<endl;
		cur = cur->next;
	}

	return 0;
}