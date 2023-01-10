#include <iostream>
#include <vector>
#include <queue>


/*
	==============
	=== MEDIUM ===
	==============

	======================================
	102) Binary Tree Level Order Traversal
	======================================

	============
	Description:
	============

	Given the "root" of a binary tree, return the level ordder traversal of its
	nodes' values. (i.e., from left to right, level by level).

	=========================================================
	FUNCTION: vector<vector<int>> levelOrder(TreeNode* root);
	=========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  root = [3, 9, 20, null, null, 15, 7]
	Output: [[3], [9, 20], [15, 7]]

	--- Example 2 ---
	Input:  root = [1]
	Output: [[1]]

	--- Example 3 ---
	Input:  root = []
	Output: []

	*** Constraints ***
	The number of nodes in the tree is in the range [0, 2000]
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

	Vector "results" will contain multiple vectors, each representing its own
	level.

	"vec_level" will be a temporary vector which will store all of the values
	in the current level.

	Queue is a data structure needed to implement this level order traversal.

	First check if the "root" is nullptr, if it is return an empty vector.

	"num_of_nodes" represents the size of a queue, if it is null break the
	infinite while loop and return the "results" vector.

	While "num_of_nodes" is greater than 0:
		pop from "queue" to a pointer "node"
		push node->val to a vec_level

		If node->left isn't nullptr
			push to a "queue"

		If node->right isn't nullptr
			push to a "queue"

		decrement "num_of_nodes"

	After the while loop ended, push "vec_level" to "results" and clear
	"vec_level".

	Return results.

*/



/*	Time  Complexity: O(n) */
/*
	Space Complexity: O(max(B, W))
	Where 'B' is depth of the tree and 'W' is the width of the tree.
*/
class Solution{
public:
	std::vector<std::vector<int>> levelOrder(TreeNode* root)
	{
		// Base case
		if (root == nullptr)
			return {};

		std::vector<std::vector<int>> results;
		std::vector<int> vec_level;
		std::queue<TreeNode *> queue;

		queue.push(root);

		for(;;)
		{
			int num_of_nodes = queue.size();

			if (num_of_nodes == 0)
				break;

			while (num_of_nodes > 0)
			{
				TreeNode* node = queue.front();
				vec_level.push_back(node->val);
				queue.pop();

				if (node->left != nullptr)
					queue.push(node->left);

				if (node->right != nullptr)
					queue.push(node->right);

				num_of_nodes--;
			}

			results.push_back(vec_level);
			vec_level.clear();
		}

		return results;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	TreeNode fifteen(15);
	TreeNode seven(7);
	TreeNode twenty(20, &fifteen, &seven);
	TreeNode nine(9);
	TreeNode three(3, &nine, &twenty);

	TreeNode* root = &three;


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


	std::cout << "\n\t=========================================";
	std::cout << "\n\t=== BINARY TREE LEVEL ORDER TRAVERSAL ===";
	std::cout << "\n\t=========================================\n\n";

	/* Solution */
	std::vector<std::vector<int>> results = sol.levelOrder(root);

	/* Write Output */
	bool first = true;
	std::cout << "\n\tResults: [";
	for (auto x: results)
	{
		if (!first)
			std::cout << ", ";

		bool first_first = true;
		std::cout << "[";
		for (const auto& xx : x)
		{
			if (!first_first)
				std::cout << ", ";

			std::cout << xx;
			first_first = false;
		}
		std::cout << "]";

		first = false;
	}
	std::cout << "]\n\n";

	return 0;
}
