#include <iostream>
#include <stack>

/*
	==============
	=== MEDIUM ===
	==============

	===============================
	98) Validate Binary Search Tree
	===============================

	============
	Description:
	============

	Given the "root" of a binary tree, determine if it is a valid binary search
	tree(BST)

	A valid BST is defined as follows:
		- The left subtree of a node containts only nodes with keys less than
		  the node's key.

		- The right subtree of a node contains only nodes with keys greater
		  than the node's key.

		- Both the left and right subtrees must also be binary search trees.

	==========================================
	FUNCTION: bool isValidBST(TreeNode* root);
	==========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [2, 1, 3]
	Output: true

	--- Example 2 ---
	Input:  root = [5, 1, 4, null, null, 3, 6]

	*** Constraints ***
	- The number of nodes in the tree is in the range [1, 10^4]
	- -2^31 <= Nodel.val <= 2^31 - 1

*/


/*
	------------
	--- IDEA ---
	------------

	It's self-explanatory.

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


/* Recursive Traversal with Valid Range */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
	bool validate(TreeNode* root, TreeNode* low, TreeNode* high)
	{
		if (root == nullptr)
			return true;

		// Check lower bound
		if (low != nullptr && low->val >= root->val)
			return false;

		// Check higher bound
		if (high != nullptr && high->val <= root->val)
			return false;

		return validate(root->left, low, root) && validate(root->right, root, high);
	}

public:
	bool isValidBST(TreeNode* root)
	{
		return validate(root, nullptr, nullptr);
	}
};


/* Iterative Traversal with Valid Range */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2{
	std::stack<TreeNode*> stack, lower_limits, upper_limits;

public:
	void update(TreeNode* root, TreeNode* low, TreeNode* high)
	{
		stack.push(root);
		lower_limits.push(low);
		upper_limits.push(high);
	}

	bool isValidBST(TreeNode* root)
	{
		TreeNode *low = nullptr;
		TreeNode *high = nullptr;
		update(root, low, high);

		while (!stack.empty())
		{
			root = stack.top();
			stack.pop();

			low = lower_limits.top();
			lower_limits.pop();

			high = upper_limits.top();
			upper_limits.pop();

			if (root == nullptr)
				continue;

			TreeNode* val_node = root;
			if (low != nullptr && low->val >= val_node->val)
				return false;

			if (high != nullptr && high->val <= val_node->val)
				return false;

			update(root->right, val_node, high);
			update(root->left, low, val_node);
		}

		return true;
	}
};


/* Recursive Inorder Traversal */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_3{
	TreeNode* prev = nullptr;
public:
	bool isValidBST(TreeNode* root)
	{
		return inorder(root);
	}

	bool inorder(TreeNode* root)
	{
		if (root == nullptr)
			return true;

		if (!inorder(root->left))
			return false;

		if (prev != nullptr && prev->val >= root->val)
			return false;

		prev = root;

		return inorder(root->right);
	}
};


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_4{
	TreeNode* prev = nullptr;
public:
	bool isValidBST(TreeNode* root)
	{
		if (root != nullptr)
		{
			if (!isValidBST(root->left))
				return false;

			if (prev != nullptr && prev->val >= root->val)
				return false;

			prev = root;
			return isValidBST(root->right);
		}

		return true;
	}
};


int
main()
{
	Solution sol;
	// Solution_2 sol_2;
	// Solution_3 sol_3;
	// Solution_4 sol_4;

	/* Example 1 */
	TreeNode three(3);
	TreeNode one(1);
	TreeNode two(2, &one, &three);
	TreeNode *root = &two;

	/* Example 2 */
	// TreeNode three(3);
	// TreeNode six(6);
	// TreeNode one(1);
	// TreeNode four(6, &three, &six);
	// TreeNode five(5, &one, &four);
	// TreeNode *root = &five;

	/* Example 3 */
	// TreeNode three(3);
	// TreeNode two(2, &three, nullptr);
	// TreeNode one(1, nullptr, &two);
	// TreeNode *root = &one;


	std::cout << "\n\t===================================";
	std::cout << "\n\t=== VALIDATE BINARY SEARCH TREE ===";
	std::cout << "\n\t===================================\n";

	std::cout << "\n\tTODO: Write a visual print of BST\n";

	/* Solution */
	if (sol.isValidBST(root))
	// if (sol_2.isValidBST(root))
	// if (sol_3.isValidBST(root))
	// if (sol_4.isValidBST(root))
		std::cout << "\n\tValid BST: True\n\n";
	else
		std::cout << "\n\tValid BST: False\n\n";

	return 0;
}
