#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	================================
	199) Binary Tree Right Side View
	================================

	============
	Description:
	============

	Give the "root" of a binary tree, imagine yourself standing on the right
	side of it, return the values of the nodes you can see ordered from top
	to bottom.

	====================================================
	FUNCTION: vector<int> rightSideView(TreeNode* root);
	====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	     1
	  2     3
	    5    4

	Input:  root = [1, 2, 3, null, 5, null, 4]
	Output: [1, 3, 4]


	--- Example 2 ---
	  1
	     3

	Input:  root = [1, null, 3]
	Output: [1, 3]

	--- Example 3 ---


	Input:  root = []
	Output: []

	*** Constraints ***
	The number of nodes in thre tree is in the range [0, 100].
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


class Solution {
private:
    // Find height of a tree, defined by the root node
    int tree_height(TreeNode* root)
    {
        if (root == nullptr)
            return 0;

        // Find the height of left, right subtrees
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);

        // Find max(subtree_height) + 1 to get the height of the tree
        return std::max(left_height, right_height) + 1;
    }

public:
	std::vector<int> rightSideView(TreeNode* root)
	{
		std::vector<int> side_view;
		const int height = tree_height(root);
        int filled = 0;

		recursion(root, side_view, height, filled, 1);

        return side_view;
	}

	// Current level starting from 1
	void recursion(TreeNode* root, std::vector<int>& side_view, const int& height, int& filled, int current_level)
	{
		if (filled == height)
			return;

		if (current_level > side_view.size())
		{
			side_view.push_back(root->val);
			filled++;
		}

		if (root->right)
			recursion(root->right, side_view, height, filled, current_level + 1);

		if (root->left)
			recursion(root->left, side_view, height, filled, current_level + 1);
	}
};



int
main()
{
	Solution sol;

	/* Example 1 */
	/*
			 1
		  2     3
			5    4
	*/
	// TreeNode one(1);
	// TreeNode two(2);
	// TreeNode three(3);
	// TreeNode five(5);
	// TreeNode four(4);

	// one.left = &two;
	// one.right = &three;
	// two.right = &five;
	// three.right = &four;

	// TreeNode* root = &one;



	/* Example 2 */
	/*
		  1
			 3
	*/
	// TreeNode one(1);
	// TreeNode three(3);

	// one.right = &three;

	// TreeNode* root = &one;



	/* Example 3 */
	// TreeNode* root = nullptr;


	/* Example 4 */
	/*
	                   1
	           2            3
	       5       6           7
	    9       8
	     10

	*/
	TreeNode one(1);
	TreeNode two(2);
	TreeNode three(3);
	TreeNode four(4);
	TreeNode five(5);
	TreeNode six(6);
	TreeNode seven(7);
	TreeNode eight(8);
	TreeNode nine(9);
	TreeNode ten(10);

	one.left  = &two;
	one.right = &three;
	three.right = &seven;
	two.left = &five;
	two.right = &six;
	five.left = &nine;
	six.left = &eight;
	nine.right = &ten;

	TreeNode* root = &one;


	std::cout << "\n\t===================================";
	std::cout << "\n\t=== BINARY TREE RIGHT SIDE VIEW ===";
	std::cout << "\n\t===================================\n\n";

	/* Solution */
	std::vector<int> side_view = sol.rightSideView(root);

	/* Write Output */

	bool first = true;
	std::cout << "\n\tSide View: [";
	for (auto x: side_view)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}
