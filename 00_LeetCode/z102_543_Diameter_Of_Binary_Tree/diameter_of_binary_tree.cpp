#include <iostream>
#include <queue>

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

/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(n)
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




/*
	------------
	--- IDEA ---
	------------

	Same as above, just implemented on another occasion so I wanted to have
	it here as well.
	
*/

/* Time  Beats: 94.44% */
/* Space Beats: 86.28% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS{
public:
	int diameterOfBinaryTree(TreeNode* root)
	{
		int longest_diameter = 0;
		dfs(root, longest_diameter);

		return longest_diameter;
	}

private:
	int dfs(TreeNode* root, int& longest_diameter)
	{
		if (root == nullptr)
			return 0;

		int left  = dfs(root->left,  longest_diameter);
		int right = dfs(root->right, longest_diameter);

		if (left + right > longest_diameter)
			longest_diameter = left + right;

		if (left == 0 && right == 0)
			return 1;

		return left > right ? left+1 : right+1;
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
	std::cout << "\n\t\t\t(TODO: Implement a Visual representation of a Binary Tree)\n\n";
	std::cout << "\n\t*** Level Order ***";
	std::cout << "\n\tTree: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";
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

	int x = vector_print.size() - 1;
	while (vector_print[x] == "null")
	{
		vector_print.pop_back();
		x--;
	}

	print_array(vector_print);
}


int
main()
{
	Solution     sol;
	Solution_DFS sol_dfs;


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
	print_levelorder(root);


	/* Solution */
	// int diameter = sol.diameterOfBinaryTree(root);
	int diameter = sol_dfs.diameterOfBinaryTree(root);


	/* Write Output */
	std::cout << "\n\tDiameter: " << diameter << "\n\n";


	return 0;
}
