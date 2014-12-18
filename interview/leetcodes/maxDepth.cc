/**
 * Maximum Depth of Binary Tree
 * Given a binary tree, find its maximum depth.
 * The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
 */
/**
 * 递归解法：就每个节点而言，其深度为左孩子和右孩子最大深度加1，节点为空时返回深度0；
 */
#include <iostream>

using namespace std;

struct TreeNode{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class Solution {
public:
    int maxDepth(struct TreeNode *root) {
 		if(root == NULL)
 			return 0;
 		else
 			return (1 + max(maxDepth(root->left), maxDepth(root->right))); 
    }
private:
	int max(int a, int b){
		return a > b ? a : b;
	}
};

//test
int main(int argc, char const *argv[])
{

	Solution test;
	struct TreeNode root(0);
	struct TreeNode t1(1);
	struct TreeNode t2(2);
	struct TreeNode t3(3);
	struct TreeNode t4(4);
	struct TreeNode t5(5);
	struct TreeNode t6(6);
	root.left = &t1;
	root.right = &t2;
	t1.left = &t3;
	t2.left = &t4;
	t4.right = &t5;
	t5.left = &t6;

	int height = test.maxDepth(&root);
	cout << "height:" << height << endl;

	return 0;
}