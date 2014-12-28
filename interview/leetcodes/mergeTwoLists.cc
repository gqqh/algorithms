/**
 * Merge Two Sorted Lists
 * Merge two sorted linked lists and return it as a new list. 
 * The new list should be made by splicing together the nodes of the first two lists.
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * merge两个有序链表：用两个指针，从头到尾依次遍历两个表，把小的元素添加到合并后的链表的尾部；
 * 	如果有一个链表到尾部了，就直接把另一个链表添加到返回指针的尾部。
 */
#include <iostream>
using namespace std;

typedef struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
} ListNode;
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *p1, *p2, *ret, *tail;
        p1 = l1;
        p2 = l2;
        if(p1 == NULL)
        	return p2;
        if(p2 == NULL)
        	return p1;
        if(p1->val < p2->val){
        	ret = p1;
        	p1 = p1->next;
        }else{
        	ret = p2;
        	p2 = p2->next;
        }
        tail = ret;
        while(p1 != NULL && p2 != NULL){
        	if(p1->val < p2->val){
	      		tail->next = p1;
	      		p1 = p1->next;
        	}else{
        		tail->next = p2;
        		p2 = p2->next;
        	}
        	tail = tail->next;
        }
        if(p1 == NULL){
        	tail->next = p2;
        }else{
        	tail->next = p1;
        }

        return ret;
    }
};

//test
int main(int argc, char const *argv[])
{
	Solution test;
	ListNode a0(10);
	ListNode a1(11);
	ListNode a2(12);
	ListNode a3(13);
	a0.next = & a1;
	a1.next = & a2;
	a2.next = & a3;
	ListNode b0(1);
	ListNode b1(12);
	ListNode b2(14);
	b0.next = & b1;
	b1.next = & b2;
	ListNode *nul = NULL;

	ListNode *ret = test.mergeTwoLists(&a0, nul);
	ListNode *tmp = ret;
	while(tmp != NULL){
		cout<<tmp->val<<"-->";
		tmp = tmp->next;
	}
	cout <<endl;
	return 0;
}