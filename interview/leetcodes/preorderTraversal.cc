/**
 * Binary Tree Preorder Traversal
 * Given a binary tree, return the preorder traversal of its nodes' values.
 * For example:
 * Given binary tree {1,#,2,3},
 *    1
 *     \
 *      2
 *     /
 *   3
 * return [1,2,3].
 * Note: Recursive solution is trivial, could you do it iteratively?
 */
/**
 * 树的先序遍历：1）递归方法就是先访问节点，再分别递归访问左右孩子。
 * 				2）非递归方法就要借助栈来实现，记住父节点的右孩子：首先把非空根节点入栈，每次访问一个节点，就先把它的非空右孩子入栈，
 * 					再把非空左孩子入栈，只要栈不为空就一直循环从栈中pop一个节点访问。
 * 	注意：1）迭代的方法时，要注意右孩子先入栈，左孩子后入栈，而且每个节点只访问一次。
 * 		 2）空节点不入栈。
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};
class Solution {
public:
	/**
	 * 递归解法
	 */
    vector<int> preorderTraversal(struct TreeNode *root) {
    	vector<int> ret;
    	preorder(root, ret);
    	return ret;
    }
    /**
     * 迭代解法
     */
    vector<int> preTraversal(struct TreeNode *root){
    	vector<int> ret;
    	if(root == NULL)
    		return ret;
    	struct TreeNode *cur_ptr;
    	stack<struct TreeNode *> pstk;
    	pstk.push(root);
    	while(!pstk.empty()){
    		cur_ptr = pstk.top();
    		pstk.pop();
   			ret.push_back(cur_ptr->val); //空指针不压栈

   			if(cur_ptr->right != NULL)
   				pstk.push(cur_ptr->right);
   			if(cur_ptr->left != NULL)
   				pstk.push(cur_ptr->left);
       	}
       	return ret;
    }
private:
	void preorder(struct TreeNode *node, vector<int> &v){
		if(node == NULL)
			return;
		v.push_back(node->val);
		preorder(node->left, v);
		preorder(node->right, v);
	}
};

//test
int main(int argc, char const *argv[])
{
	Solution test;
	struct TreeNode n0(0);
	struct TreeNode n1(1);
	struct TreeNode n2(2);
	struct TreeNode n3(3);
	struct TreeNode n4(4);
	struct TreeNode n5(5);
	struct TreeNode n6(6);
	n0.left = &n1;
	n0.right = &n2;
	n1.left = &n3;
	n2.right = &n4;
	n3.right = &n5;
	n4.left = &n6;

	vector<int> ret = test.preorderTraversal(&n0);
	for(int i = 0; i < ret.size(); i++){
		cout<<"ret["<<i<<"]:"<<ret[i]<<endl;
	}
	struct TreeNode *n8 = NULL;
	vector<int> ret1 = test.preTraversal(n8);
	for(int i = 0; i < ret1.size(); i++){
		cout<<"ret1["<<i<<"]:"<<ret1[i]<<endl;
	}
	return 0;
}