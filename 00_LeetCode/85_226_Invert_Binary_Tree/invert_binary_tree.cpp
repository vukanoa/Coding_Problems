#include <iostream>

/*
	============
	=== EASY ===
	============

	===========================
	226) Invert Binary Tree
	===========================

	============
	Description:
	============

	Given the "root" of a binary Tree, invert the tree, and return its root.

	===============================================
	FUNCTION: TreeNode* invertTree(TreeNode* root);
	===============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [4, 2, 7, 1, 3, 6, 9]
	Output: [4, 7, 2, 9, 6, 3, 1]

	--- Example 2 ---
	Input:  root = [2, 1, 3]
	Output: [2, 1, 3]

	--- Example 3 ---
	Input:  []
	Output: []

	*** Constraints ***
	The number of nodes in the tree is in the range [0, 100].
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

	This is a classic tree problem that is best-suited for a recursive approach

	Algorithm
	The inverse of an empty tree is empty tree. The inverse of a tree with root
	"t", and subtrees "right" and "left", is a tree with root "r", whose right
	subtree is the inverse of "left", and whose left subtree is the inverse of
	"right".
*/



class Solution{
public:
	TreeNode* invertTree(TreeNode* root)
	{
		if (root == nullptr)
			return nullptr;

		TreeNode* left  = invertTree(root->left);
		TreeNode* right = invertTree(root->right);
		root->left  = right;
		root->right = left;

		return root;
	}
};


class Solution_initial{
public:
    TreeNode* invertTree(TreeNode* root)
	{
        if (root == nullptr)
            return nullptr;
        else if (root->left && root->right == nullptr)
        {
            root->right = root->left;
            root->left = nullptr;
        }
        else if (root->left == nullptr && root->right)
        {
            root->left = root->right;
            root->right = nullptr;
        }
        else
        {
            TreeNode* tmp = root->left;
            root->left = root->right;
            root->right = tmp;
        }

        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};


void
inorder(TreeNode* root)
{
	if (root == nullptr)
		return;

	inorder(root->left);
	std::cout << root->val << " ";
	inorder(root->right);
}


int
main()
{
	Solution sol;

	/* Example 1 */
	TreeNode four(4);
	TreeNode two(2);
	TreeNode seven(7);
	TreeNode one(1);
	TreeNode three(3);
	TreeNode six(6);
	TreeNode nine(9);

	four.left   = &two;
	four.right  = &seven;
	two.left    = &one;
	two.right   = &three;
	seven.left  = &six;
	seven.right = &nine;

	TreeNode* root = &four;



	/* Example 2 */
	// TreeNode two(2);
	// TreeNode one(1);
	// TreeNode three(3);

	// two.left  = &one;
	// two.right = &three;

	// TreeNode* root = &two;



	/* Example 3 */
	// TreeNode* root = nullptr;

	std::cout << "\n\t==========================";
	std::cout << "\n\t=== INVERT BINARY TREE ===";
	std::cout << "\n\t==========================\n";

	/* Write Input */
	std::cout << "\n\tBefore: ";
	inorder(root);
	std::cout << "\n";

	/* Solution */
	sol.invertTree(root);

	/* Write Output */
	std::cout << "\n\tAfter:  ";
	inorder(root);
	std::cout << "\n\n";

	return 0;
}
