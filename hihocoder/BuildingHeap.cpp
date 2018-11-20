/************
 * http://hihocoder.com/problemset/problem/1405
 */

#include <iostream>

#define MAX 2000000

using namespace std;


struct node
{
	int val;
	node* left;
	node* right;
};

node* buildTree(int* inorder, int beg, int end)
{
	if (beg > end) {
		return nullptr;
	}

	// find the minimum node as the root of subtree
	int mini, mini_val = MAX;
	for (int i = beg; i <= end; i++) {
		if (inorder[i] < mini_val) {
			mini = i;
			mini_val = inorder[i];
		}
	}

	node* n = new node;
	n -> val = mini_val;
	n -> left = buildTree(inorder, beg, mini - 1); 
	n -> right = buildTree(inorder, mini + 1, end);

	return n;
}

void preorder(node* root)
{
	if (root == nullptr) {
		return;
	}

	cout << root -> val << " ";
	preorder(root -> left);
	preorder(root -> right);
}

int main()
{
	int N;
	cin >> N;

	int arr[N];

	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;

		arr[i] = a;
	}

	node* root = buildTree(arr, 0, N - 1);

	preorder(root);
	cout << endl;

	return 0;
}