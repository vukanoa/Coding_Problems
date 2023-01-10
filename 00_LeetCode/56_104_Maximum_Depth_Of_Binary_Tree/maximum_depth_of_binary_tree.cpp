#include <iostream>


/*
	============
	=== EASY ===
	============

	=================================
	104) Maximum Depth of Binary Tree
	=================================

	============
	Description:
	============

	Given the "root" of a binary tree, return its maximum depth.

	A binary Tree's maximum depth is the nmber of nodes along the longest path
	from the root node down to the farthest leaf node.

	=======================================
	FUNCTION: int maxDepth(TreeNode* root);
	=======================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [3, 9, 20, null, null, 15, 7]
	Output: 3

	--- Example 2 ---
	Input:  root = [1, null, 2]
	Output: 2

	*** Constraints ***
	The number of nodes in the tree is in the range [0, 10^4]
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


/*
	------------
	--- IDEA ---
	------------

	Let's assume that we're already given the maximum depth of root's let and
	right subtrees by recursion.
	So to find the maximum depth of this binary tree, we will have to take out
	the maximum of hte 2 depths given to us by recursion and add 1 to that to
	consider the current level i.e. root's level into our depth.

	Base Case:
		We can easily analyse tha if we are at a leaf node as root, then its
		left and right subtrees will have 0 depth, and consecutively, this leaf
		node will have max depth of 1.

	From Base Case, just follow recursion and it's self-explanatory.

*/



/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(h)
	Where 'h' is the height of the tree, for the recursive stack.
*/
class Solution{
public:
	int maxDepth(TreeNode* root)
	{
		if (root == nullptr)
			return 0;

		int max_left  = maxDepth(root->left);
		int max_right = maxDepth(root->right);

		return std::max(max_left, max_right) + 1;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	// TreeNode fifteen(15);
	// TreeNode seven(7);
	// TreeNode twenty(20, &fifteen, &seven);
	// TreeNode nine(9);
	// TreeNode three(3, &nine, &twenty);

	// TreeNode* root = &three;


	/* Example 2 */
	// TreeNode one(1);

	// TreeNode* root = &one;


	/* Example 3 */
	// TreeNode* root = nullptr;


	/* Example 4 */
	// TreeNode two(2);
	// TreeNode one(1, &two, nullptr);

	// TreeNode* root = &one;


	/* Example 5 */
	// TreeNode five(5);
	// TreeNode four(4, &five, nullptr);
	// TreeNode three(3, &four, nullptr);
	// TreeNode two(2, &three, nullptr);
	// TreeNode one(1, &two, nullptr);

	// TreeNode* root = &one;


	/* Example 6 */
	TreeNode seven(7);
	TreeNode five(5, &seven, nullptr);
	TreeNode four(4);
	TreeNode two(2, &four, &five);
	TreeNode six(6);
	TreeNode three(3, nullptr, &six);
	TreeNode one(1, &two, &three);

	TreeNode* root = &one;


	std::cout << "\n\t======================================";
	std::cout << "\n\t=== MAXIMUM DEPTH OF A BINARY TREE ===";
	std::cout << "\n\t======================================\n\n";

	/* Solution */
	int depth = sol.maxDepth(root);

	std::cout << "\n\tMaximum Depth is: " << depth << "\n\n";

	return 0;
}
