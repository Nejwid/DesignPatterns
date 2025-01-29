#include "Strategy.h"

void strategy::Inorder::Traversal(TreeNode* root) {
	if (!root) return;
	Traversal(root->left.get());
	cout << root->val;
	Traversal(root->right.get());
}

void strategy::Postorder::Traversal(TreeNode* root) {
	if (!root) return;
	Traversal(root->left.get());
	Traversal(root->right.get());
	cout << root->val;
}

void strategy::Searcher::changeStrategy(unique_ptr<Strategy> str) {
	this->current = move(str);
}

void strategy::Searcher::run() {
	this->current->Traversal(this->root.get());
}
