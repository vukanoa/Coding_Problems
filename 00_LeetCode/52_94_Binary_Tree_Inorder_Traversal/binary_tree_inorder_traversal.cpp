#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	=================================
	94) Binary Tree Inorder Traversal
	=================================

	============
	Description:
	============

	Given the "root" of a binary tree, return the inorder traversal of its
	nodes' values.

	=======================================================
	FUNCTION: vector<int> inorderTraversal(TreeNode* root);
	=======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [1, null, 2, 3]
	Output: [1, 3, 2]

	--- Example 2 ---
	Input:  root = []
	Output: []

	--- Example 3 ---
	Input:  root = [1]
	Output: [1]

	*** Constraints ***
	The number of nodes in the tree is in the range [0, 100]
	-100 <= Node.val <= 100

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution{
	void inorder(std::vector<int>& vec, TreeNode* root)
	{
		if (root == nullptr)
			return;

		inorder(vec, root->left);
		vec.push_back(root->val);
		inorder(vec, root->right);
	}
public:
	std::vector<int> inorderTraversal(TreeNode* root)
	{
		std::vector<int> vec;
		inorder(vec, root);

		return vec;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	TreeNode three(3);
	TreeNode two(2, &three, nullptr);
	TreeNode* one = new TreeNode(1, nullptr, &two);

	/* Example 2 */
	// Root is nullptr
	// TreeNode* one = nullptr;

	/* Example 3 */
	// TreeNode* one = new TreeNode(1);


	std::cout << "\n\t=====================================";
	std::cout << "\n\t=== BINARY TREE INORDER TRAVERSAL ===";
	std::cout << "\n\t=====================================\n\n";

	std::cout << "\n\tTODO: Visual print of a binary Tree\n";

	/* Solution */
	std::vector<int> result = sol.inorderTraversal(one);


	bool first = true;
	std::cout << "\n\tInorder: [";
	for (auto x: result)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
