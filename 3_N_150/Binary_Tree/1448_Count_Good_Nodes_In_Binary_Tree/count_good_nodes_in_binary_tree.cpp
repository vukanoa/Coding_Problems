#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	=====================================
	1448) Count Good Nodes In Binary Tree
	=====================================

	============
	Description:
	============

	Given a binary tree root, a node X in the tree is named good if in the path
	from root to X there are no nodes with a value greater than X.

	Return the number of good nodes in the binary tree.

	========================================
	FUNCTION: int goodNodes(TreeNode* root); 
	========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	        ___________
	        _____3_____
	        __1_____4__
	        3______1__5

	Input: root = [3,1,4,3,null,1,5]
	Output: 4
	Explanation: Nodes in blue are good.
	Root Node (3) is always a good node.
	Node 4 -> (3,4) is the maximum value in the path starting from the root.
	Node 5 -> (3,4,5) is the maximum value in the path
	Node 3 -> (3,1,3) is the maximum value in the path.




	--- Example 2 ---
	        ___________
	        _____3_____
	        __3________
	        4__2_______

	Input: root = [3,3,null,4,2]
	Output: 3
	Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.


	--- Example 3 ---
	Input: root = [1]
	Output: 1
	Explanation: Root is considered as good.


	*** Constraints ***
    The number of nodes in the binary tree is in the range [1, 10^5].
    Each node's value is between [-10^4, 10^4].

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

/* Time  Beats: 99.34% */
/* Space Beats: 7.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	int goodNodes(TreeNode* root)
	{
		int count = 1;
		std::stack<int> stack;

		stack.push(root->val);
		
		dfs(root, count, stack);
		
		return count;
	}

private:
	void dfs(TreeNode* root, int& count, std::stack<int>& stack)
	{
		if (root->val >= stack.top())
			stack.push(root->val);
		
		if (root->left != nullptr)
		{
			if (root->left->val >= stack.top())
				count++;

			dfs(root->left, count, stack);
		}

		if (root->right != nullptr)
		{
			if (root->right->val >= stack.top())
				count++;
			
			dfs(root->right, count, stack);
		}

		if (root->val == stack.top())
			stack.pop();
	}
};

/* Time  Beats: 98.03% */
/* Space Beats: 67.51% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	int goodNodes(TreeNode* root)
	{
		int count = 0;
		dfs(root, INT_MIN, count);

		return count;
	}

private:
	void dfs(TreeNode* root, int max_on_this_path, int& count)
	{
		if (!root)
			return;

		if (root->val >= max_on_this_path)
		{
			count++;
			max_on_this_path = root->val;
		}

		dfs(root->left,  max_on_this_path, count);
		dfs(root->right, max_on_this_path, count);
	}
};
