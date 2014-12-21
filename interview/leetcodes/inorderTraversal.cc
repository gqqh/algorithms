/** 
 * Binary Tree Inorder Traversal
 * Given a binary tree, return the inorder traversal of its nodes' values.
 * For example:
 * Given binary tree {1,#,2,3},
 *    1
 *     \
 *      2
 *     /
 *    3
 * return [1,3,2].
 * Note: Recursive solution is trivial, could you do it iteratively?
 * OJ's Binary Tree Serialization:
 * The serialization of a binary tree follows a level order traversal, 
 * 	where '#' signifies a path terminator where no node exists below.
 * Here's an example:
 *    1
 *   / \
 *  2   3
 *     /
 *    4
 *     \
 *      5
 * The above binary tree is serialized as "{1,2,3,#,#,4,#,#,5}".
 */
/**
 * 两种方法
 * 	1）递归解法：先访问左孩子，再访问当前节点，最后访问右孩子。
 * 	2）迭代解法：从根节点开始向左走到头，走到头后出栈，向右走一步，再向左走到头。
 * 		p = root; 			//从根开始遍历	
 * 		stack.push(root);	//根入栈
 * 		while(!stack.empty() || p){	//只要栈不为空或者当前节点不为空就继续遍历
 * 			if(p){	//如果当前节点不为空就入栈，然后一直走到最左边一个孩子
 * 				stack.push(p);
 * 				p = p->left;
 * 			}else{ 	//当前节点为空，以为着到了最左边，则出栈一个节点，访问之，然后向右走一步。
 * 				p = stack.pop();
 * 				visit(p);
 * 				p = p->right;
 * 			}
 * 		}
 * 		
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
    vector<int> inorderTraversal(struct TreeNode *root) {
    	vector<int> ret;
    	inorder(root, ret);
    	return ret;
    }
    /**
     * 迭代解法
     */
    vector<int> inTraversal(struct TreeNode *root){
    	vector<int> ret;
    	if(root == NULL)
    		return ret;
    	struct TreeNode *cur_ptr = root;
    	stack<struct TreeNode *> pstk;
    	while(!pstk.empty() || cur_ptr != NULL){
    		if(cur_ptr != NULL){ 		//走到最左边
    			pstk.push(cur_ptr);
    			cur_ptr = cur_ptr->left;
    		}else{ 						//访问当前节点
    			cur_ptr = pstk.top();
    			pstk.pop();
    			ret.push_back(cur_ptr->val);
    			cur_ptr = cur_ptr->right;
    		}
       	}
       	return ret;
    }
private:
	void inorder(struct TreeNode *node, vector<int> &v){
		if(node == NULL)
			return;
		inorder(node->left, v);
		v.push_back(node->val);
		inorder(node->right, v);
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

	vector<int> ret = test.inorderTraversal(&n0);
	for(int i = 0; i < ret.size(); i++){
		cout<<"ret["<<i<<"]:"<<ret[i]<<endl;
	}
	struct TreeNode *n8 = &n0;
	vector<int> ret1 = test.inTraversal(n8);
	for(int i = 0; i < ret1.size(); i++){
		cout<<"ret1["<<i<<"]:"<<ret1[i]<<endl;
	}
	return 0;
}