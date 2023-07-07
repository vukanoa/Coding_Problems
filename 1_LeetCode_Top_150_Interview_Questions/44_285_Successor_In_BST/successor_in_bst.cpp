#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	285) Successor in BST
	===========================

	============
	Description:
	============

	Given the root of a binary search tree and a node p in it, return the
	in-order successor of that node in the BST. If the given node has no
	in-order successor in the tree, return null.

	The successor of a node p is the node with the smallest key greater than
	p.val.

	=================================================================
	FUNCTION: TreeNode* inorderSuccessor(TreeNode* root, TreeNode p);
	=================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [2, 1, 3], p = 1
	Output: 2

	*** Constraints ***
	Unknown

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
public:
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p)
	{
		if (root == nullptr)
			return nullptr;

		if (root == p)
		{
			if (root->right == nullptr)
				return nullptr;

			// Successor of root
			return successor(root->right);
		}

		std::stack<std::pair<TreeNode*, bool>> stack;

		while (root != nullptr)
		{
			if (root->left == p)
			{
				if (root->left->right != nullptr)
					return successor(root->left->right);

				return root;
			}
			else if (root->right == p)
			{
				if (root->right->right != nullptr)
					return successor(root->right->right);

				while (!stack.empty())
				{
					std::pair<TreeNode*, bool> pair = stack.top();

					if (pair.second == true) // Right
						stack.pop();
					else
						return pair.first;
				}
			}
			else
			{
				if (p->val < root->val)
				{
					stack.push({root, false}); // Left is false
					root = root->left;
				}
				else
				{
					stack.push({root, true});  // Right is true
					root = root->right;
				}
			}
		}

		return nullptr;
	}

private:
	TreeNode* successor(TreeNode* root)
	{
		while (root->left != nullptr)
			root = root->left;

		return root;
	}
};
