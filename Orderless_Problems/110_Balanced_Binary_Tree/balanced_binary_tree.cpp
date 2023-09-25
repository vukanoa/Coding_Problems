#include <iostream>

/*
	============
	=== EASY ===
	============

	=========================
	110) Balanced Binary Tree
	=========================

	============
	Description:
	============

	Given a binary tree, determine if it is height-balanced.

	(A height-balanced binary tree is a binary tree in which the depth of the
	two subtrees of every node never differs by more than one)

	==========================================
	FUNCTION: bool isBalanced(TreeNode* root);
	==========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	    ___________
	    _____3_____
	    __9____20__
	    _____15___7

	Input: root = [3,9,20,null,null,15,7]
	Output: true



	--- Example 2 ---
	    _______________________
	    ___________1___________
	    _____2___________2_____
	    __3_____3______________
	    4___4__________________

	Input: root = [1,2,2,3,3,null,null,4,4]
	Output: false


	--- Example 3 ---
	Input: root = []
	Output: true


	*** Constraints ***
	The number of nodes in the tree is in the range [0, 5000].
	-10^4 <= Node.val <= 10^4

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/*
	------------
	--- IDEA ---
	------------

	Since we have to keep track of the depths, we have to have an additional
	parameter in function "dfs" since also must keep track if at each subtree's
	root, the subtree is balanced. For that reason we have the functions "dfs"
	return bool type, while variable 'x' is passed as a reference.

*/

/* Time  Beats: 93.52% */
/* Space Beats: 17.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	bool isBalanced(TreeNode* root)
	{
	    int x = 0;
	
	    return dfs(root, x);
	}

private:
	bool dfs(TreeNode* root, int& x)
	{
		if (!root)
		{
			x = 0;
			return true;
		}

		/* Left */
		if(!dfs(root->left, x))
			return false;
		int left  = x;

		/* Right */
		if (!dfs(root->right, x))
			return false;
		int right = x;

		/* Difference */
		if (std::abs(left - right) > 1)
			return false;

		/* Max Depth Subtree where "root" is the root of that Subtree */
		x = 1 + std::max(left, right);

		return true;
	}
};
