#include <iostream>
#include <vector>
#include <stack>


/*
	============
	=== EASY ===
	============

	===========================
	101) Symmetric Tree
	===========================

	============
	Description:
	============

	Given the "root" of a binary tree, check whether it is a mirror of itself
	(i.e. symmetric around its center).

	===========================================
	FUNCTION: bool isSymmetric(TreeNode* root);
	===========================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [1, 2, 2, 3, 4, 4, 3]
	Output: true

	--- Example 2 ---
	Input:  root = [1, 2, 2, null, 3, null, 3]
	Output: false

	*** Constraints ***
	The number of nodes in the tree is in the range [1, 1000]
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

	Postorder is a mirror order of Preorder.

	We push preorder values in vector "left" along with null-nodes which are
	of value -101.
	(It is said in the Description of a problem that a constraint
	is: -100 <= Node.val <= 100, so '-101' is out of bounds, meaning we can
	treat it as a "nullptr")

	We push preorder of left subtree in vector "left" and we push postorder
	of right subtree in vector "right".

	After that all we do is check:
		if (left[i] == right[right.size() - 1 - i])

	Meaning if the 0th element of the "left" vector equals to the last element
	of the "right" vector, and if 1st element of the "left" vector equals to
	the 1st element before the last element of the vector "right" and so on.

	If we find a single element that doesn't match - Tree is NOT Symmetric.
	Return false.

	If every single element matches - Tree is INDEED Symmetric.
	Return true.

*/


/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(h)
	Where 'h' is the the height of tree
*/
class Solution{
	void preorder(TreeNode* root, std::vector<int>& left)
	{
		if (root == nullptr)
		{
			left.push_back(-101); // Push null-nodes as -101
			return;
		}

		left.push_back(root->val);
		preorder(root->left, left);
		preorder(root->right, left);
	}

	void postorder(TreeNode* root, std::vector<int>& right)
	{
		if (root == nullptr)
		{
			right.push_back(-101); // Push null-nodes as -101
			return;
		}

		postorder(root->left, right);
		postorder(root->right, right);
		right.push_back(root->val);
	}

public:
	bool isSymmetric(TreeNode* root)
	{
		if (root == nullptr)
			return true;

		std::vector<int> left;
		std::vector<int> right;

		preorder(root->left, left);
		postorder(root->right, right);

		if (left.size() != right.size())
			return false;

		for (int i = 0; i < left.size(); i++)
		{
			if (left[i] != right[left.size() - 1 - i])
				return false;
		}

		return true;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	TreeNode three1(3);
	TreeNode three2(3);
	TreeNode four1(4);
	TreeNode four2(4);
	TreeNode two1(2, &three1, &four1);
	TreeNode two2(2, &four2, &three2);
	TreeNode one(1, &two1, &two2);

	TreeNode* root = &one;


	/* Example 2 */
	// TreeNode three1(3);
	// TreeNode three2(3);
	// TreeNode two1(2, nullptr, &three1);
	// TreeNode two2(2, nullptr, &three2);
	// TreeNode one(1, &two1, &two2);

	// TreeNode* root = &one;

	/* Example 3 */
	// TreeNode* root = nullptr;

	/* Example 4 */
	// TreeNode two1(2);
	// TreeNode two2(2);
	// TreeNode one(1, &two1, &two2);

	// TreeNode* root = &one;

	/* Example 5 */
	// TreeNode five1(5);
	// TreeNode two1(2, &five1, nullptr);
	// TreeNode two2(2);
	// TreeNode one(1, &two1, &two2);

	// TreeNode* root = &one;


	std::cout << "\n\t======================";
	std::cout << "\n\t=== SYMMETRIC TREE ===";
	std::cout << "\n\t======================\n";

	/* Solution */
	if (sol.isSymmetric(root))
		std::cout << "\n\tTree is INDEED Symmetric!\n\n";
	else
		std::cout << "\n\tTree is NOT Symmetric!\n\n";

	return 0;
}
