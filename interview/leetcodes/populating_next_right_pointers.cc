/**
 * Populating Next Right Pointers in Each Node
 * Given a binary tree
 *     struct TreeLinkNode {
 *     TreeLinkNode *left;
 *     TreeLinkNode *right;
 *     TreeLinkNode *next;
 *     }
 * Populate each next pointer to point to its next right node. 
 * 	If there is no next right node, the next pointer should be set to NULL.
 * 	
 * 	Initially, all next pointers are set to NULL.
 * 	Note:
 * 	You may only use constant extra space.
 * 	You may assume that it is a perfect binary tree 
 * 		(ie, all leaves are at the same level, and every parent has two children).
 *      （满二叉树）
 * 	For example, Given the following perfect binary tree,
 *        1
 *      /  \
 *     2    3
 *    / \  / \
 *   4  5  6  7
 * After calling your function, the tree should look like:
 *        1 -> NULL
 *      /  \
 *     2 -> 3 -> NULL
 *    / \  / \
 *   4->5->6->7 -> NULL
 */
/**注意：这一题的意思是满二叉树
 * 使用层序遍历，并同时记录节点的编号i=1,该行最大的编号j=1，如果i>j,则j=j*2+1,每次元素
 * 		出队列时把其左右孩子都入队列，如果节点为空也把两个空节点入队列，保证形成一个完全二叉树。
 * 		使用last指向上一个节点，然后每次向后面找不为空的节点出队列，如果为空则继续出队列，
 * 		如果i>j则表示该行右边没有了节点，则last->next=NULL,同时出队列继续。直到队列为空，
 * 		或者一行都是空。
 */
#include <iostream>
#include <queue>

using namespace std;
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
struct TreeLinkNode {
	int val;
	struct TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};
class Solution {
public:
    /*
     *满二叉树
     */
    void connect(struct TreeLinkNode *root){
        if(root == NULL)    
            return;
        struct TreeLinkNode *cur = root;
        connect_helper(cur);
    }

    // void connect1(struct TreeLinkNode *root) {
    // 	if(root == NULL) return;
    // 	bool flag = false; 	//表示当前行是否全空
    // 	queue<struct TreeLinkNode *> lqueue;
    // 	struct TreeLinkNode *cur, *last;
    // 	last->next = NULL;
    // 	lqueue.push(root);
    // 	int i = 1, level = 1;
    //     last = root;
    // 	while(!flag){
            
    // 	}
    // }
private:
    void connect_helper(struct TreeLinkNode *node){
        if(node->left != NULL){
            node->left->next = node->right;
            if(node->next != NULL){
                node->right->next = node->next->left;
            }
            connect_helper(node->left);
            connect_helper(node->right);
        }
    }

    // int leavel_nodes(int t){
    //     int ret = 1;
    //     for(int i = 1; i < t; i++)
    //         ret *= 2;
    // }
};
void printer(struct TreeLinkNode *node){
    if(node == NULL)
        return;
    cout<<"node:"<<node->val;
    if(node->left != NULL){
        cout<<"\tleft:"<<node->left->val;
    }else{
        cout<<"\tleft: NULL";
    }
    if(node->right != NULL){
        cout<<"\tright:"<<node->right->val;
    }else{
        cout<<"\tright: NULL";
    }
    if(node->next != NULL){
        cout<<"\tnext:"<<node->next->val<<endl;
    }else{
        cout<<"\tnext: NULL" <<endl;
    }
}
//test
int main(int argc, char const *argv[])
{
	Solution test;
	struct TreeLinkNode n0(0);
	struct TreeLinkNode n1(1);
	struct TreeLinkNode n2(2);
	struct TreeLinkNode n3(3);
	struct TreeLinkNode n4(4);
	struct TreeLinkNode n5(5);
	struct TreeLinkNode n6(6);
	n0.left = &n1;
	n0.right = &n2;
	n1.left = &n3;
    n1.right = &n4;
    n2.left = &n5;
	n2.right = &n6;
	test.connect(&n0);

    printer(&n0);
    printer(&n1);
    printer(&n2);
    printer(&n3);
    printer(&n4);
    printer(&n5);
    printer(&n6);

	return 0;
}