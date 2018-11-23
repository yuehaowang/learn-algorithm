/************
 * http://hihocoder.com/problemset/problem/1049
 */

#include <iostream>
#include <string>

using namespace std;

struct node
{
	char val;
	node* left;
	node* right;
};

void postorder(node* root)
{
	if (root == nullptr) {
		return;
	}

	postorder(root -> left);
	postorder(root -> right);
	cout << root -> val;
}

node* build_tree(const string& preorder, const string& inorder)
{
	if (preorder.size() <= 0) {
		return nullptr;
	}

	char val = preorder[0];

	int pos = inorder.find(val);

	node* n = new node;
	n -> val = val;
	n -> left = build_tree(preorder.substr(1, pos), inorder.substr(0, pos));
	n -> right = build_tree(preorder.substr(pos + 1, preorder.size() - 1 - pos), inorder.substr(pos + 1, inorder.size() - 1 - pos));

	return n;
}

int main()
{
	string preorder;
	string inorder;
	
	cin >> preorder >> inorder;

	node* root = build_tree(preorder, inorder);
	postorder(root);
	cout << endl;
	
	return 0;
}