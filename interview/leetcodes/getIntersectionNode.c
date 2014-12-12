/*
 *Intersection of Two Linked Lists:
 * Write a program to find the node at which the intersection of two singly linked lists begins.
 * 
 * For example, the following two linked lists:
 * A:      a1 → a2
 *                 ↘
 *                  c1 → c2 → c3
 *                 ↗            
 * B: b1 → b2 → b3
 * begin to intersect at node c1.
 * 
 * Notes:
 * If the two linked lists have no intersection at all, return null.
 * The linked lists must retain their original structure after the function returns.
 * You may assume there are no cycles anywhere in the entire linked structure.
 * Your code should preferably run in O(n) time and use only O(1) memory.
 */

/*
 *解题思想：可以分别遍历A和B，记录下节点个数分别为Sa和Sb，然后求最小值min=(Sa, Sb)，
 * 			然后把A和B都移到一样长的位置，向后遍历一次比较。
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <stdio.h>

struct ListNode{
	int val;
	struct ListNode *next;
};
typedef struct ListNode ListNode;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int len_a = 0, len_b = 0;
        ListNode *a = headA;
        ListNode *b = headB;
        //求A，B的长度
        while(a != NULL){
        	len_a++;
        	a = a->next;
        }
        while(b != NULL){
        	len_b++;
        	b = b->next;
        }
        //把A，B尾对齐
        if(len_a >= len_b){
        	int delt = len_a - len_b;
        	while(delt > 0){
        		delt--;
        		headA = headA->next;
        	}
        }else{
        	int delt = len_b - len_a;
        	while(delt > 0){
        		delt --;
        		headB = headB->next;
        	}
        }

        //尾对齐后，一起向后遍历
        while(headA != headB){
        	headA = headA->next;
        	headB = headB->next;
        }

        return headA;
}

//测试
int main(int argc, char const *argv[])
{
	ListNode c3 = {33, NULL};
	ListNode c2 = {32, &c3};
	ListNode c1 = {31, &c2};

	ListNode a2 = {12, &c1};
	ListNode a1 = {11, &a2};
	
	ListNode b3 = {23, &c1};
	ListNode b2 = {22, &b3};
	ListNode b1 = {21, &b2};
	
        //找a和b的交点
	ListNode *ret = getIntersectionNode(&a1, &b1);
	printf("x:%d\n", ret == NULL ? -1 : ret->val);

	return 0;
}