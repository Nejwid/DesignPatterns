#pragma once
#include <iostream>
#include <memory>

namespace strategy {
	using namespace::std;

	struct TreeNode {
		int val;
		unique_ptr<TreeNode> left;
		unique_ptr<TreeNode> right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, unique_ptr<TreeNode> left, unique_ptr<TreeNode> right)
			: val(x), left(move(left)), right(move(right)) {}
	};

	class Strategy {
	public:
		virtual void Traversal(TreeNode* root) = 0;
		virtual ~Strategy() = default;
	};

	class Inorder : public Strategy {
	public:
		void Traversal(TreeNode* root) override;
	};

	class Postorder : public Strategy {
	public:
		void Traversal(TreeNode* root) override;
	};

	class Searcher {
	private:
		TreeNode* root;
		unique_ptr<Strategy> current;
	public:
		Searcher(unique_ptr<Strategy> str):current(move(str)), root(nullptr){}
		Searcher(unique_ptr<Strategy> str, TreeNode* root):current(move(str)), root(root){}
		void changeStrategy(unique_ptr<Strategy> str);
		void run();
		~Searcher() {
			delete root;
		}
	};

}