#include <iostream>
#include <climits>

/*
	============
	=== HARD ===
	============

	=================================
	124) Binary Tree Maximum Path Sum
	=================================

	============
	Description:
	============

	A path in a binary tree is a sequence of nodes where each pair of adjacent
	nodes in the sequence has an edge connecing them. A node can only appear
	in the sequence at most once. Note that the path does not need to pass
	through the root.

	The path sum of a path is the sum of the node's values in the path.

	Given the root of a binary tree, return the maximum path sum of any
	non-empty path.

	=========================================
	FUNCTION: int maxPathSum(TreeNode* root);
	=========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [1, 2, 3]
	Output: 6

	--- Example 2 ---
	Input:  root = [-10, 9, 20, null, null, 15, 7]
	Output: 42

	*** Constraints ***
	The number of nodes in the tree is in the range [1, 3 * 10^4]
	-1000 <= Node.val <= 1000

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

	There could be 4 possibilities:
		1. The path starts at the root and goes down through the root's left
		   child. We don't know how long the path is, but it could extend to
		   the bottom of the left subtree.

		2. The path starts at the root and goes down through the root's right
		   child. Very similar to the tprevious case, but the direction is
		   toward the right.

		3. The path involves both the left and the right child.

		4. The path doesn't involve any child. The root itself is the only
		   element of the path with maximum sum.

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
private:
	int max = INT_MIN;

	int postorder_DFS(TreeNode* root)
	{
		if (root == nullptr)
			return 0;

		int val = root->val;

		int left = postorder_DFS(root->left);
		if (left < 0)
			left = 0;

		int right = postorder_DFS(root->right);
		if (right < 0)
			right = 0;

		max = std::max(max, left + right + val);

		return std::max (left + val, right + val);
	}

public:
	int maxPathSum(TreeNode* root)
	{
		if (root == nullptr)
			return 0;

		postorder_DFS(root);

		return max;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	TreeNode three(3);
	TreeNode two(2);
	TreeNode one(1, &two, &three);
	TreeNode* root = &one;
	/*
		_____
		__1__
		2___3
	*/

	/* Example 2 */
	// TreeNode nine(9);
	// TreeNode seven(7);
	// TreeNode fifteen(15);
	// TreeNode twenty(20, &fifteen, &seven);
	// TreeNode minus_ten(-10, &nine, &twenty);
	// TreeNode* root = &minus_ten;
	/*
		___________
		____-10____
		__9_____20_
		______15__7
	*/

	/* Example 3 */
	// TreeNode two1(2);
	// TreeNode minus_one(-1);
	// TreeNode minus_three(-3, &two1, &minus_one);
	// TreeNode one(1);
	// TreeNode two2(2);
	// TreeNode five(5, &one, &two2);
	// TreeNode minus_two(-2, &minus_three, &five);
	// TreeNode* root = &minus_two;
	/*
		___________
		____-2_____
		_-3_____5__
		2__-1_1___2
	*/

	/* Example 4 */
	// TreeNode four(4);
	// TreeNode minus_two(-2, &four, nullptr);
	// TreeNode one(1);
	// TreeNode five(5, &one, &minus_two);
	// TreeNode three(3);
	// TreeNode two1(2);
	// TreeNode minus_four(-4, &three, &two1);
	// TreeNode two2(2, &five, &minus_four);
	// TreeNode* root = &two2;
	/*
		_____
		__1__
		2___3
	*/

	/* Example 5 */
	// TreeNode four(4);
	// TreeNode minus_two1(-2, &four, nullptr);
	// TreeNode two1(2);
	// TreeNode minus_three(-3, &two1, &minus_two1);
	// TreeNode seven(7);
	// TreeNode two2(2);
	// TreeNode minus_two2(-2, &seven, &two2);
	// TreeNode three(3, &minus_three, &minus_two2);
	// TreeNode *root = &three;
	/*
		_______________________
		___________3___________
		____-3__________-2_____
		__2____-2_____7_____2__
		______4________________
	*/

	/* Example 6 */
	// TreeNode minus_one(-1);
	// TreeNode four(4, &minus_one, nullptr);
	// TreeNode two1(2);
	// TreeNode minus_three(-3, &two1, &four);
	// TreeNode five(5);
	// TreeNode two2(2);
	// TreeNode minus_two(-2, &five, &two2);
	// TreeNode two3(2, &minus_three, &minus_two);
	// TreeNode *root = &two3;
	/*
		_______________________
		___________2___________
		____-3__________-2_____
		__2_____4_____5_____2__
		_____-1________________
	*/

	/* Example 7 */
	// TreeNode minus_one(-1);
	// TreeNode one1(1, &minus_one, nullptr);
	// TreeNode two1(2);
	// TreeNode minus_three(-3, &two1, &one1);
	// TreeNode two2(2);
	// TreeNode one2(2);
	// TreeNode minus_four(-4, &two2, &one2);
	// TreeNode three(3, &minus_three, &minus_four);
	// TreeNode *root = &three;
	/*
		_______________________
		___________3___________
		____-3__________-4_____
		__2_____1_____2_____1__
		_____-1________________
	*/

	/* Example 8 */
	// TreeNode minus_three(-3);
	// TreeNode* root = &minus_three;
	/*
		_____
		_-3__
	*/

	/* Example 9 */
	// TreeNode* root = nullptr;
	/*
		_____
	*/

	/* Example 10 */
	// TreeNode minus_one(-1);
	// TreeNode one1(1, &minus_one, nullptr);
	// TreeNode three(3);
	// TreeNode minus_two1(-2, &one1, &three);
	// TreeNode minus_two2(-2);
	// TreeNode minus_three(-3, &minus_two2, nullptr);
	// TreeNode one(1, &minus_two1, &minus_three);
	// TreeNode* root = &one;
	/*
		_______________________
		___________1___________
		____-2__________-3_____
		__1_____3____-2________
		-1_____________________
	*/


	std::cout << "\n\t====================================";
	std::cout << "\n\t=== BINARY TREE MAXIMUM PATH SUM ===";
	std::cout << "\n\t====================================\n";

	/* Solution */
	int max = sol.maxPathSum(root);

	std::cout << "\n\tMax Path Sum is: " << max << "\n\n";

	return 0;
}
