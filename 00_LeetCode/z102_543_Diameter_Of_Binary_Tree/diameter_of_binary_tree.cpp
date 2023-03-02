#include <iostream>

/*
	============
	=== EASY ===
	============

	============================
	543) Diameter of Binary Tree
	============================

	============
	Description:
	============

	Given the "root" of a binary tree, return the length of the diameter of the
	tree.

	The diameter of a binary tree is the length of the longest path between any
	two nodes in a tree. This path may or may not pass through the "root".

	The length of a path between two nodes is represented by the number of
	edges between them.

	===================================================
	FUNCTION: int diameterOfBinaryTree(TreeNode* root);
	===================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [1, 2, 3, 4, 5]
	Output: 3
	Explanation: 3 is the length of the path [4, 2, 1, 3] or [5, 2, 1, 3]

	--- Example 2 ---
	Input:  root = [1, 2]
	Output: 1

	*** Constraints ***
	The number of nodes in the tree is in the range [1, 10^4]
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

	We construct the Solution using recursion. We need to ask ourselves:
		What is the diameter of a Leaf node?
			It's always 0.

	Then, we have to ask:
		What is the diameter with a single leaf node child?
			It's always 1.

	Then, we have to ask:
		What is the diameter of a node with two leaves?
			It's always 2.

	We can clearly see a pattern.

	Use recursion to go to leaf nodes and construct the solution "bottom-up".
	(It's actually a top-down approach because it's a recursion, but you get
	what I mean)

	We will make a function "max_depth" that returns the maximum depth of that
	subtree and within that function we will check if the diameter of this
	subtree is greater than the global diameter and if it is - Update the value

*/


/* Time  Beats: 70.86% */
/* Space Beats: 69.70% */
/*	Time  Complexity: O(N) */
/*
	Space Complexity: O(N)
	Because of the Call Stack
*/
class Solution{
public:
	int diameterOfBinaryTree(TreeNode* root)
	{
		int diameter = 0;
		max_depth(root, diameter);

		return diameter;
	}

	int max_depth(TreeNode* root, int& diameter)
	{
		if (root == nullptr)
			return -1;
		else if (root->left == nullptr && root->right == nullptr)
			return 0;

		int left  = 1 + max_depth(root->left,  diameter);
		int right = 1 + max_depth(root->right, diameter);

		if (left + right > diameter)
			diameter = left + right;

		return (left > right) ? left : right;
	}
};



/* Print nodes at a current level */
void
print_current_level(TreeNode* root, int level)
{
    if (root == NULL)
    {
        std::cout << "null ";
        return;
    }

    if (level == 1)
        std::cout << root->val << " ";
    else if (level > 1)
	{
        print_current_level(root->left, level - 1);
        print_current_level(root->right, level - 1);
    }
}


/*
    Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node
*/
int
height(TreeNode* node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}


/*
    Function to print level
    order traversal a tree
*/
void
print_level_order(TreeNode* root)
{
    int h = height(root);
    int i;

    for (i = 1; i <= h; i++)
        print_current_level(root, i);
}


int
main()
{
	Solution sol;

	/* Example 1 */
	/*
		___________
		_____1_____
		__2_____3__
		4___5______
	*/
	// TreeNode one(1);
	// TreeNode two(2);
	// TreeNode three(3);
	// TreeNode four(4);
	// TreeNode five(5);

	// one.left   = &two;
	// one.right  = &three;
	// two.left   = &four;
	// two.right  = &five;

	// TreeNode* root = &one;




	/* Example 2 */
	/*
		_____
		__1__
		2____
	*/
	// TreeNode one(1);
	// TreeNode two(2);

	// one.left = &two;

	// TreeNode* root = &one;




	/* Example 3 */
	/* 1 */
	// TreeNode one(1);

	// TreeNode* root = &one;



	/* Example 3 */
	/*
		_______________________
		___________5___________
		_____4___________8_____
		__11__________13____4__
		7____2____________5____
	*/
	// TreeNode five(5);
	// TreeNode four(4);
	// TreeNode eight(8);
	// TreeNode eleven(11);
	// TreeNode thirteen(13);
	// TreeNode four_2(4);
	// TreeNode seven(7);
	// TreeNode two(2);
	// TreeNode five_2(5);

	// five.left    = &four;
	// five.right   = &eight;
	// four.left    = &eleven;
	// eight.left   = &thirteen;
	// eight.right  = &four_2;
	// eleven.left  = &seven;
	// eleven.right = &two;
	// four_2.left  = &five_2;

	// TreeNode* root = &five;




	/* Example 4 */
	/*
		_______________________
		___________10__________
		_____5__________-3_____
		__3_____2__________11__
		3__-2_____1____________
	*/
	TreeNode ten(10);
	TreeNode five(5);
	TreeNode three(3);
	TreeNode two(2);
	TreeNode three_2(3);
	TreeNode minus_two(-2);
	TreeNode one(1);

	ten.left          = &five;
	five.left         = &three;
	five.right        = &two;
	three.left        = &three_2;
	three.right       = &minus_two;
	two.right         = &one;

	TreeNode* root = &ten;




	std::cout << "\n\t===============================";
	std::cout << "\n\t=== DIAMETER OF BINARY TREE ===";
	std::cout << "\n\t===============================\n";

	/* Write Input */
	std::cout << "\n\tTree:\n\t\t";
	print_level_order(root);
	std::cout << "\n\n";

	/* Solution */
	int diameter = sol.diameterOfBinaryTree(root);

	/* Write Output */
	std::cout << "\n\tDiameter: " << diameter << "\n\n";

	return 0;
}
