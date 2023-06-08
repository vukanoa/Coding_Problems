#include <iostream>
#include <stack>
#include <queue>
#include <string>

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

	"return" at Line 97 is the most important thing.

	1) If you are checking the Left subtree, you have to pass current node as
	   the right bound.

	2) If you are checking the Right subtree, you have to pass current node as
	   the left bound.

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


/* Time  Beats: 95.81% */
/* Space Beats: 83.78% */

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




/*
	------------
	--- IDEA ---
	------------

	Essentially the same Idea, just implemented Iteratively.
	
*/

/* Time  Beats: 95.81% */
/* Space Beats: 14.13% */

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




/*
	------------
	--- IDEA ---
	------------

	Do an inorder traversal and check if at any point order is not valid.
	You have to go through the code a few times to "get it". It's not intuitive
	to write this. At least it wasn't intuitive to me.
	
*/

/* Time  Beats: 86.47% */
/* Space Beats: 56.36% */

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




/*
	=============================
	=== This is just printing ===
	=============================
*/

void
print_array(std::vector<std::string>& nums)
{
	bool first = true;
	std::cout << "\n\t*** Level Order ***";
	std::cout << "\n\tTree: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";
}


void
print_levelorder(TreeNode* root)
{
	if (root == nullptr)
		return;
	
	std::queue<TreeNode*> queue;
	queue.push(root);

	std::vector<std::string> vector_print;

	while (!queue.empty())
	{
		int size = queue.size();

		for (int i = 0; i < size; i++)
		{
			TreeNode* node = queue.front();
			queue.pop();

			if (node == nullptr)
			{
				vector_print.push_back("null");
				continue;
			}
			else
				vector_print.push_back(std::to_string(node->val));

			if (node->left != nullptr)
				queue.push(node->left);
			else
				queue.push(nullptr);

			if (node->right != nullptr)
				queue.push(node->right);
			else
				queue.push(nullptr);
		}
	}

	print_array(vector_print);
}


int
main()
{
	Solution sol;
	// Solution_2 sol_2;
	// Solution_3 sol_3;

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


	/* Write Input */
	std::cout << "\n\t\t\t~~~ TODO: Write a visual print of BST ~~~\n";
	print_levelorder(root);

	
	/* Solution */
	bool valid = sol.isValidBST(root);
	// bool valid = sol_2.isValidBST(root);
	// bool valid = sol_3.isValidBST(root);


	/* Write Output */
	if (valid)
		std::cout << "\n\tValid BST: True\n\n";
	else
		std::cout << "\n\tValid BST: False\n\n";


	return 0;
}
