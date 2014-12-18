/**
 * Same Tree :
 *  Given two binary trees, write a function to check if they are equal or not.
 *  Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
 */

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	/**
	 * 递归比较，如果左孩子右孩子以及自己等相等，则认为两个节点及其子树是相同的。
	 */
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(p == NULL && q == NULL)
        	return true;
        else if(p == NULL || q == NULL)
        	return false;
        else if(p->val == q->val)
        	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        else 
        	return false;
    }
};

//test
int main(int argc, char const *argv[])
{

	Solution test;
	struct TreeNode p(0), q(0);
	struct TreeNode t1(1);
	struct TreeNode t2(2);
	struct TreeNode t3(3);
	struct TreeNode t4(4);
	struct TreeNode t5(5);
	struct TreeNode t6(6);
	p.left = &t1;
	p.right = &t2;
	t1.left = &t3;
	t2.left = &t4;
	t4.right = &t5;
	t5.left = &t6;

	q.left = &t4;
	q.right = &t2;

	if(test.isSameTree(&p, &q))
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	return 0;
}